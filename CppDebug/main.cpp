
#include "stdafx.h"
#include "CppDebug.h"

int _tmain(int argc, _TCHAR* argv[])
{
    std::locale::global(std::locale("Russian_Russia"));

    CppDebug::log(TEXT("Русский текс в перемешу с English www фыва ФЫВА WWW ёЁжик!!!"));
    
	return 0;
}
