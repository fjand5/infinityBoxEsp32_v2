#pragma once
#include "voca_env.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#ifdef AUTH_FEATURE
#include <ArduinoJWT.h>
#include "voca_store/voca_store.h"
ArduinoJWT auth_jwt(__TIME__);
#endif
// uint32_t createHash(String str)
// {
//     uint32_t ret = 0;
//     for (size_t i = 0; i < str.length(); i++)
//     {
//         ret += int8_t(str[i]);
//     }
//     return ret;
// }
String createAuthJwt()
{
#ifdef AUTH_FEATURE
    DynamicJsonDocument _doc(128);
    JsonObject obj = _doc.to<JsonObject>();
    obj["exp"] = String(millis() + EXPIRE_TIME);
    obj["hpw"] = simpleHash(getPassword());
    String tmp;
    serializeJson(_doc, tmp);
    return auth_jwt.encodeJWT(tmp);
#else
    return "";

#endif
}
bool checkAuthJwt(String token)
{
#ifdef AUTH_FEATURE
    DynamicJsonDocument _doc(128);
    String payload;
    if (auth_jwt.decodeJWT(token, payload))
    {
        DeserializationError err = deserializeJson(_doc, payload);
        if (err) // sai cấu trúc json
            return false;
        JsonObject obj = _doc.as<JsonObject>();

#ifdef CHECK_EXPIRE
        int exp = obj["exp"];
        if (exp < millis() || exp >= (millis() + EXPIRE_TIME))
        // hết hạn hoặc  không hợp lệ
        {
            return false;
        }
#endif
        if (obj["hpw"] != simpleHash(getPassword())) // mật khẩu đã thay đổi
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
#else
    return true;

#endif
}