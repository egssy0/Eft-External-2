#pragma once 

#include "common.hpp"
#include "memory.hpp"
#include "GameObjectManager.hpp"
#include "World.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "ExfiltrationPoint.hpp"
#include "Loot.hpp"
#include "mono.hpp"
Vector3 Leg1; // left leg
Vector3 Leg2; // right leg
Vector3 Dickarea; //dick area 
Vector3 Neck; // neck
Vector3 Arm1; // left arm
Vector3 Arm2; //right arm
Vector3 L2;
Vector3 R2;
Vector3 ArmL;
Vector3 ArmR;
Vector3 FootL;
Vector3 FootR;


struct Player_Info
{
	std::string type;
	int distance;
	float health;
};
float fov = 100.0f;
struct Draw_Info
{
	Vector2 Head_Position;
	Vector2 Skeleton_Head_position;

	Vector2 Neck;

	Vector2 Left_Upper_Arm;
	Vector2 Right_Upper_Arm;
	Vector2 Left_Forearm;
	Vector2 Right_Forearm;

	Vector2 Pevlis;
	Vector2 Right_Leg;
	Vector2 Left_Leg;
	Vector2 Right_Leg2;
	Vector2 Left_Leg2;
	Vector2 Left_Foot;
	Vector2 Right_Foot;
	Vector2 Base_Position;
	Player_Info p_info;
};

struct Aim_Target_Info
{
	Vector2 FirePortPos;
	Vector2 PlayerPos;
};

namespace vars
{
	std::string loot_values;
	uint32_t target_pid;
	Player* aim_player;
	Aim_Target_Info target_info;
	std::vector<uintptr_t> players_list{};
	std::vector<Draw_Info> drawing_list;
}

namespace pointers
{	
	Matrix4x4* view_matrix_pointer;
	uintptr_t unity_player;
	GameObjectManager* GOM;
	World* world;
	Camera* camera;
}
float healthr;
float healthg;

float healthb;
namespace settings 
{
	bool corpse;
	bool is_in_raid = true;
	bool phase;
	bool is_no_visor;
	bool is_thermal_vision;
	bool chanfov;
	bool is_chams;
	bool is_esp = true;
	bool is_aimbot;
	bool snaplinesnigga;
	bool is_infinite_stamina;
	bool is_no_recoil;
	bool is_no_spread;
	bool silent;
	bool is_instant_aim;
	bool corner;
	bool is_loot_thru_walls;
	bool skeleton;
	bool box;
	bool nightvision;

	namespace aim
	{
		float aim_fov = 300.f;
		bool enable_fov_circle;
		float max_distance = 200.f;
		Bone::bones aim_bone;
		Vector3 aim_circle_color{ 1,1,1 };
	}

	namespace esp
	{
		bool show_aim_line;
		bool show_role;
		bool show_distance;
		bool show_health;
		bool show_extracts;
		bool is_loot_esp = false;
		float max_distance = 200.f;
		Vector3 box_color{ 1,1,1 };
		namespace loot_esp
		{
			float min_price = 10000.f;
			float max_distance = 200.f;
			Vector3 loot_color{ .29, .35, .73 };
		}
	}
}

namespace keybinds
{
}