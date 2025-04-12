const fs = require('fs');
// 格式化字符串的函数
function formatStr(fileName,template, params) {
    fs.writeFileSync(fileName, template.replace(/{(\w+)}/g, (_, key) => params[key] ?? ''), 'utf8');
}

// 示例：将模板字符串中的占位符 `{}` 替换为相应的值
const template = `
UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Add{funname}(FName key, {addvalue} v, bool sync = false);
UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Add{funname}ExI(int32 key, {addvalue} v, bool sync = false);
UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Add{funname}ExO(UObject* key, {addvalue} v, bool sync = false);

UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
bool QP_Contains{funname}ExI(int32 key);
UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
bool QP_Contains{funname}ExO(UObject* key);
UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
bool QP_Contains{funname}(FName key);

UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
{returnvalue} QP_Get{funname}(FName key);
UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
{returnvalue} QP_Get{funname}ExI(int32 key);
UFUNCTION(BlueprintPure, Category = "QipaWorld|QPData")
{returnvalue} QP_Get{funname}ExO(UObject* k = nullptr);

UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Remove{funname}ExO(UObject* key, bool sync = false);
UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Remove{funname}(FName key, bool sync = false);
UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Remove{funname}ExI(int32 key, bool sync = false);

UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Clear{funname}ExI( bool sync = false);
UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Clear{funname}ExO( bool sync = false);
UFUNCTION(BlueprintCallable, Category = "QipaWorld|QPData")
void QP_Clear{funname}( bool sync = false);

QP_ADD_TYPE_FUN({returnvalue}, {addvalue}, int32, {valuetype}, EQPDataKeyType::INT32, {valueenum}, {funname}ExI)
QP_ADD_TYPE_FUN({returnvalue}, {addvalue}, UObject*, {valuetype}, EQPDataKeyType::VOID, {valueenum}, {funname}ExO)
QP_ADD_TYPE_FUN({returnvalue}, {addvalue}, FName, {valuetype}, EQPDataKeyType::FNAME, {valueenum}, {funname})

`;

formatStr('output/double.txt',template, { funname: 'double', 
                                    addvalue: 'double', 
                                    returnvalue: 'double', 
                                    valuetype: 'double', 
                                    valueenum: 'EQPDataValueType::DOUBLE' });

formatStr('output/int64.txt',template, { funname: 'int64', 
                                    addvalue: 'int64', 
                                    returnvalue: 'int64', 
                                    valuetype: 'int64', 
                                    valueenum: 'EQPDataValueType::INT64' });


//console.log(result);  // 输出: Hello, my name is John and I am 30 years old.