#include "portable_executable.hpp"
using namespace std;

pe::pe(string_view file)
{
	buffer = util::file_to_buffer(file);
}

pe::pe(vector<uint8_t>& file)
{
	buffer = file;
}

IMAGE_DOS_HEADER* pe::dos_header()
{
	return reinterpret_cast<IMAGE_DOS_HEADER*>(buffer.data());
}

IMAGE_NT_HEADERS64* pe::nt_headers()
{
	return reinterpret_cast<IMAGE_NT_HEADERS*>(buffer.data() + dos_header()->e_lfanew);
}

DWORD pe::get_certificate_offset()
{
	return nt_headers()->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress;
}

DWORD pe::get_certificate_size()
{
	return nt_headers()->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size;
}

void pe::set_certificate_offset(DWORD offset)
{
	nt_headers()->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].VirtualAddress = offset;
}

void pe::set_certificate_size(DWORD size)
{
	nt_headers()->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_SECURITY].Size = size;
}

vector<uint8_t> pe::certificate()
{
	return vector<uint8_t>(&buffer[get_certificate_offset()], &buffer[get_certificate_offset() + get_certificate_size()]);
}

void pe::sign(vector<uint8_t>& cert)
{
	set_certificate_offset(buffer.size());
	set_certificate_size(cert.size());
	buffer.insert(buffer.end(), cert.begin(), cert.end());
}

void pe::save_to_file(string_view file_name)
{
	util::buffer_to_file(buffer, file_name);
}
