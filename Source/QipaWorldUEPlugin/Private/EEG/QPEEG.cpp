#include "EEG/QPEEG.h"

#include "CoreMinimal.h"
#include "HAL/RunnableThread.h"

const int PARSER_CODE_POOR_SIGNAL = 2;
const int PARSER_CODE_HEARTRATE = 3;
const int PARSER_CODE_CONFIGURATION = 4;
const int PARSER_CODE_RAW = 128;
const int PARSER_CODE_DEBUG_ONE = 132;
const int PARSER_CODE_DEBUG_TWO = 133;
const int PARSER_CODE_EEG_POWER = 131;
const int PST_PACKET_CHECKSUM_FAILED = -2;
const int PST_NOT_YET_COMPLETE_PACKET = 0;
const int PST_PACKET_PARSED_SUCCESS = 1;
const int MESSAGE_READ_RAW_DATA_PACKET = 17;
const int MESSAGE_READ_DIGEST_DATA_PACKET = 18;
const int RAW_DATA_BYTE_LENGTH = 2;
const int EEG_DEBUG_ONE_BYTE_LENGTH = 5;
const int EEG_DEBUG_TWO_BYTE_LENGTH = 3;
const int PARSER_SYNC_BYTE = 170;
const int PARSER_EXCODE_BYTE = 85;
const int MULTI_BYTE_CODE_THRESHOLD = 127;
const int PARSER_STATE_SYNC = 1;
const int PARSER_STATE_SYNC_CHECK = 2;
const int PARSER_STATE_PAYLOAD_LENGTH = 3;
const int PARSER_STATE_PAYLOAD = 4;
const int PARSER_STATE_CHKSUM = 5;

QPEEG::QPEEG(const FString& PortName, int BaudRate)
{
    QP_Open(PortName, BaudRate);
    qp_thread = FRunnableThread::Create(this, TEXT("QPEEG"));
}

QPEEG::~QPEEG()
{
    qp_runThread = false;
    if (qp_thread != nullptr)
    {
        qp_thread->Kill(true);
        delete qp_thread;
    }
    QP_Close();
}

uint32 QPEEG::Run()
{
    qp_runThread = true;
    int qp_buffSize = 256;
    uint8 Buffer[256];
    DWORD BytesRead;

    // Keep processing until we're cancelled through Stop() or we're done,
    // although this thread will suspended for other stuff to happen at the same time
    while (qp_runThread)
    {
        
        if (ReadFile(SerialHandle, Buffer, qp_buffSize, &BytesRead, NULL))
        {
            //FString Data = FString(ANSI_TO_TCHAR(reinterpret_cast<char*>(Buffer))).Left(BytesRead);
           // UE_LOG(LogTemp, Log, TEXT("收到串口数据：%s"), *Data);
            QP_Parser();
            for (int i = 0; i < qp_buffSize; ++i) {
                QP_ParseByte(Buffer[i]);
            }
            //QP_ParsePacketPayload();
        }

        FPlatformProcess::Sleep(0.01f);
        //ProcessedNumbers.Add(FMath::RandRange(0, 999));
       
    }


    return 0;
}


void QPEEG::Exit()
{
    // Here's where we can do any cleanup we want to 
}


void QPEEG::Stop()
{
    // Force our thread to stop early
    qp_runThread = false;
    //QP_Close();
}

bool QPEEG::QP_Open(const FString& PortName, int BaudRate)
{
    FString FullName = TEXT("\\\\.\\") + PortName; // 例如 COM3
    SerialHandle = CreateFileW(*FullName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (SerialHandle == INVALID_HANDLE_VALUE)
    {
        UE_LOG(LogTemp, Error, TEXT("not open serial %s"), *PortName);
        return false;
    }

    DCB SerialParams = { 0 };
    SerialParams.DCBlength = sizeof(SerialParams);
    GetCommState(SerialHandle, &SerialParams);
    SerialParams.BaudRate = BaudRate;
    SerialParams.ByteSize = 8;
    SerialParams.StopBits = ONESTOPBIT;
    SerialParams.Parity = NOPARITY;
    SetCommState(SerialHandle, &SerialParams);

    COMMTIMEOUTS Timeouts = { 0 };
    Timeouts.ReadIntervalTimeout = 50;
    Timeouts.ReadTotalTimeoutConstant = 50;
    Timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(SerialHandle, &Timeouts);

    UE_LOG(LogTemp, Log, TEXT("open sreial %s"), *PortName);
    return true;
}

int QPEEG::QP_Read(uint8* Buffer, int BufferSize)
{
    DWORD BytesRead;
    if (ReadFile(SerialHandle, Buffer, BufferSize, &BytesRead, NULL))
        return BytesRead;
    return -1;
}

void QPEEG::QP_Close()
{
    if (SerialHandle != INVALID_HANDLE_VALUE)
        CloseHandle(SerialHandle);
}


    
void QPEEG::QP_Parser()
{
    qp_parserStatus = PARSER_STATE_SYNC;
}

int QPEEG::QP_ParseByte(uint8 buffer)
{
    int returnValue = 0;
    switch (qp_parserStatus)
        {
            case 1: 
            {
                if ((buffer & 0xFF) != PARSER_SYNC_BYTE)
                {
                    break;
                }
                qp_parserStatus = PARSER_STATE_SYNC_CHECK;
                    
                break;
            }
        case 2: 
            {

                if ((buffer & 0xFF) == PARSER_SYNC_BYTE)
                {
                    qp_parserStatus = PARSER_STATE_PAYLOAD_LENGTH;
                }
                else
                {
                    qp_parserStatus = PARSER_STATE_SYNC;
                }
                break;
            }
        case 3: 
            {
                payloadLength = (buffer & 0xFF);
                payloadBytesReceived = 0;
                payloadSum = 0;
                qp_parserStatus = PARSER_STATE_PAYLOAD;
                break;
            }
        case 4: 
        {
            qp_buffer[(payloadBytesReceived++)] = buffer;
            payloadSum += (buffer & 0xFF);
            if (payloadBytesReceived < payloadLength)
            {
                break;
            }
            qp_parserStatus = PARSER_STATE_CHKSUM;
            break;
        }
        case 5:
        {
            checksum = (buffer & 0xFF);
            qp_parserStatus = PARSER_STATE_SYNC;
            if (checksum != ((payloadSum ^ 0xFFFFFFFF) & 0xFF))
            {
                returnValue = PST_PACKET_CHECKSUM_FAILED;
                UE_LOG(LogTemp, Error, TEXT("CheckSum ERROR!!"));
            }
            else
            {
                returnValue = 1;
                QP_ParsePacketPayload();
            }
            break;
        }
        }
    return returnValue;
}



void QPEEG::QP_ParsePacketPayload()
{
    int i = 0;
    int extendedCodeLevel = 0;
    int code = 0;
    int valueBytesLength = 0;
    int signal = 0; int config = 0; int heartrate = 0;
    int rawWaveData = 0;
    while (i < payloadLength)
    {
        extendedCodeLevel++;
        while (qp_buffer[i] == PARSER_EXCODE_BYTE)
        {
            i++;
        }
        code = qp_buffer[(i++)] & 0xFF;
        if (code > MULTI_BYTE_CODE_THRESHOLD)
        {
            valueBytesLength = qp_buffer[(i++)] & 0xFF;
        }
        else
        {
            valueBytesLength = 1;
        }
        if (code == PARSER_CODE_RAW)
        {
            if ((valueBytesLength == RAW_DATA_BYTE_LENGTH))
            {
                uint8 highOrderByte = qp_buffer[i];
                uint8 lowOrderByte = qp_buffer[(i + 1)];
                rawWaveData = QP_GetRawWaveValue(highOrderByte, lowOrderByte);
                if (rawWaveData > 32768) {
                    rawWaveData-=65536;
                }
                   // UE_LOG(LogTemp, Log, TEXT("Raw: %d"), rawWaveData);

                   
            }
            i += valueBytesLength;
        }
        else
            {
                switch (code)
                {
                    case PARSER_CODE_POOR_SIGNAL: {
                        signal = qp_buffer[i] & 0xFF;
                        i += valueBytesLength;
                        UE_LOG(LogTemp, Log, TEXT("PQ: %d"), signal);

                        break;
                    }
                    
                    case PARSER_CODE_EEG_POWER: {

                        i += valueBytesLength;
                            break;
                    }
                    case PARSER_CODE_CONFIGURATION: {

                        //attention
                        if (signal == 29 || signal == 54 || signal == 55 || signal == 56 || signal == 80 ||
                            signal == 81 || signal == 82 || signal == 107 || signal == 200)
                        {
                            config = qp_buffer[i] & 0xFF;
                            
                                UE_LOG(LogTemp, Log, TEXT("NoShouldAtt: %d"), config);

                                i += valueBytesLength;
                                break;
                        }
                        else
                        {
                            config = qp_buffer[i] & 0xFF;
                           
                                UE_LOG(LogTemp, Log, TEXT("Att: %d"), config);
                                qp_attention = config;
                        }
                        i += valueBytesLength;
                            break;
                    }
                    case PARSER_CODE_HEARTRATE: {

                        heartrate = qp_buffer[i] & 0xFF;
                            i += valueBytesLength;
                            break;
                    }
                    case PARSER_CODE_DEBUG_ONE: {

                        if (valueBytesLength == EEG_DEBUG_ONE_BYTE_LENGTH)
                        {
                            i += valueBytesLength;
                        }
                        break;
                    }
                    case PARSER_CODE_DEBUG_TWO: {

                        if (valueBytesLength == EEG_DEBUG_TWO_BYTE_LENGTH)
                        {
                            i += valueBytesLength;
                        }
                        break;
                    }
                    case 5: {
                        //Meditation
                        if (signal == 29 || signal == 54 || signal == 55 || signal == 56 || signal == 80 ||
                            signal == 81 || signal == 82 || signal == 107 || signal == 200)
                        {
                            config = qp_buffer[i] & 0xFF;

                            UE_LOG(LogTemp, Log, TEXT("NoShouldAtt: %d"), config);

                            i += valueBytesLength;
                            break;
                        }
                        else
                        {
                            config = qp_buffer[i] & 0xFF;

                            UE_LOG(LogTemp, Log, TEXT("Med: %d"), config);
                            qp_meditation = config;
                        }
                        i += valueBytesLength;
                        break;
                    
                        break;
                    }
                   /* case 0x18: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 1 / 3"));

                        break;
                    }
                    case 0xD4: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 2 / 3"));

                        break;
                    }
                    case 0x8B: {
                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 3 / 3"));


                        break;
                    }
                    case 0x17: {

                        UE_LOG(LogTemp, Log, TEXT("______________________HighAlpha 1 / 3"));

                        break;
                    }
                    case 0x3B: {

                        UE_LOG(LogTemp, Log, TEXT("______________________HighAlpha 2 / 3"));

                        break;
                    }
                    case 0xDC: {
                        UE_LOG(LogTemp, Log, TEXT("______________________HighAlpha 3 / 3"));


                        break;
                    }
                    case 0x18: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 1 / 3"));

                        break;
                    }
                    case 0xD4: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 2 / 3"));

                        break;
                    }
                    case 0x8B: {
                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 3 / 3"));


                        break;
                    }
                    case 0x18: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 1 / 3"));

                        break;
                    }
                    case 0xD4: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 2 / 3"));

                        break;
                    }
                    case 0x8B: {
                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 3 / 3"));


                        break;
                    }
                    case 0x18: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 1 / 3"));

                        break;
                    }
                    case 0xD4: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 2 / 3"));

                        break;
                    }
                    case 0x8B: {
                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 3 / 3"));


                        break;
                    }
                    case 0x18: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 1 / 3"));

                        break;
                    }
                    case 0xD4: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 2 / 3"));

                        break;
                    }
                    case 0x8B: {
                        UE_LOG(LogTemp, Log, TEXT("______________________Delta 3 / 3"));


                        break;
                    }
                             
                    case 0x02: {

                        UE_LOG(LogTemp, Log, TEXT("______________________LowAlpha 1 / 3"));

                        break;
                    }
                    case 0x58: {

                        UE_LOG(LogTemp, Log, TEXT("______________________LowAlpha 2 / 3"));

                        break;
                    }
                    case 0xC1: {
                        UE_LOG(LogTemp, Log, TEXT("______________________LowAlpha 3 / 3"));


                        break;
                    }
                    case 0x69: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Theta 3 / 3"));

                        break;
                    }
                    case 0xD1: {

                        UE_LOG(LogTemp, Log, TEXT("______________________Theta 2 / 3"));

                        break;
                    }
                    case 0x13: {
                        UE_LOG(LogTemp, Log, TEXT("______________________Theta 1 / 3"));


                        break;
                    }*/
                }
            }
    }
    //qp_parserStatus = PARSER_STATE_SYNC;
}



//02 LowBeta 1 / 3
//50 LowBeta 2 / 3
//00 LowBeta 3 / 3
//03 HighBeta 1 / 3
//CB HighBeta 2 / 3
//9D HighBeta 3 / 3
//03 LowGamma 1 / 3
//6D LowGamma 2 / 3
//3B LowGamma 3 / 3
//03 MiddleGamma 1 / 3
//7E MiddleGamma 2 / 3
//89 MiddleGamma 3 / 3
int QPEEG::QP_GetRawWaveValue(uint8 highOrderByte, uint8 lowOrderByte)
{
        /* Sign­extend the signed high byte to the width of a signed int */
        int hi = (int)highOrderByte;
        /* Extend low to the width of an int, but keep exact bits instead of sign­extending */
        int lo = ((int)lowOrderByte) & 0xFF;/* Calculate raw value by appending the exact low bits to the sign­extended high bits */
        int value = (hi << 8) | lo;
        return (value);
}
//}
//}