
#include "stdafx.h"
#include "CppDebug.h"

int _tmain(int argc, _TCHAR* argv[])
{
    std::locale::global(std::locale("Russian_Russia"));

    CppDebug::log(__FILE__, __LINE__, TEXT("Simple message"), 6);

    try {
        try {

            CppDebug::log(TEXT("__FILE__ __LINE__ message and code"));

            _tprintf_s(TEXT(">>> %s"), CppException::GetFormatMessage(3u).c_str());
            _tprintf_s(TEXT(">>> %s"), CppException::GetFormatMessage(12155u).c_str());

            throw new CppException(TEXT(__FILE__), __LINE__, TEXT("Inner error"), 12u);

            

        } catch (CppException *exception) {
            CppDebug::log(exception);
            CppException *ex2 = new CppException(TEXT("Outer error"), 2, exception);
            throw ex2;
        }
    } catch (CppException *ex) {
        std::vector<std::basic_string<TCHAR> > stack_trace;
        stack_trace = ex->GetStackTrace();
        for(StackTrace::iterator it = stack_trace.begin(); it != stack_trace.end(); it++)
        {
            std::basic_string<TCHAR> mes;
            mes = *it;
            _tprintf(TEXT("%s\n"), mes.c_str());
        }
    }

    try {

        CppDebug::log(TEXT("Only message and error code."));

        throw CppException(TEXT("my error message"), 8);

    } catch (CppException exception) {
        CppDebug::log(&exception);
    }

    try {

        CppDebug::log(TEXT("Throw exection by pointer"));

        throw new CppException(TEXT("my error message"), 9);

    } catch (CppException exception) {

        CppDebug::log(TEXT("Unreachable block code"));
        CppDebug::log(&exception);

    } catch (CppException *exception) {

        CppDebug::log(TEXT("Catch exception by pointer"));
        CppDebug::log(exception);

    }

    try {
        RAISE_APPLICATION_ERROR(TEXT("Fill the form"), 45);
    } catch (CppException *exception) {
        CppDebug::log(TEXT("Catch exception from macro RAISE_APPLICATION_ERROR"));
        CppDebug::log(exception);
    }

	return 0;
}
