#include <Components/Zombie.hpp>
#include <Components/Player.hpp>
#include <Windows.h>
#include <iostream>

const uintptr_t ZombieOffsets::fetchZombie(uint8_t index)
{
	const uintptr_t moduleBaseAddress = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
	const uintptr_t zombieEntityList = moduleBaseAddress + ZombieOffsets::entityList;
	return *reinterpret_cast<uintptr_t*>((zombieEntityList + (index * ZombieOffsets::entityListIndexOffset)));
}

//For solo players, a total of 24 zombies can spawn at a single time.
//For each player added, it adds a total of 6 zombies to the entity list.
const int32_t ZombieOffsets::determineEntityListSize(int32_t players)
{
	const int32_t initialEntityListSize = 24;
	return (initialEntityListSize + ((players - 1) * 6));
}

const void ZombieHandler::oneShotZombies()
{
	PlayerList playerList = PlayerHandler::populatePlayerList();
	int32_t lobbySize = PlayerHandler::determineLobbySize(playerList);
	const int32_t entityListSize = ZombieOffsets::determineEntityListSize(lobbySize);
	for (auto i = 0; i < entityListSize; i++)
	{
		const uintptr_t zombiePointer = ZombieOffsets::fetchZombie(i);
		if (zombiePointer != NULL)
		{
			const auto zombie = reinterpret_cast<Zombie*>(zombiePointer);
			zombie->health = 0;
		}
	}
}