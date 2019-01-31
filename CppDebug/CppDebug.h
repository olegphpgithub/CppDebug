#pragma once

#include <windows.h>
#include <string.h>

#include "CppException.h"

class CppDebug
{
public:
    CppDebug(void);
    ~CppDebug(void);
    static std::string getLogFileNameA();
    static void log(LPCWSTR str);
    static void log(const char *str);
    static void log(INT arg);
    static void log(LONG arg);
    static void log(DWORD arg);
    static void log(const CppException *exception);
    static void log(const char *file, int line, LPCTSTR message, HRESULT hr);
    
};
