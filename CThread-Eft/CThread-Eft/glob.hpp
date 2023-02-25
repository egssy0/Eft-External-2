#pragma once
#include "Director.hpp"


uintptr_t Unity;
uintptr_t mono_dll_address;
ULONG PID;

#define oGOM 0x17FFD28

#define oIsLocalPlayer 0x837 // done
#define oPhysical 0x530// done
#define oWeaponAnimation 0x1A0 // done
#define oIsDead 0x6e0 // done
#define oProfile 0x520 // done
#define oPlayerBody 0xA8 // done
#define oMovement 0x40 // done

#define oStamina 0x38 // done
#define oHandStamina 0x538 // done

#define oShooting 0x48 // done
#define oMask 0x118 // donee
#define oIntensity 0x78 // done
#define oAimSpeed 0x1b8 //done
#define oFireArmController 0x18 // done

#define oCurrent 0x48 //done

#define oInfo 0x28 //done

#define oRegistrationDate 0x74 // done
#define oSettings 0x50
#define oSide 0x70 //done

#define oAngle 0x234 //done

#define oHealthController 0x558
#define oHealthBody 0x58