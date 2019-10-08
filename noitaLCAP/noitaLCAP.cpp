#include <Windows.h>
#include <map>
#include <cstdio>
#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <WinUser.h>

using namespace std;


DWORD noitaPID;
DWORD noitaSeed = 0x177712C;


int main()
{
	map<string, string> mat = {
		{"water", "Water (mat_water)"},
		{"water_ice", "Chilly Water (mat_water_ice)"},
		{"water_swamp", "Swamp (mat_water_swamp)"},
		{"oil", "Oil (mat_oil)"},
		{"alcohol", "Whiskey (mat_alcohol)"},
		{"swamp", "Swamp (mat_swamp)"},
		{"mud", "Mud (mat_mud)"},
		{"blood", "Blood (mat_blood)"},
		{"blood_fungi", "Fungus (mat_blood_fungi)"},
		{"blood_worm", "Worm Blood (mat_blood_worm)"},
		{"radioactive_liquid", "Toxic Sludge (mat_radioactive_liquid)"},
		{"cement", "Cement (mat_cement)"},
		{"acid", "Acid (mat_acid)"},
		{"lava", "Lava (mat_lava)"},
		{"urine", "Urine (mat_dont_bother)"},
		{"poison", "Glowing Liquid (mat_poison)"},
		{"magic_liquid_teleportation", "Teleportatium (mat_magic_liquid_teleportation)"},
		{"magic_liquid_polymorph", "Polymorphine (mat_magic_liquid_polymorph)"},
		{"magic_liquid_random_polymorph", "Chaotic Polymorphine (mat_magic_liquid_random_polymorph)"},
		{"magic_liquid_berserk", "Berserkium (mat_magic_liquid_berserk)"},
		{"magic_liquid_charm", "Pheromone (mat_magic_liquid_charm)"},
		{"magic_liquid_invisibility", "Invisiblium (mat_magic_liquid_invisibility)"},
		{"sand", "Sand (mat_sand)"},
		{"bone", "Bone (mat_bone)"},
		{"soil", "Soil (mat_soil)"},
		{"honey", "Honey (mat_honey)"},
		{"slime", "Slime (mat_slime_pink)"},
		{"snow", "Snow (mat_snow)"},
		{"rotten_meat", "Rotten Meat (mat_rotten_meat)"},
		{"wax", "Wax (mat_wax)"},
		{"gold", "Gold (mat_gold)"},
		{"silver", "Silver (mat_dont_bother_boogaloo)"},
		{"copper", "Copper (mat_copper)"},
		{"brass", "Brass (mat_brass)"},
		{"diamond", "Diamond (mat_diamond)"},
		{"coal", "Coal (mat_coal)"},
		{"gunpowder", "Gunpowder (mat_gunpowder)"},
		{"gunpowder_explosive", "Gunpowder (mat_gunpowder_explosive)"},
		{"grass", "Grass (mat_grass)"},
		{"fungi", "Fungus (mat_fungus)"}
	};
	int seed;


	//program runs until END key is pressed
	while (!(GetAsyncKeyState(VK_F12) & 0x0001)){
		//does shit when HOME key is pressed
		if(GetAsyncKeyState(VK_F4) & 0x0001)
		{
			//gets the active window's title and then uses that to get PID (too lazy to do it other way)
			//have noita active when pressing it
			HWND hWnd = GetForegroundWindow();
			GetWindowThreadProcessId(hWnd, &noitaPID);

			//reads seed and stores it in the seed variable
			HANDLE pHandle = OpenProcess(PROCESS_VM_READ, FALSE, noitaPID);
			ReadProcessMemory(pHandle, (LPVOID)noitaSeed, &seed, sizeof(seed), 0);
			
			//send this to super secret server uwu
			string cmd = "curl -s --get \"http://94.172.33.134:4921/noita?" + to_string(seed) + "&hey_you_reading_this_you_will_find_literally_nothing_and_just_waste_your_time\"";
			//fuck you cpp
			const char* fuck = cmd.c_str();


			array<char, 128> buffer;
			string result;
			unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(fuck, "r"), _pclose);
			if (!pipe) {
				throw runtime_error("popen() failed!");
			}
			while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
				result += buffer.data();
			}

			//clean response from server
			//cout << result << endl << endl << endl << endl;
			
			//splitting the response to use what we need
			//very messy please dont look i am embarrassed
			size_t pos = 0;
			int count = 0;
			string token;
			string token1;
			string token2;
			string token3;
			string token4;
			string token5;
			string token6;

			while ((pos = result.find(",")) != string::npos)
			{
				count++;
				token = result.substr(0, pos);
				if (count == 3)
					token1 = token;
				if (count == 4)
					token2 = token;
				if (count == 5)
					token3 = token;
				if (count == 7)
					token4 = token;
				if (count == 8)
					token5 = token;
				if (count == 9)
					token6 = token;
				result.erase(0, pos + 1);
			}

			while ((pos = token3.find(";")) != string::npos)
			{
				token = token3.substr(0, pos);
				token3 = token;
			}


			token6 = result;
			while ((pos = token6.find(";")) != string::npos)
			{
				token = token6.substr(0, pos);
				token6 = token;
			}

			cout << "LC:" << endl;
			cout << mat.find(token1)->second << endl;
			cout << mat.find(token2)->second << endl;
			cout << mat.find(token3)->second << endl;
			cout << "AP:" << endl;
			cout << mat.find(token4)->second << endl;
			cout << mat.find(token5)->second << endl;
			cout << mat.find(token6)->second << endl;

			string end = "LC:\n\n";
			end.append(mat.find(token1)->second);
			end.append("\n\n");
			end.append(mat.find(token2)->second);
			end.append("\n\n");
			end.append(mat.find(token3)->second);
			end.append("\n\n\n\n");
			end.append("AP:\n\n");
			end.append(mat.find(token4)->second);
			end.append("\n\n");
			end.append(mat.find(token5)->second);
			end.append("\n\n");
			end.append(mat.find(token6)->second);
			end.append("\n\n");

			MessageBoxA(NULL, end.c_str(), "LCAP", MB_OK | MB_SYSTEMMODAL);
		}
	}
	return 0;
}