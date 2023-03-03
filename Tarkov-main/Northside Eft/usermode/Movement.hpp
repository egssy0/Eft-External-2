#include "common.hpp"
#include "math.hpp"
#include "memory.hpp"

class Movement
{
public:
	Vector2 get_va()
	{
		return driver.read<Vector2>((uintptr_t)this + 0x234);
	}

	void set_va(Vector2 angles)
	{
		driver.write<Vector2>((uintptr_t)this + 0x234, angles);
	}
};