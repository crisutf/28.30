#include "pch.h"
#include "Client.h"

void ClientThread()
{
    while (true)
    {
        if (UWorld::GetWorld() && UWorld::GetWorld()->OwningGameInstance)
        {
            auto& LocalPlayers = UWorld::GetWorld()->OwningGameInstance->LocalPlayers;

            if (LocalPlayers.Num() > 0 && LocalPlayers[0] && LocalPlayers[0]->PlayerController)
            {
                auto PlayerController = (AFortPlayerControllerAthena*)LocalPlayers[0]->PlayerController;

                if (PlayerController && !PlayerController->CheatManager)
                {
                    PlayerController->CheatManager = (UFortCheatManager*)UGameplayStatics::SpawnObject(PlayerController->CheatClass.Get(), PlayerController);
                }
            }
        }

        Sleep(500);
    }
}

void Client::Init()
{
    auto Engine = UEngine::GetEngine();
    if (Engine && Engine->GameViewport)
    {
        Engine->GameViewport->ViewportConsole = (UConsole*)UGameplayStatics::SpawnObject(Engine->ConsoleClass, Engine->GameViewport);
    }

    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)ClientThread, nullptr, 0, nullptr);
}
