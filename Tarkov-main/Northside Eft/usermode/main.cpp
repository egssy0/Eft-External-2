#include "common.hpp"
#include "memory.hpp"

#include "auth/skStr.h"
#include "auth/auth.hpp"

#include "drawing.hpp"
#include "features.hpp"
#include "drawing.hpp"
#include <fstream>
bool should_exit = true;
bool do_once = true;

void update_player_list()
{
	Player* return_player = NULL;
	pointers::world = (World*)pointers::GOM->get_game_world();
	if (pointers::world)
	{
		vars::players_list = pointers::world->get_player_list();

		if (vars::players_list.size() > 0)
		{
			for (auto& player : vars::players_list)
			{
				Player* current = (Player*)player;
				if (current->is_local_player())
				{
					return_player = current;
					break;
				}
			}
		}
	}
	local_player.player_class = return_player;
}

void cheat_entry()
{
	std::wifstream file; file.open("loot.json"); std::stringstream ss; ss << file.rdbuf(); vars::loot_values = ss.str();

	if (!file)
	{
		std::cout << "Cant Open Loot.json";
	}
	while (!should_exit)
	{
		Sleep(1);
	}

	Sleep(40);

	pointers::GOM = driver.read<GameObjectManager*>(pointers::unity_player + oGOM);
	mono::init_functions();

	if(!pointers::GOM)
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		std::cout << _("Error 2");
		Sleep(3000);
		exit(3);
	}

	std::chrono::steady_clock::time_point start = std::chrono::high_resolution_clock::now();

	while (true)
	{
		if (settings::is_in_raid)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(9));
			update_player_list();
			if (vars::players_list.size() < 0) continue;
			//if (!pointers::world) continue;
		//	if (exfil_list.exfil_pointer_list.size() > 0) continue;
			exfil_list.exfil_pointer_list = pointers::world->get_extract_list();
			if (exfil_list.exfil_pointer_list.size() > 0 && local_player.player_class)
			{
				if(local_player.player_class)
				loot_list.loot_pointer_list = pointers::world->get_loot_list();

				camera.object = pointers::GOM->get_fps_camera();

			//	if (!camera.object) continue;
				local_player.setup();
				//if (current_health < 0.1f);

				std::thread(features::runshit).detach();
				std::thread(features::loot_esp).detach();
				std::thread(features::extract_esp).detach();
				std::thread(features::esp).detach();
				

				auto stop = std::chrono::high_resolution_clock::now();
				if (std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() > 10)
				{
					start = std::chrono::high_resolution_clock::now();
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					std::thread(features::do_cham).detach();
				}
			}
			else
			{
				vars::drawing_list.clear();
				exfil_list.extract_info_list.clear();
				loot_list.world_loot_list.clear();
			}
		}
	}
}

/*void load_drv()
{
	if (!driver.is_mapped()) {
		HANDLE iqvw64e_device_handle = intel_driver::Load();
		if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE) {
			exit(3);
		}
		if (!kdmapper::MapDriver(iqvw64e_device_handle, b2)) {
			intel_driver::Unload(iqvw64e_device_handle);
		}
	}
}*/

int main()
{
	if (function.setup())
		std::cout << "[+] Function Setup Successful\n";

	if (!function.setup()) {
		driver.set_pid("EscapeFromTarkov.exe");
		if (driver.get_pid()) {
			exit(2);
		}
	}


	if (!driver.is_mapped()) { std::cout << "lol"; }
	else std::cout << ("[+] Driver Mapped | Loaded\n");

	std::cout << "Please Launch Squad\n";
	while (driver.get_pid() == NULL) {
		driver.set_pid("EscapeFromTarkov.exe");
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
	ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;

	Sleep(1000);

	vars::target_pid = driver.get_pid();

	driver.get_module_base("UnityPlayer.dll");
	pointers::unity_player = driver.get_base();
	driver.get_module_base("mono-2.0-bdwgc.dll");
	mono_dll_address = driver.get_base();
	if (!pointers::unity_player)
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		std::cout << _("Error 1");
		Sleep(3000);
		exit(3);
	}

	std::thread(cheat_entry).detach();
	std::thread(draw::Initialize).detach();

	while (true);
}