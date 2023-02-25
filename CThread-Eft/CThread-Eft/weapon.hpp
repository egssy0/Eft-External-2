#pragma once
#include "Director.hpp"

class ProceduralWeaponAnimation
{
private:
public:
	void set_no_recoil()
	{
		uintptr_t shot_effector = driver.read<uintptr_t>((uintptr_t)this + oShooting);
		driver.write<float>(shot_effector + oIntensity, 0.f);
	}


	void set_mask(int mask)
	{
		driver.write<int>((uintptr_t)this + oMask, mask);
	}

	void set_effectors()
	{
		uintptr_t breath_effector = driver.read<uintptr_t>((uintptr_t)this + 0x28);
		driver.write<float>(breath_effector + 0xa4, 0.f);
	}

	Vector3 get_fireport()
	{
		if (!reinterpret_cast<uintptr_t>(this))
			return {};

		uintptr_t fire_arm_controller = driver.read<uintptr_t>((uintptr_t)this + oFireArmController);
		uintptr_t transform = driver.read<uintptr_t>(fire_arm_controller + 0x88);
		transform = driver.read<uintptr_t>(transform + 0x10);
		return Bone::get_transform_position(transform);
	}

	void set_aim_speed(float speed)
	{
		driver.write<float>((uintptr_t)this + oAimSpeed, speed);
	}

	void SetWeaponRotation(Vector3 angle)
	{

		uintptr_t hands = driver.read<uintptr_t>((uintptr_t)this + 0x18);

		uintptr_t recoil = driver.read<uintptr_t>(hands + 0x40);

		driver.write<float>(recoil + 0x38, 0.f);
		driver.write<float>(recoil + 0x3c, 0.f);
		driver.write<Vector3>(recoil + 0x80, angle);
	}

	void handcont()
	{
		uintptr_t hands = driver.read<uintptr_t>((uintptr_t)this + 0x18);
	}
};
