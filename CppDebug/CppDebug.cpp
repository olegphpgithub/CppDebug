#include "CppDebug.h"

#include <strsafe.h>
#include <iostream>
#include <fstream>
using namespace std;

#define MAX_ERROR_STRING 255

CppDebug::CppDebug(void) {
}

CppDebug::~CppDebug(void) {
}


std::string CppDebug::getLogFileNameA() {
    
    HMODULE hModule = GetModuleHandleW(NULL);
    char lpFilename[MAX_PATH];
    GetModuleFileNameA(hModule, lpFilename, MAX_PATH);
    
    std::string execPath(lpFilename);
    
    std::string logFile = execPath.substr(0, execPath.find_last_of("\\/"));
    
    logFile.append("\\");
    logFile.append("debug.txt");
    
    return logFile;
    
}


void CppDebug::log(LPCWSTR str) {
    std::wofstream myfile (getLogFileNameA().c_str(), std::wofstream::app);
    if (myfile.is_open()) {
        myfile << str << std::endl;
        myfile.close();
    }
}


void CppDebug::log(const char *str) {
    ofstream myfile (getLogFileNameA().c_str(), std::ofstream::app);
    if (myfile.is_open()) {
        myfile << str << std::endl;
        myfile.close();
    }
}

void CppDebug::log(INT arg) {
    ofstream myfile (getLogFileNameA().c_str(), std::ofstream::app);
    if (myfile.is_open()) {
        myfile << arg << std::endl;
        myfile.close();
    }
}

void CppDebug::log(LONG arg) {
    ofstream myfile (getLogFileNameA().c_str(), std::ofstream::app);
    if (myfile.is_open()) {
        myfile << arg << std::endl;
        myfile.close();
    }
}

void CppDebug::log(DWORD arg) {
    ofstream myfile (getLogFileNameA().c_str(), std::ofstream::app);
    if (myfile.is_open()) {
        myfile << arg << std::endl;
        myfile.close();
    }
}


void CppDebug::log(const char *file, int line, LPCTSTR message, HRESULT hr) {
    
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
    
}

void CppDebug::log(const CppException *exception) {
    
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
    
}
