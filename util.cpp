#include "util.hpp"
using namespace std;

namespace util
{
	vector<uint8_t> file_to_buffer(string_view file)
	{
		auto input = ifstream(file.data(), ios_base::binary);
		return vector<uint8_t>(istreambuf_iterator<char>(input), istreambuf_iterator<char>());
	}

	void buffer_to_file(vector<uint8_t>& buffer, string_view file_name)
	{
		auto out = ofstream(file_name.data(), ios_base::binary);
		out.write(reinterpret_cast<char*>(buffer.data()), buffer.size());
		out.close();
	}

	HKEY open_registry_key(string_view key)
	{
		HKEY result;
		RegOpenKeyExA(
			HKEY_LOCAL_MACHINE,
			key.data(),
			0,
			KEY_ALL_ACCESS,
			&result
		);
		return result;
	}

	string get_reg_entry(HKEY key, string_view entry_name)
	{
		char buffer[512];
		DWORD buffer_size = sizeof(buffer);
		RegQueryValueExA(key, entry_name.data(), 0, NULL, (LPBYTE)buffer, &buffer_size);
		return buffer;
	}

	void set_reg_entry(HKEY key, string_view entry_name, string_view data)
	{
		RegSetValueExA(key, entry_name.data(), NULL, REG_SZ, (const BYTE*)data.data(), data.size() + 1);
	}

	string get_temp_path_of_file(string filename)
	{
		char buffer[MAX_PATH];
		GetTempPathA(MAX_PATH, buffer);

		string path = buffer + filename;
		return path;
	}

	string generate_guid()
	{
		GUID guid = { 0 };
		char szGuid[40] = { 0 };
		CoCreateGuid(&guid);
		sprintf_s(szGuid, "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

		return szGuid;
	}
}