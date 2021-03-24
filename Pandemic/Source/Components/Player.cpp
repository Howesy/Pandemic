#include <Components/Player.hpp>
#include <Memory.hpp>
#include <Windows.h>
#include <cmath>

Player::Player(uintptr_t player)
{
	this->player = player;
}

uintptr_t Player::get()
{
	return this->player;
}

void Player::setPoints(int32_t value)
{
	this->points = value;
}

void Player::setKills(int32_t value)
{
	this->kills = value;
}

void Player::setHeadshots(int32_t value)
{
	this->headshots = value;
}

void Player::setDowns(int32_t value)
{
	this->downs = value;
}

void Player::maxOutStats()
{
	int32_t highStatValue = INT32_MAX - static_cast<int32_t>(pow(10, 5));
	this->setPoints(highStatValue);
	this->setKills(highStatValue);
	this->setHeadshots(highStatValue);
	this->setDowns(0);
}
//I need to test this function.
void Player::initiateGodMode()
{
	PlayerHandler::godMode = !PlayerHandler::godMode;

	if (PlayerHandler::godMode)
		Memory::set(PlayerOffsets::playerHealth, 0x90, 6);
	else
		Memory::writeByteArray(PlayerOffsets::playerHealth, PlayerOriginalBytes::godMode);
}
//I need to test this function.
void Player::initiateInfiniteAmmo()
{
	PlayerHandler::infiniteAmmo = !PlayerHandler::infiniteAmmo;

	if (PlayerHandler::infiniteAmmo)
		Memory::set(PlayerOffsets::playerAmmo, 0x90, 3);
	else
		Memory::writeByteArray(PlayerOffsets::playerAmmo, PlayerOriginalBytes::ammo);
}

void Player::initiateNoclip()
{
	PlayerHandler::noclip = !PlayerHandler::noclip;

	if (PlayerHandler::noclip)
		Memory::write(PlayerOffsets::playerNoclip, 1);
	else
		Memory::write(PlayerOffsets::playerNoclip, 0);
}

void Player::initiateSuperSpeed()
{
	const uintptr_t moduleBaseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
	const uintptr_t playerModifiers = *reinterpret_cast<uintptr_t*>(moduleBaseAddress + PlayerOffsets::playerModifiers);
	const uintptr_t playerSpeed = playerModifiers + PlayerOffsets::playerSpeedOffset;
	*reinterpret_cast<int32_t*>(playerSpeed) = 1000;
}

void PlayerList::maxAllPlayerStats()
{
	for (auto player : this->players)
		player->maxOutStats();
}

int32_t PlayerHandler::determineLobbySize(PlayerList playerList)
{
	int32_t placeholderCounter = 0;
	for (auto player : playerList.players)
		if (player->get() != NULL)
			placeholderCounter += 1;

	return placeholderCounter;
}

PlayerList PlayerHandler::populatePlayerList()
{
	PlayerList placeholderStruct;
	std::vector<Player*> placeholderVector;
	for (auto i = 0; i < 3; i++)
	{
		Player* player = reinterpret_cast<Player*>(PlayerOffsets::fetchPlayer(i));
		if (player != nullptr)
			placeholderVector.push_back(player);
	}
	placeholderStruct.localPlayer = placeholderVector.at(0);
	placeholderStruct.players = placeholderVector;
	return placeholderStruct;
}

const uintptr_t PlayerOffsets::fetchPlayer(uint8_t index)
{
	return (PlayerOffsets::entityList + (index * PlayerOffsets::entityListIndexOffset));
}