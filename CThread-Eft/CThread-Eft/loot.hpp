#include <tuple>

#include "Director.hpp"

struct ItemInfo
{
	std::string id;
	std::string shortname;
	uint32_t price;
};

std::vector<ItemInfo> cached_item_list;

class LootItem
{
public:
	static bool query_item_id(std::string file_input, std::string id, std::string& short_name, uint32_t& price)
	{
		size_t offset = file_input.find(id);

		if (offset == std::string::npos)
			return false;

		offset = file_input.find("bsgId \" \,", offset) + 3;
		if (offset = file_input.find("bsgId \" \,", offset) + 3)
		{
			std::cout << "a";
		}
		size_t temp = file_input.find("shortName \" ,", offset);
		short_name = file_input.substr(offset, temp - offset);

		offset = file_input.find("avg24hPrice \"", temp) + 8;
		temp = file_input.find("},", offset) - 13;
		price = std::stoi(file_input.substr(offset, temp - offset));

		cached_item_list.push_back({ id, short_name, price });
		std::cout << offset;
		return true;
	}

	std::string get_name()
	{
		uintptr_t name_pointer = driver.read<uintptr_t>((uintptr_t)this + 0x50);
		const int name_size = driver.read<int>(name_pointer + 0x10) - 10;
		if (name_size < 3)
			return "Corpse";
		return driver.read_str(name_pointer, name_size);
	}

	std::string get_item_id()
	{
		uintptr_t name_pointer = driver.read<uintptr_t>((uintptr_t)this + 0x50);
		const int name_size = driver.read<int>(name_pointer + 0x80);
		return driver.read_str(name_pointer, name_size);
	}

	Vector3 get_position()
	{
		std::vector<std::uint64_t> monkey = { 0x10, 0x30, 0x30, 0x8, 0x28, 0x10 };
		auto transform = driver.read_chain<uintptr_t>((uint64_t)this, monkey);
		return Bone::get_transform_position(transform);
	}
};

class WorldLoot
{
public:
	uint32_t price;
	Vector2 location;
	std::string short_name;
	std::string id;
	float distance;
};

class Loot_List
{
public:
	std::vector<uintptr_t> loot_pointer_list{};
	std::vector<WorldLoot> world_loot_list;
} loot_list;
