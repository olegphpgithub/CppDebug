#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

typedef std::vector<std::basic_string<TCHAR> > StackTrace;

#define ERROR_REPORTING 1

#if ERROR_REPORTING == 1
    #define RAISE_APPLICATION_ERROR(ERROR, ERRNO) \
        throw new CppException(TEXT(__FILE__), __LINE__, ERROR, ERRNO)
#else if ERROR_REPORTING == 0
    #define RAISE_APPLICATION_ERROR(ERROR, ERRNO) \
        throw new CppException(ERROR, ERRNO)
#endif

class CppException
{
public:
    CppException(void);
    CppException(CppException &obj);
    ~CppException(void);
    CppException(LPCTSTR error, DWORD errcode);
    CppException(LPCTSTR file, int line, LPCTSTR error, DWORD errcode);
    std::vector<std::basic_string<TCHAR> > GetStackTrace();
    
    TCHAR m_szFilePath[MAX_PATH];
    int m_iLineCode;
    TCHAR *m_szError;
    DWORD m_dwErrno;
    CppException *m_stack;
};
