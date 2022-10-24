#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FCowboyCore : public IModuleInterface
{
private:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};