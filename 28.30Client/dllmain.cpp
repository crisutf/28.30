// dllmain.cpp : Defines the entry point for the 28.30Client DLL application.
#include "pch.h"
#include "Client.h"
#include "../28.30/Offsets.h"
#include "../28.30/Options.h"

void Main()
{
    Sarah::Offsets::Init();

    // 1. Disable network encryption on the client
    UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"net.AllowEncryption 0", nullptr);

    // 2. Synchronize Iris replication setting with the GameServer
    *(bool*)(__int64(Sarah::Offsets::ImageBase) + 0x117E1128) = bIris;

    // 3. Suppress UI director logs
    UKismetSystemLibrary::ExecuteConsoleCommand(UWorld::GetWorld(), L"log LogFortUIDirector None", nullptr);

    // 4. Initialize console and client systems
    Client::Init();
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(Main).detach();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
