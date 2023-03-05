#pragma once
#include <Windows.h>
#include <iostream>


uintptr_t Game;
bool start = false;

const DWORD Local_Player = 0x1edb678;

const DWORD Cl_EntityList = 0x1b2a578;
const DWORD Local_Entity_Handle = 0x1352c7c;
const DWORD M_VecAbsOrigin = 0x014c;
const DWORD M_bConstrainBetweenEndpoints = 0x0f50; //m_nForceBone  0x0e88 + 0x48
const DWORD demfuckingBone = 0x0e98 + 0x48;
const DWORD ItemId = 0x1648;
const DWORD M_IName = 0x0589;
const DWORD m_scriptNameIndex = 0x0690;
const DWORD m_nSkin = 0x0e54;
const DWORD m_vecPunchWeapon_Angle = 0x24a8;
const DWORD ViewMatrix = 0x11a210;
const DWORD ViewRender = 0x7664e80;
const DWORD m_ammoPoolCapacity = 0x25a4;
const DWORD viewAngles = m_ammoPoolCapacity - 0x14;
const DWORD camera_origin = 0x1f48;
const DWORD M_ITeamNum = 0x044c; //updated 
const DWORD M_BleedOutState = 0x2738; //updated
const DWORD M_IWorldModelIndex = 0x1658; //updated
const DWORD Glow_Type = 0x2C4;
const DWORD Glow_Enabled = 0x3c8;
const DWORD Glow_Through_Walls = 0x3d0;
const DWORD m_highlightFunctionBits = 0x02c0; //item_glow //updated

const DWORD m_vecAbsVelocity = 0x0140;

const DWORD m_ActiveState = 0x166c; //updated

const DWORD CurrentWeapon = 0x1a14; //m_latestPrimaryWeapons //updated
const DWORD m_ammoInClip = 0x1644; //updated

const DWORD m_iHealth = 0x043c; //updated
const DWORD m_iMaxHealth = 0x0578; //updated 
const DWORD m_shieldHealth = 0x170; //updated
const DWORD m_shieldHealthMax = 0x0174; //updated
const DWORD CPlayerarmorType = 0x45bc; //updated

const DWORD m_flProjectileSpeed = 0x1ef0;
const DWORD m_flProjectileScale = 0x1ef8;
const DWORD OFFSET_ZOOM_FOV = 0x16b8 + 0xb8; //m_playerData + m_curZoomFOV
const DWORD m_thirdPersonShoulderView = 0x36c8; //updated 
const DWORD thirdperson_override = 0x01b0f000 + 0x6c; //updated
const DWORD m_playerMoveSpeedScale = 0x3214; //updated
const DWORD m_flModelScale = 0x0f08; //updated
const DWORD m_skydiveIsDiving = 0x46a8; //updated

const DWORD NameList = 0xbbda330;
const DWORD lastVisibleTime = 0x1a70;
const DWORD OFFSET_STUDIOHDR = 0x10f0;