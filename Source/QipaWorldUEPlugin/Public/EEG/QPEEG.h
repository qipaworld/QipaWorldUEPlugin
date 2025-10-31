#pragma once

#include "HAL/Runnable.h"

#include <atomic>
#include "Windows/AllowWindowsPlatformTypes.h"
#include <windows.h>
#include "Windows/HideWindowsPlatformTypes.h"
class QIPAWORLDUEPLUGIN_API QPEEG : public FRunnable
{
    HANDLE SerialHandle;

public:

    QPEEG(const FString& PortName, int BaudRate);
    virtual ~QPEEG();

    // FRunnable functions
    virtual uint32 Run() override;
    virtual void Stop() override;
    virtual void Exit() override;

    FRunnableThread* qp_thread = nullptr;

    bool qp_runThread = true;

    // FRunnable

    bool QP_Open(const FString& PortName, int BaudRate);

    int QP_Read(uint8* Buffer, int BufferSize);

    void QP_Close();

   

    int qp_parserStatus;

    int payloadLength;
    int payloadBytesReceived;
    int payloadSum;
    int checksum;
    std::atomic<int> qp_attention;
    std::atomic<int> qp_meditation;
    uint8 qp_buffer[256];

    void QP_Parser();
    int QP_ParseByte(uint8 buffer);
    void QP_ParsePacketPayload();
    int QP_GetRawWaveValue(uint8 highOrderByte, uint8 lowOrderByte);
};

