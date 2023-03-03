#pragma once
#include "common.hpp"
#include "memory.hpp"
#include "offsets.hpp"

class Physical
{
private:
public:
	void set_stamina(float value)
	{
		uintptr_t body_stamina =driver.read<uintptr_t>((uintptr_t)this + oStamina);
		uintptr_t hand_stamina =driver.read<uintptr_t>((uintptr_t)this + oHandStamina);
		driver.write<float>(body_stamina + 0x48, value);
		driver.write<float>(hand_stamina + 0x48, value);
	}
};
