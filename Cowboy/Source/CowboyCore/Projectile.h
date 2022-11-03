#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class COWBOYCORE_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	AProjectile();

	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* MovementComponent;
};