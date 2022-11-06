#include "Enemy.h"
#include "AIEnemyController.h"
#include "Projectile.h"

AEnemy::AEnemy()
{
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	AIControllerClass = AAIEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (Cast<AProjectile>(OtherActor))
	{
		OtherActor->Destroy();
		Destroy();
	}
}