#include "CppException.h"

#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <fstream>


CppException::CppException(void)
{
    memset(m_szFilePath, 0, MAX_PATH * sizeof(TCHAR));
    m_iLineCode = 0;
    m_szError = NULL;
    m_dwErrno = ERROR_SUCCESS;
    m_stack = NULL;
}

CppException::CppException(CppException &obj)
{
    
    _tcscpy_s(m_szFilePath, MAX_PATH, obj.m_szFilePath);
    
    m_iLineCode = obj.m_iLineCode;
    
    if (obj.m_szError != NULL)
    {
        m_szError = new TCHAR[_tcslen(obj.m_szError) + 1];
        _tcscpy_s(m_szError, _tcslen(obj.m_szError) + 1, obj.m_szError);
    } else {
        m_szError = NULL;
    }
    
    m_dwErrno = obj.m_dwErrno;
    
    m_stack = obj.m_stack;
}

CppException::~CppException(void)
{
    if (m_szError != NULL)
    {
        delete []m_szError;
    }
    if (m_stack != NULL)
    {
        delete m_stack;
    }
}

CppException::CppException(LPCTSTR file,
                           int line,
                           LPCTSTR error,
                           DWORD errcode)
{
    if(file != NULL)
    {
        _tcscpy_s(m_szFilePath, MAX_PATH, file);
    } else {
        memset(m_szFilePath, 0, MAX_PATH * sizeof(TCHAR));
    }
    
    m_iLineCode = line;
    
    if(error != NULL)
    {
        m_szError = new TCHAR[_tcslen(error) + 1];
        _tcscpy_s(m_szError, _tcslen(error) + 1, error);
    } else {
        m_szError = new TCHAR(0);
    }
    
    m_dwErrno = errcode;
    
    m_stack = NULL;
}


CppException::CppException(LPCTSTR error, DWORD errcode)
{
    
    memset(m_szFilePath, 0, MAX_PATH * sizeof(TCHAR));
    
    m_iLineCode = 0;
    
    if(error != NULL)
    {
        m_szError = new TCHAR[_tcslen(error) + 1];
        _tcscpy_s(m_szError, _tcslen(error) + 1, error);
    } else {
        m_szError = new TCHAR(0);
    }
    
    m_dwErrno = errcode;
    
    m_stack = NULL;
}


std::vector<std::basic_string<TCHAR> > CppException::GetStackTrace()
{
    std::vector<std::basic_string<TCHAR> > stack_trace;
    if (m_stack != NULL)
    {
        stack_trace = m_stack->GetStackTrace();
    }
    if( (_tcslen(m_szFilePath) > 0) && (m_iLineCode > 0) )
    {
        LPCTSTR szFormat = TEXT("%s:%d: %s: 0x%08lX");
        TCHAR szMessage[1024];
        _sntprintf_s(szMessage,
            1024,
            _TRUNCATE,
            szFormat,
            m_szFilePath,
            m_iLineCode,
            m_szError,
            m_dwErrno);
        stack_trace.insert(stack_trace.begin(), szMessage);
    }
    else
    {
        LPCTSTR szFormat = TEXT("%s: 0x%08lX");
        TCHAR szMessage[1024];
        _sntprintf_s(szMessage,
            1024,
            _TRUNCATE,
            szFormat,
            m_szError,
            m_dwErrno);
        stack_trace.insert(stack_trace.begin(), szMessage);
    }
    return stack_trace;
}
