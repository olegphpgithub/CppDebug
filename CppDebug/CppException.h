#pragma once

#include <iostream>
#include <windows.h>

class CppException
{
public:
    CppException(HRESULT hr);
    CppException(LPCTSTR error, HRESULT hr);
    CppException(const char *file, int line, LPCTSTR error, HRESULT hr);
    ~CppException(void);
    
    void CppInitialize(void);
    
    static void log(HRESULT hr);
    
    TCHAR *wcFilePath;
    int iLineCode;
    TCHAR *wcError;
    HRESULT herr;
};
