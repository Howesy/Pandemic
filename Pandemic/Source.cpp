#include <Windows.h>
#include <iostream>
#include <Components/Zombie.hpp>
#include <Components/Player.hpp>

void AllocateConsole(const char* consoleTitle)
{
	FILE* file;
	AllocConsole();
	freopen_s(&file, "CONOUT$", "w", stdout);
	SetConsoleTitleA(consoleTitle);
}

DWORD WINAPI DllEntry(LPVOID lpArgument)
{
	AllocateConsole("Pandemic");
	PlayerList playerList = PlayerHandler::populatePlayerList();
	playerList.maxAllPlayerStats();
	playerList.localPlayer->initiateSuperSpeed();
	playerList.localPlayer->initiateInfiniteAmmo();
	playerList.localPlayer->initiateGodMode();
	while (true)
		ZombieHandler::oneShotZombies();
	return 0;
}

BOOL APIENTRY DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DllEntry), nullptr, 0, nullptr);

	return TRUE;
}