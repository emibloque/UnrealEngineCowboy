#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CowboyPlayer.h"
#include "AIEnemyController.generated.h"

UCLASS()
class COWBOYCORE_API AAIEnemyController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	ACowboyPlayer* TargetPlayer;

	void FollowPlayer();
	void OnMovementProcessed(UPathFollowingComponent* Component, FVector& Velocity);
	void OnFollowCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
};