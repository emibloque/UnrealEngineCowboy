#pragma once

#include "CoreMinimal.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class COWBOYCORE_API AEnemy : public APawn
{
	GENERATED_BODY()

protected:
	AEnemy();

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UPROPERTY(EditDefaultsOnly)
	UFloatingPawnMovement* FloatingPawnMovement;
};