#include "CppException.h"

#include <tchar.h>
#include <strsafe.h>
#include <iostream>
#include <fstream>

using namespace std;


CppException::~CppException(void)
{
    
}


CppException::CppException(const char *file, int line,
    LPCTSTR error, HRESULT hr) {
    
    CppInitialize();
    
    size_t sizeInWords = 0;
    
#ifdef _UNICODE
    size_t wcfile = 0;
    StringCchLengthA(file, STRSAFE_MAX_CCH, &wcfile);
    size_t bcfile = (wcfile + 1) * sizeof(TCHAR);
    wcFilePath = (TCHAR *)LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, bcfile);
    size_t ReturnSize = 0;
    mbstowcs_s(&ReturnSize, wcFilePath, wcfile + 1, file, wcfile);
#else
    size_t bcfile = 0;
    StringCchLengthA(file, STRSAFE_MAX_CCH, &bcfile);
    bcfile++;
    wcFilePath=(TCHAR *) LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, bcfile);
    StringCbCopy(wcFilePath, bcfile, file);
#endif

    iLineCode = line;
    
    size_t wcerror = 0;
    StringCchLength(error, STRSAFE_MAX_CCH, &wcerror);
    size_t bcerror = (wcerror + 1) * sizeof(TCHAR);
    wcError = (TCHAR *)LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, bcerror);
    StringCbCopy(wcError, bcerror, error);

    herr = hr;
    
}


CppException::CppException(LPCTSTR error, HRESULT hr) {
    
    CppInitialize();
    
    size_t wcerror = 0;
    StringCchLength(error, STRSAFE_MAX_CCH, &wcerror);
    size_t bcerror = (wcerror + 1) * sizeof(TCHAR);
    wcError = (TCHAR *)LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, bcerror);
    StringCbCopy(wcError, bcerror, error);

    herr = hr;
    
}


void CppException::CppInitialize(void) {
    wcFilePath = NULL;
    iLineCode = 0;
    herr = S_OK;
}


void CppException::log(HRESULT hr) {
    
    
}