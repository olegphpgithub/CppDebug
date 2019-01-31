#include "CppDebug.h"

#include <strsafe.h>
#include <shlwapi.h>
#include <iostream>
#include <fstream>
#include <clocale>
using namespace std;

#define MAX_ERROR_STRING 255

CppDebug::CppDebug(void) {
}

CppDebug::~CppDebug(void) {
}

LPTSTR g_logFileName = NULL;

LPTSTR CppDebug::getLogFileName() {
    
    if(g_logFileName == NULL) {
        g_logFileName = (LPTSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH * sizeof(TCHAR));

        HMODULE hModule = GetModuleHandle(NULL);
        TCHAR lptFileName[MAX_PATH];
        ZeroMemory(lptFileName, MAX_PATH * sizeof(TCHAR));
        GetModuleFileName(hModule, lptFileName, MAX_PATH);
        PathRemoveFileSpec(lptFileName);
        
        StringCchCat(lptFileName, MAX_PATH, TEXT("\\debug.txt"));
        StringCbCopy(g_logFileName, MAX_PATH * sizeof(TCHAR), lptFileName);

        return g_logFileName;
    } else {
        return g_logFileName;
    }
    
    
}






void CppDebug::log(LPCTSTR str) {

    std::wfstream myfile;

    myfile.open(getLogFileName(), std::wofstream::binary | std::wofstream::app);
    if (myfile.is_open()) {
        myfile << str << std::endl;
        myfile.close();
    }
    
}


void CppDebug::log(const char *str) {
    /*
    ofstream myfile (getLogFileNameA().c_str(), std::ofstream::app);
    if (myfile.is_open()) {
        myfile << str << std::endl;
        myfile.close();
    }
    */
}

void CppDebug::log(INT arg) {
    /*
    ofstream myfile (getLogFileNameA().c_str(), std::ofstream::app);
    if (myfile.is_open()) {
        myfile << arg << std::endl;
        myfile.close();
    }
    */
}

void CppDebug::log(LONG arg) {
    /*
    ofstream myfile (getLogFileNameA().c_str(), std::ofstream::app);
    if (myfile.is_open()) {
        myfile << arg << std::endl;
        myfile.close();
    }
    */
}

void CppDebug::log(DWORD arg) {
    /*
    ofstream myfile (getLogFileNameA().c_str(), std::ofstream::app);
    if (myfile.is_open()) {
        myfile << arg << std::endl;
        myfile.close();
    }
    */
}


void CppDebug::log(const char *file, int line, LPCTSTR message, HRESULT hr) {
    /*
    size_t cchDest = MAX_ERROR_STRING;
    TCHAR pszDest[MAX_ERROR_STRING];
    LPCTSTR pszFormat = TEXT("%s:%d: %s: 0x%08lx\n");
    
    wchar_t *wcFile;
    size_t size = strlen(file) + 1;
    wcFile = new wchar_t[size];
    size_t outSize;
    mbstowcs_s(&outSize, wcFile, size, file, strlen(file) - 1);
    
    HRESULT hres = StringCchPrintf(
        pszDest, cchDest, pszFormat, wcFile, line, message, hr
    );
    
    CppDebug::log(pszDest);
    */
}

void CppDebug::log(const CppException *exception) {
    /*
    size_t cchDest = MAX_ERROR_STRING;
    TCHAR pszDest[MAX_ERROR_STRING];
    
    if( (exception->wcFilePath != NULL) && (exception->iLineCode > 0) ) {
        
        LPCTSTR pszFormat = TEXT("%s:%d: %s: 0x%08lx\n");
        
        HRESULT hres = StringCchPrintf(
            pszDest, cchDest, pszFormat, exception->wcFilePath,
            exception->iLineCode, exception->wcError, exception->herr
        );
        
    } else {
        
        LPCTSTR pszFormat = TEXT("%s: 0x%08lx\n");
        
        HRESULT hres = StringCchPrintf(
            pszDest, cchDest, pszFormat, exception->wcError, exception->herr
        );
        
    }
    
    CppDebug::log(pszDest);
    */
}
