#include "memory.hpp"
#include "common.hpp"
#include "Aimbot.hpp"
#include "drawing.hpp"
Vector3 BasePosition;

namespace features
{

	void runshit()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (settings::is_infinite_stamina)
		{
			local_player.physical_class->set_stamina(100.f);


		}

		if (settings::chanfov)
		{
			driver.write(camera.object + 0x15c, fov);
		}

		if (settings::is_no_visor)
		{
			uint64_t visor_effect = driver.GetComponentFromGameObject(camera.object, "VisorEffect");
			if (!visor_effect)
			{
				std::cout << "Visor Not Working";
			}
			driver.write<bool>(visor_effect + 0xB8, 0);
	
		}

		if (!settings::is_no_visor)
		{
			uint64_t visor_effect = driver.GetComponentFromGameObject(camera.object, "VisorEffect");
			if (!visor_effect)
			{
				std::cout << "Visor Not Working";
			}
			driver.write<bool>(visor_effect + 0xB8, 1);

		}



		if (settings::is_thermal_vision)
		{
			uint64_t thermal_effect = driver.GetComponentFromGameObject(camera.object, "ThermalVision");
			if (!thermal_effect)
			{
				std::cout << "Thermal Not Working";
			}
			uint64_t ThermalEnable = driver.read<uint64_t>(thermal_effect + 0x28);
			driver.write<bool>(thermal_effect + 0xE0, 1);
			driver.write<bool>(thermal_effect + 0xE1, 0);
			driver.write<bool>(thermal_effect + 0xE2, 0);
			driver.write<bool>(thermal_effect + 0xE3, 0);
			driver.write<bool>(thermal_effect + 0xE4, 0);
			driver.write<bool>(thermal_effect + 0xE5, 0);
		}

		if (!settings::is_thermal_vision)
		{
			uint64_t thermal_effect = driver.GetComponentFromGameObject(camera.object, "ThermalVision");
		
			driver.write<bool>(thermal_effect + 0xE0, 0);
		
		}
		

		if (settings::nightvision)
		{
			uint64_t night = driver.GetComponentFromGameObject(camera.object, "NightVision");

			driver.write<bool>(night + 0xE4, 1);
		}

		if (!settings::nightvision)
		{
			uint64_t night = driver.GetComponentFromGameObject(camera.object, "NightVision");

			driver.write<bool>(night + 0xE4, 0);
		}
		if (settings::is_no_recoil)
		{
			local_player.weapon_class->set_no_recoil();
		}
		if (settings::is_no_spread)
		{
			local_player.weapon_class->set_effectors();
			local_player.weapon_class->set_mask(16);
		}
		else
		{
			local_player.weapon_class->set_mask(127);
		}

		if (settings::is_aimbot)
		{
			Aim::find_target();
			if (GetAsyncKeyState(VK_RBUTTON))
			{
				Aim::do_aim();
			}
		}

		if (settings::silent)
		{
			Aim::find_target();
			if (GetAsyncKeyState(VK_RIGHT))
			{
				local_player.weapon_class->SetWeaponRotation(Vector3(BasePosition.x, BasePosition.y, BasePosition.z));
			}
		}

		if (settings::is_instant_aim)
		{
			local_player.weapon_class->set_aim_speed(10);
		}

		if (settings::is_loot_thru_walls)
		{
			static auto eft_hard_settings = driver.read<uint64_t>(mono::find_class(("Assembly-CSharp"), ("EFTHardSettings"))->get_vtable(mono::get_root_domain())->get_static_field_data());
			if (eft_hard_settings)
				if (driver.read<float>(eft_hard_settings + 0x1F4) != 4.f)
					driver.write<float>(eft_hard_settings + 0x1F4, 4.f);

			static auto game_world_instance = mono::find_class(("Assembly-CSharp"), ("EFT.GameWorld"))->get_vtable(mono::get_root_domain())->get_static_field_data();
			if (game_world_instance)
				if (driver.read<int>(game_world_instance + 0x14) != 0)
					driver.write<int>(game_world_instance + 0x14, 0);
		}

	}
	
		
	
		

	

	
	void do_cham()
	{
		if (settings::is_chams)
		{
			for (auto& player : vars::players_list)
			{
				Player* current = (Player*)player;

				if (current != local_player.player_class)
				{
					current->write_chams();
				}
			}
		}
	}

	
	

	void loot_esp()
	{
		if (settings::esp::is_loot_esp)
		{
			std::vector<WorldLoot> temp;
			std::cout << "\nSize: " << loot_list.loot_pointer_list.size();
			for (auto& loot : loot_list.loot_pointer_list)
			{
				bool cached = false;
				LootItem* current = (LootItem*)loot;

				WorldLoot item;

				Vector3 position = current->get_position();

				float distance = Calc3D_Dist(position, local_player.position);
				if (distance > settings::esp::loot_esp::max_distance)
					continue;

				Vector2 ScreenPos;
				if (!world_to_screen(position, ScreenPos))
					continue;
				draw::DrawCross(ScreenPos.x, ScreenPos.y, 2, 2, ImColor(255, 0, 0));
				std::string id = current->get_name();
				std::string shortname;
				uint32_t price;
			
				if (id == "Corpse")
				{
					item.short_name = "Corpse";
					item.location = ScreenPos;
					item.price = 0;
					item.distance = (int)distance;
					temp.push_back(item);
					continue;
				}

				for (auto& entry : cached_item_list)
				{
					if (entry.id == id)
					{
						cached = true;
						shortname = entry.shortname;
						price = entry.price;
					}
				}

				if (!cached)
				{
					if (!LootItem::query_item_id(vars::loot_values, id, shortname, price))
						continue;
				}

				if (price < settings::esp::loot_esp::min_price)
					continue;

				item.price = price;
				item.short_name = shortname;
				item.location = ScreenPos;
				item.id = id;
				item.distance = (int)distance;
				temp.push_back(item);
			}
			loot_list.world_loot_list = std::move(temp);
		}
	}

	void extract_esp()
	{
		if (settings::esp::show_extracts)
		{
			std::vector<Extract_Info> temp;
			for (auto& extract : exfil_list.exfil_pointer_list)
			{
				ExfiltrationPoint* current = (ExfiltrationPoint*)extract;

				Vector3 pos = current->get_position();
				Vector2 screen_pos;

				float distance = Calc3D_Dist(pos, local_player.position);

				if (!world_to_screen(pos, screen_pos))
					continue;

				Extract_Info info;
				info.name = current->get_name();
				info.distance = distance;
				info.screen_pos = screen_pos;
				temp.push_back(info);
			}
			exfil_list.extract_info_list = std::move(temp);
		}
		else
		{
			exfil_list.extract_info_list.clear();
		}
	}

	void esp()
	{
		if (settings::is_esp)
		{
			std::vector<Draw_Info> temp_list;

			for (auto& player : vars::players_list)
			{
				Player* current = (Player*)player;

				if (current == local_player.player_class)
					continue;

				Vector3 HeadPosition = current->get_position(Bone::bones::HumanHead);
				HeadPosition.y += 0.25;
				BasePosition = (current->get_position(Bone::bones::HumanLFoot) + current->get_position(Bone::bones::HumanRFoot)) / 2;
				Vector2 HeadScreenPosition;
				Vector2 BaseScreenPosition;
			
				
				if (!world_to_screen(HeadPosition, HeadScreenPosition) || !world_to_screen(BasePosition, BaseScreenPosition))
					continue;

				Draw_Info info;
				Player_Info playerInfo;

				playerInfo.type = current->get_profile()->get_role();
				playerInfo.distance = (int)Calc3D_Dist(local_player.position, HeadPosition);
				if (playerInfo.distance > settings::esp::max_distance)
					continue;

				if (settings::esp::show_health)
					playerInfo.health = current->get_health();


				if (settings::skeleton)
				{
					L2 = current->get_position(Bone::bones::HumanLThigh2);

					R2 = current->get_position(Bone::bones::HumanRThigh2);

					Head = current->get_position(Bone::bones::HumanHead);
					Leg1 = current->get_position(Bone::bones::HumanRThigh1);
					Leg2 = current->get_position(Bone::bones::HumanLThigh1);
					Dickarea = current->get_position(Bone::bones::HumanPelvis);
					Neck = current->get_position(Bone::bones::HumanNeck);
					Arm1 = current->get_position(Bone::bones::HumanLUpperarm);

					Arm2 = current->get_position(Bone::bones::HumanRUpperarm);
					ArmR = current->get_position(Bone::bones::HumanRForearm1);
					ArmL = current->get_position(Bone::bones::HumanLForearm1);
					FootR = current->get_position(Bone::bones::HumanRFoot);
					FootL = current->get_position(Bone::bones::HumanLFoot);
					world_to_screen(Head, info.Skeleton_Head_position);

					world_to_screen(Leg1, info.Right_Leg);
					world_to_screen(Leg2, info.Left_Leg);
					world_to_screen(R2, info.Right_Leg2);
					world_to_screen(L2, info.Left_Leg2);

					world_to_screen(Dickarea, info.Pevlis);

					world_to_screen(Neck, info.Neck);

					world_to_screen(Arm1, info.Left_Upper_Arm);
					world_to_screen(Arm2, info.Right_Upper_Arm);
					world_to_screen(ArmR, info.Right_Forearm);
					world_to_screen(ArmL, info.Left_Forearm);

					world_to_screen(FootR, info.Right_Foot);
					world_to_screen(FootL, info.Left_Foot);
				}


				info.Head_Position = HeadScreenPosition;
				info.Base_Position = BaseScreenPosition;
				info.p_info = playerInfo;

				temp_list.push_back(info);
			}
			vars::drawing_list = std::move(temp_list);

			if (settings::esp::show_aim_line && vars::aim_player)
			{
				Vector3 AimPos = vars::aim_player->get_position(settings::aim::aim_bone);
				Vector3 PlayerPos = local_player.fireport_position;

				Vector2 AimSPos;
				Vector2 PlayerSPos;

				world_to_screen(AimPos, AimSPos);
				world_to_screen(PlayerPos, PlayerSPos);

				vars::target_info.FirePortPos = PlayerSPos;
				vars::target_info.PlayerPos = AimSPos;
			}
			else
			{
				vars::target_info.FirePortPos = {};
				vars::target_info.PlayerPos = {};
			}
		}
	}
}