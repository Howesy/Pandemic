#pragma once

#include <cstdint>
#include <vector>

class Player
{
	char pad_0000[160];
	int32_t points;
	int32_t kills;
	char pad_00A8[24];
	int32_t downs;
	int32_t headshots;
	char pad_00C8[132];
public:
	uintptr_t get();
	Player(uintptr_t player);
	void setPoints(int32_t value);
	void setKills(int32_t value);
	void setHeadshots(int32_t value);
	void setDowns(int32_t value);
	void maxOutStats();
	void initiateSuperSpeed();
	void initiateGodMode();
	void initiateInfiniteAmmo();
	void initiateNoclip();

private:
	uintptr_t player;
};

struct PlayerList
{
	Player* localPlayer;
	std::vector<Player*> players;
	void maxAllPlayerStats();
};

namespace PlayerHandler
{
	PlayerList populatePlayerList();
	int32_t determineLobbySize(PlayerList playerList);
	static bool godMode = false;
	static bool infiniteAmmo = false;
	static bool noclip = false;
}

namespace PlayerOffsets
{
	const uintptr_t entityList = 0x1C0A628;
	const uintptr_t entityListIndexOffset = 0x1D28;
	const uintptr_t playerHealth = 0x007DADD0;
	const uintptr_t playerAmmo = 0x00697A10;
	const uintptr_t playerNoclip = 0x1C0A74C;
	const uintptr_t playerModifiers = 0x01801810;
	const uintptr_t playerSpeedOffset = 0x18;
	const uintptr_t fetchPlayer(uint8_t index);
}

namespace PlayerOriginalBytes
{
	const static std::vector<uint8_t> godMode = { 0x89, 0x85, 0x84, 0x01, 0x00, 0x00 };
	const static std::vector<uint8_t> ammo = { 0x89, 0x50, 0x4 };
}