const fs = require('fs');
const path = require('path');
const os = require('os');



const templateH = `
UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Add{funName}{exName}({funKey} key, {funValue} v, EQPDataBroadcastType bType = EQPDataBroadcastType::DEFAULT);

UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
bool QP_Contains{funName}{exName}({funKey} key);

UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
{returnValue} QP_Get{funName}{exName}({funKey} key);

UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
bool QP_Remove{funName}{exName}({funKey} key, EQPDataBroadcastType bType = EQPDataBroadcastType::DEFAULT);

UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Clear{funName}{exName}( EQPDataBroadcastType bType = EQPDataBroadcastType::DEFAULT);

`;

const templateCPP = `
void UQPData::QP_Add{funName}{exName}({funKey} key, {funValue} v, EQPDataBroadcastType bType)
{
    QP_AddValue<{keyType}, {valueType}>(key,v,{enumV},{enumK},bType);
}

bool UQPData::QP_Contains{funName}{exName}({funKey} key)
{
    return QP_Contains<{keyType},{valueType}>(key,{enumV},{enumK});
}

{returnValue} UQPData::QP_Get{funName}{exName}({funKey} key)
{
    return QP_GetValue<{keyType}, {valueType}>(key,{enumV},{enumK});
}

bool UQPData::QP_Remove{funName}{exName}({funKey} key, EQPDataBroadcastType bType)
{
    return QP_RemoveValue<{keyType},{valueType}>(key,{enumV},{enumK},bType);
}

void UQPData::QP_Clear{funName}{exName}( EQPDataBroadcastType bType)
{
    QP_ClearValue<{keyType},{valueType}>({enumV},{enumK},bType);
}

`;

var hStr = "";
var cppStr = "";
function formatStr(params) {
    params.exName = "";
    params.funKey = "FName ";
    params.keyType = "FName ";
    params.enumK = "EQPDataKeyType::FNAME ";
    hStr = hStr + templateH.replace(/{(\w+)}/g, (_, key) => params[key] ?? '');
    cppStr = cppStr + templateCPP.replace(/{(\w+)}/g, (_, key) => params[key] ?? '');

    params.exName = "ExI";
    params.funKey = "int32 ";
    params.keyType = "int32 ";
    params.enumK = "EQPDataKeyType::INT32 ";
    hStr = hStr + templateH.replace(/{(\w+)}/g, (_, key) => params[key] ?? '');
    cppStr = cppStr + templateCPP.replace(/{(\w+)}/g, (_, key) => params[key] ?? '');

    params.exName = "ExO";
    params.funKey = "UObject* ";
    params.keyType = "UObject* ";
    params.enumK = "EQPDataKeyType::VOID ";

    hStr = hStr + templateH.replace(/{(\w+)}/g, (_, key) => params[key] ?? '');
    cppStr = cppStr + templateCPP.replace(/{(\w+)}/g, (_, key) => params[key] ?? '');

    
}

var dataList = 
[
    {funName: 'double',funValue: 'double',valueType: 'double',returnValue: 'double',enumV: 'EQPDataValueType::DOUBLE' },
    {funName: 'int64',funValue: 'int64',valueType: 'int64',returnValue: 'int64',enumV: 'EQPDataValueType::INT64' },
    {funName: 'FVector',funValue: 'const FVector&',valueType: 'FVector',returnValue: 'FVector&',enumV: 'EQPDataValueType::FVECTOR' },
    {funName: 'FName',funValue: 'const FName',valueType: 'FName',returnValue: 'FName&',enumV: 'EQPDataValueType::FNAME' },
    {funName: 'FText',funValue: 'const FText&',valueType: 'FText',returnValue: 'FText&',enumV: 'EQPDataValueType::FTEXT' },
    {funName: 'FString',funValue: 'const FString&',valueType: 'FString',returnValue: 'FString&',enumV: 'EQPDataValueType::FSTRING' },
    {funName: 'bool',funValue: 'bool',valueType: 'bool',returnValue: 'bool',enumV: 'EQPDataValueType::BOOL' },
    {funName: 'float',funValue: 'float',valueType: 'float',returnValue: 'float',enumV: 'EQPDataValueType::FLOAT' },
    {funName: 'int32',funValue: 'int32',valueType: 'int32',returnValue: 'int32',enumV: 'EQPDataValueType::INT32' },
    {funName: 'UObject',funValue: 'UObject*',valueType: 'UObject*',returnValue: 'UObject*',enumV: 'EQPDataValueType::UOBJECT' },
    {funName: 'UQPData',funValue: 'UQPData*',valueType: 'UQPData*',returnValue: 'UQPData*',enumV: 'EQPDataValueType::UQPDATA' },
    {funName: 'FRotator',funValue: 'const FRotator&',valueType: 'FRotator',returnValue: 'FRotator&',enumV: 'EQPDataValueType::FROTATOR' },
    {funName: 'FTransform',funValue: 'const FTransform&',valueType: 'FTransform',returnValue: 'FTransform&',enumV: 'EQPDataValueType::FTRANSFORM' },
    {funName: 'FQuat',funValue: 'const FQuat&',valueType: 'FQuat',returnValue: 'FQuat&',enumV: 'EQPDataValueType::FQUAT' },
]

function writeFile(path,str){
    const startMarker = '//------------auto generator start';
    const endMarker = '//------------auto generator end';

    let fileData = fs.readFileSync(path, 'utf8');

    
    updated = fileData.replace(
      new RegExp(`${startMarker}[\\s\\S]*?${endMarker}`, 'g'),
      `${startMarker}\n${str}\n${endMarker}`
    );
    updated = updated.replace(/\r?\n/g, os.EOL);
    fs.writeFileSync(path, updated, 'utf8');
}
function start(){
    for (let i = 0; i < dataList.length; i++) 
    {
        formatStr(dataList[i]);
    }

    // const filePath = "output/" + params["valueType"] + ".txt";
    // const dir = path.dirname(filePath);

    
    // if (!fs.existsSync(dir)) {
    //     fs.mkdirSync(dir, { recursive: true });
    // }

    const hFilePath ="../Source/QipaWorldUEPlugin/Public/Data/QPData.h"; 
    const cppFilePath = "../Source/QipaWorldUEPlugin/Private/Data/QPData.cpp" ; 
     
    writeFile(hFilePath,hStr);
    writeFile(cppFilePath,cppStr);

    // fs.writeFileSync( filePath, v1H+v2H+v3H+v1CPP+v2CPP+v3CPP , 'utf8');
}

start();

