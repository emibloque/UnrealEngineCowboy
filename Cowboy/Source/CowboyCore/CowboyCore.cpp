#include "CowboyCore.h"
#include "Modules/ModuleManager.h"


void FCowboyCore::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("CowboyCore module starting up"));

}

void FCowboyCore::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("CowboyCore module shutting down"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FCowboyCore, CowboyCore, "CowboyCore");