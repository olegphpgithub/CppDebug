
#include "stdafx.h"
#include "CppDebug.h"

int _tmain(int argc, _TCHAR* argv[])
{
    std::locale::global(std::locale("Russian_Russia"));

    CppDebug::log(__FILE__, __LINE__, TEXT("Simple message"), 6);

    try {

        CppDebug::log(TEXT("__FILE__ __LINE__ message and code"));

        throw CppException(__FILE__, __LINE__, TEXT("my error zero"), 7);

    } catch (CppException exception) {
        CppDebug::log(&exception);
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

	return 0;
}
