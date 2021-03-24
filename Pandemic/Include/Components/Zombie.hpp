#pragma once

#include <cstdint>

struct Zombie
{
    char pad_0000[388]; //0x0000
    int32_t health; //0x0184
    int32_t maxHealth; //0x0188
    char pad_018C[696]; //0x018C
};

namespace ZombieHandler
{
    const void oneShotZombies();
}

namespace ZombieOffsets
{
	const uintptr_t entityList = 0x017FBC84;
	const uintptr_t entityListIndexOffset = 0x8C;
	const uintptr_t fetchZombie(uint8_t index);
    const int32_t determineEntityListSize(int32_t players);
}