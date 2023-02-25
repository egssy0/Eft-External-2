#include "Director.hpp"
#define Print std::cout << 
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

	std::cout << "Please Launch Eft\n";
	while (driver.get_pid() == NULL) {
		driver.set_pid("EscapeFromTarkov.exe");
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	Sleep(1000);

	PID = driver.get_pid();

	driver.get_module_base("UnityPlayer.dll");
	Unity = driver.get_base();
	driver.get_module_base("mono-2.0-bdwgc.dll");
	mono_dll_address = driver.get_base();
	if (!Unity)
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
		std::cout << _("Error 1");
		Sleep(3000);
		exit(3);
	}
	SetConsoleTitleA("CThread EFT");
	for (;;)
	{
		Print "CThread EFT";
	}

}