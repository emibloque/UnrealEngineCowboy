#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "Components/ArrowComponent.h"

#include "ShootingComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShoot);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COWBOYCORE_API UShootingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void Shoot();

	UPROPERTY(BlueprintAssignable)
	FOnShoot OnShoot;

	UPROPERTY(EditDefaultsOnly, Category = "Cowboy Shooting")
	float ShootingCooldownTime = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Cowboy Shooting")
	TSubclassOf<AProjectile> ProjectileClass;

private:
	float LastShootingTime = 0.f;
	UPROPERTY()
	TArray<UArrowComponent*> ShootingArrows;
};
