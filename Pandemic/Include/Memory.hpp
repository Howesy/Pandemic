#pragma once

#pragma once

#include <Windows.h>
#include <cstdint>
#include <vector>

namespace Memory
{
	template <class T>
	void write(uintptr_t address, T value)
	{
		DWORD dwOldProtection;
		VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), PAGE_EXECUTE_READWRITE, &dwOldProtection);
		*reinterpret_cast<T*>(address) = value;
		VirtualProtect(reinterpret_cast<void*>(address), sizeof(T), dwOldProtection, &dwOldProtection);
	}

	template <class T>
	T read(uintptr_t address)
	{
		return *reinterpret_cast<T*>(address);
	}

	void set(uintptr_t address, uint8_t value, size_t size);
	void writeByteArray(uintptr_t address, std::vector<uint8_t> arrayOfBytes);
}