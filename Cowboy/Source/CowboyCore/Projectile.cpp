#include "Projectile.h"

AProjectile::AProjectile()
{
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
}