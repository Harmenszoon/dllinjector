#include "portable_executable.hpp"
#include "registry.hpp"
#include "library_loader.hpp"
#include <iostream>

void inject(std::string_view ll_file_name, std::string_view class_name)
{
	const auto loaded_library = LoadLibraryA(ll_file_name.data());
	const auto entry_point = GetProcAddress(loaded_library, "load_lib");

	const auto window = FindWindowA(class_name.data(), nullptr);
	if (window == nullptr)
	{
		std::cout << "Window class name not found\n";
		return;
	}

	const auto thread_id = GetWindowThreadProcessId(window, nullptr);

	auto hook = SetWindowsHookExW(WH_GETMESSAGE, (HOOKPROC)entry_point, loaded_library, thread_id);
	PostThreadMessageW(thread_id, WM_USER + 400, 0, 0);

	Sleep(200);
	UnhookWindowsHookEx(hook);
}

void main(const int argument_count, char* argument[])
{
	if (argument_count == 1)
	{
		std::cout << "Incorrect usage\n";
		std::cin.ignore();
		std::cin.get();
		return;
	}
	
	registry::exploit_registry();

	std::cout << "Start your process and enter the window classname:\n";
	std::string class_name;
	std::cin >> class_name;

	pe ntdll(R"(C:\windows\system32\ntdll.dll)");
	pe input_file(argument[1]);
	pe ll(library_loader);

	auto cert = ntdll.certificate();
	input_file.sign(cert);
	ll.sign(cert);

	const auto ll_file_name = util::get_temp_path_of_file(util::generate_guid() + ".dll");
	const auto output_file_name = util::get_temp_path_of_file("gwmapi.dll");

	ll.save_to_file(ll_file_name);
	input_file.save_to_file(output_file_name);

	inject(ll_file_name, class_name);
	registry::reset_registry();
}