#include <Memory.hpp>
#include <iterator>

void Memory::set(uintptr_t address, uint8_t value, size_t size)
{
	DWORD dwOldProtection;
	VirtualProtect(reinterpret_cast<void*>(address), size, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	memset(reinterpret_cast<void*>(address), value, size);
	VirtualProtect(reinterpret_cast<void*>(address), size, dwOldProtection, &dwOldProtection);
}

void Memory::writeByteArray(uintptr_t address, std::vector<uint8_t> arrayOfBytes)
{
	DWORD dwOldProtection;
	auto sizeOfArray = std::size(arrayOfBytes);
	VirtualProtect(reinterpret_cast<void*>(address), sizeOfArray, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	for (size_t i = 0; i < sizeOfArray; i++)
		*reinterpret_cast<uint8_t*>(address + i) = arrayOfBytes[i];
	VirtualProtect(reinterpret_cast<void*>(address), sizeOfArray, dwOldProtection, &dwOldProtection);
}