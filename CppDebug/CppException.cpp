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
    
}

CppException::~CppException(void)
{
    if (m_szError != NULL)
    {
        delete []m_szError;
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
    
}
