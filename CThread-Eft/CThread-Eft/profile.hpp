#pragma once
#include "Director.hpp"

class Profile
{
private:
public:
    std::string get_name()
    {
        uintptr_t info = driver.read<uintptr_t>((uintptr_t)this + oInfo);
        uintptr_t namePtr = driver.read<uintptr_t>(info + 0x10);
        return driver.read_wstr(namePtr + 0x14);
    }

    std::string get_role()
    {
        uintptr_t player_info = driver.read<uintptr_t>((uintptr_t)this + oInfo);

        uint32_t registration_date = driver.read<uint32_t>(player_info + oRegistrationDate);

        uint32_t side = driver.read<uint32_t>(player_info + oSide);

        uintptr_t settings = driver.read<uintptr_t>(player_info + oSettings);

        uint32_t role = driver.read<uint32_t>(settings + 0x10);

        if (registration_date > 0 && (side == 1 || side == 2))
            return this->get_name();
        else if (registration_date > 0 && side == 4)
            return _("Player Scav");
        else
        {
            switch (role)
            {
            case 1:
                return _("Sniper Scav");
                break;
            case 2:
                return _("Ai Scav");
                break;
            case 8:
                return _("Reshala");
                break;
            case 16:
                return _("Follower");
                break;
            case 32:
                return _("Reshala Demon");
                break;
            case 64:
                return _("Killa");
                break;
            case 128:
                return _("Shturman");
                break;
            case 256:
                return _("Shturman Demon");
                break;
            case 512:
                return _("Raider");
                break;
            case 1024:
                return _("Cultist");
                break;
            case 2048:
                return _("Gluhar");
                break;
            case 4096:
                return _("Gluhar Demon");
                break;
            case 8192:
                return _("Gluhar Demon");
                break;
            case 16384:
                return _("Gluhar Demon");
                break;
            case 32768:
                return _("Gluhar Demon");
                break;
            case 65536:
                return _("Sanitar Demon");
                break;
            case 131072:
                return _("Sanitar");
                break;
            case 524288:
                return _("Raider");
                break;
            case 4194304:
                return _("Tagilla");
                break;
            case 536870912:
                return _("Zryachiy");
                break;
            case 1073741824:
                return _("Follower Zryachiy");
                break;
            default:
                return _("Not Valid");
                break;
            }
        }
    }
};
