#include "library.h"
#include <windows.h>
#include <iostream>

// Generated using ReClass 2016

struct Vector3
{
    float x, y, z;
};

struct Vector2
{
    float x, y;
};

class soldier;
class weapon;

class soldier
{
public:
    DWORD vTable; //0x0000
    Vector3 head; //0x0004
    char pad_0x0010[0x24]; //0x0010
    Vector3 position; //0x0034
    Vector2 aimCoords; //0x0040
    char pad_0x0048[0x14]; //0x0048
    float crouch; //0x005C
    char pad_0x0060[0x8]; //0x0060
    __int32 jumping; //0x0068
    char pad_0x006C[0x4]; //0x006C
    __int32 notMoving; //0x0070
    char pad_0x0074[0x84]; //0x0074
    __int32 health; //0x00F8
    char pad_0x00FC[0x128]; //0x00FC
    unsigned char blankByte; //0x0224
    char name[16]; //0xB45888
    char pad_0x0235[0xF7]; //0x0235
    __int32 team; //0x032C
    char pad_0x0330[0x44]; //0x0330
    weapon* currentWeapon; //0x0374
    char pad_0x0378[0x1C]; //0x0378

}; //Size=0x0394

class weapon
{
public:
    char pad_0x0000[0x8]; //0x0000
    soldier* owner; //0x0008
    int* name; //0x000C
    int* ammo; //0x0010
    int* clip; //0x0014
    int* wait; //0x0018
    __int32 shotsFired; //0x001C
    __int32 reloading; //0x0020
    char pad_0x0024[0x20]; //0x0024

}; //Size=0x0044



struct EntList
{
    soldier * ents[31];
};

bool IsValidEnt(soldier* ent)
{
    if (ent)
    {
        if (ent->vTable == 0x4E4A98 || ent->vTable == 0x4E4AC0)
        {
            return true;
        }
    }
    return false;
}




int * numOfPlayers = (int*)(0x50f500);
soldier * localPlayer = *(soldier**)0x50F4F4;
EntList * entList = *(EntList**)0x50F4F8;

DWORD __stdcall hackthread(void* param)
{

    FILE *pFile = nullptr;
    AllocConsole();
    freopen_s(&pFile, "CONOUT$", "w", stdout);

    while (!GetAsyncKeyState(VK_F3))
    {
        for (int i = 0; i < (*numOfPlayers); i++)
        {
            if (entList && IsValidEnt(entList->ents[i]))
            {
                std::cout << entList->ents[i]->name << std::endl;

            }
        }
        Sleep(100);
    }
//    system ("CLS");
    std::cout << "good to exit" << std::endl;
    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)param, NULL);
    return NULL;
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH:
            CreateThread(0, 0, hackthread, hModule, 0, 0);
            break;

        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}