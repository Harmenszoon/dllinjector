#pragma once
#include <windows.h>
#include <vector>
#include <string>

#include "util.hpp"

class pe
{
public:
	pe(std::string_view file);
	pe(std::vector<uint8_t>& file);

	IMAGE_DOS_HEADER* dos_header();
	IMAGE_NT_HEADERS64* nt_headers();

	DWORD get_certificate_offset();
	DWORD get_certificate_size();

	std::vector<uint8_t> certificate();

	void sign(std::vector<uint8_t>& cert);
	void save_to_file(std::string_view file_name);

private:
	void set_certificate_offset(DWORD offset);
	void set_certificate_size(DWORD size);

	std::vector<uint8_t> buffer;
};