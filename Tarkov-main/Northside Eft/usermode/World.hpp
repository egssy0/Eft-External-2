#pragma once
#include "common.hpp"
#include "memory.hpp"

class World
{
private:
	struct list_info
	{
		int size;
		uintptr_t base;
	};
public:
	std::vector<uintptr_t> get_player_list()
	{
		std::vector<uintptr_t> return_list;

		uintptr_t list_ptr = driver.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0xA0);
		if (!list_ptr)
		{
			return return_list;

		}

		list_info info{};

		info.size = driver.read<int>(list_ptr + 0x18);
		info.base = driver.read<uintptr_t>(list_ptr + 0x10);
		if (!info.base || info.size > 200)
		{
			return return_list;

		}
		std::unique_ptr<uintptr_t> entities_buffer(new uintptr_t[info.size * sizeof(uintptr_t)]);

		/* read into the buffer */
		driver.read(info.base + 0x20, entities_buffer.get(), info.size * sizeof(uintptr_t));
		return_list = { entities_buffer.get(), entities_buffer.get() + (uintptr_t)info.size };
		return return_list;
	}

	std::vector<uintptr_t> get_extract_list()
	{
		std::vector<uintptr_t> return_list;

		uintptr_t list_ptr = driver.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x18);
		list_ptr = driver.read<uintptr_t>(list_ptr + 0x20);

		if (!list_ptr)
			return return_list;

		list_info info{};

		info.size = driver.read<int>(list_ptr + 0x18);

		if (info.size > 200)
			return return_list;

		std::unique_ptr<uintptr_t> entities_buffer(new uintptr_t[info.size * sizeof(uintptr_t)]);

		/* read into the buffer */
		driver.read(list_ptr + 0x20, entities_buffer.get(), info.size * sizeof(uintptr_t));
		return_list = { entities_buffer.get(), entities_buffer.get() + (uintptr_t)info.size };
		return return_list;
	}

	std::vector<uintptr_t> get_loot_list()
	{
		std::vector<uintptr_t> return_list;

		uintptr_t list_ptr = driver.read<uintptr_t>(reinterpret_cast<uintptr_t>(this) + 0x80); //loot done 
		list_ptr = driver.read<uintptr_t>(list_ptr + 0x10); // done

		if (!list_ptr)
			return return_list;

		int sz = driver.read<uint32_t>(list_ptr + 0x40);

		list_ptr = driver.read<uintptr_t>(list_ptr + 0x18);

		if (sz > 0xFFFFFF)
			return return_list;
		
		for (int i = 0; i < sz; i++)
		{
			return_list.push_back(driver.read<uintptr_t>(list_ptr + 0x30 + (i * 0x18)));
		}
		return return_list;
	}
};