#include "ShootingComponent.h"

void UShootingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastShootingTime = GetWorld()->GetTimeSeconds() - ShootingCooldownTime;

	if (GetOwner())
	{
		const auto Arrows = GetOwner()->GetComponentsByTag(UArrowComponent::StaticClass(), FName("ShootingArrow"));
		for (const auto& Arrow : Arrows)
		{
			ShootingArrows.Add(Cast<UArrowComponent>(Arrow));
		}
	}
}

void UShootingComponent::Shoot()
{
	if (!ProjectileClass) return;

	if (LastShootingTime > GetWorld()->GetTimeSeconds() + ShootingCooldownTime) return;

	LastShootingTime = GetWorld()->GetTimeSeconds();

	for (const auto& Arrow : ShootingArrows)
	{
		GetWorld()->SpawnActor<AProjectile>(ProjectileClass,
											Arrow->GetComponentLocation(),
											Arrow->GetComponentRotation());
	}

	OnShoot.Broadcast();
}
