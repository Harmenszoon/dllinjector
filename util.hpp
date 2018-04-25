#pragma once
#include <windows.h>
#include <fstream>
#include <vector>

namespace util
{
	std::vector<std::uint8_t> file_to_buffer(std::string_view file);
	void buffer_to_file(std::vector<std::uint8_t>& buffer, std::string_view file_name);
	HKEY open_registry_key(std::string_view key);
	std::string get_reg_entry(HKEY key, std::string_view entry_name);
	void set_reg_entry(HKEY key, std::string_view entry_name, std::string_view data);
	std::string get_temp_path_of_file(std::string filename);
	std::string generate_guid();
}