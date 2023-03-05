#include "memory.h"
#include <Windows.h>
#include "glob.h"


uintptr_t GetEntityById(int Ent)
{
    uintptr_t EntityList = memory::read<uintptr_t>(Game + 0x1b37a78);
    uintptr_t BaseEntity = memory::read<uintptr_t>(EntityList);
    if (!BaseEntity)
        return NULL;
    return memory::read(EntityList + (Ent << 5));
}

struct GlowMode
{
    int8_t GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};
DWORD64 GetWeapon(DWORD64 entity)
{
    DWORD64 WeaponHandle = memory::read<DWORD64>(entity + 0x1a1c);
    WeaponHandle &= 0xffff;
    return memory::read<DWORD64>(Game + 0x1b37a78 + (WeaponHandle << 5));
}

void Being()
{
       for (int i = 1; i < 400; i++)
       {
           //if (i < 1) continue;
         //  if (1 < 0) continue;
           uintptr_t LocalPlayer = memory::read<uintptr_t>(Game + 0x1388eb8); // LocalPlayer
           
          
           if (LocalPlayer == NULL) continue;
           uintptr_t Entity = GetEntityById(i);

           std::cout << std::hex << Entity;
          if (LocalPlayer == Entity) continue;
         //  uintptr_t LocalPlayerWeapon = GetWeapon(LocalPlayer);
          // if (LocalPlayerWeapon == NULL) continue;
         memory::write<int>(Entity + 0x03c0 + 0x8, 1); // glow enable: 1 = enabled, 2 = disabled
           memory::write<int>(Entity + 0x03c0 + 0x10, 2); // glow through walls: 2 = enabled, 5 = disabled
       memory::write<GlowMode>(Entity + 0x2c0, { 101,101,90,100 }); // glow type: GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
           memory::write<float>(Entity + 0x1D0, 0.0f);
           memory::write<float>(Entity + 0x1D4, 155.0f);
           memory::write<float>(Entity + 0x1D8, 255.0f);
          // memory::write<int>(LocalPlayerWeapon + 0x0e54, 10);
           
       }
   
}   