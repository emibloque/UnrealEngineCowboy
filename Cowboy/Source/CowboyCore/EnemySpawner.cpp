
#include "EnemySpawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	SpawningArea = CreateDefaultSubobject<UBoxComponent>("SpawningArea");
	RootComponent = SpawningArea;
	SpawningArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemy();
}

void AEnemySpawner::SpawnEnemy()
{
	if (NumberOfEnemiesToSpawn != -1 && TotalEnemiesSpawned >= NumberOfEnemiesToSpawn)
	{
		return;
	}
	
	FVector RandomPoint = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(),
																	   SpawningArea->GetScaledBoxExtent());
	RandomPoint.Z = GetActorLocation().Z;

	const FRotator RandomRotation = FRotator(0.f, FMath::FRand() * 360.f, 0.f);

	GetWorld()->SpawnActor<AEnemy>(EnemyClass, RandomPoint, RandomRotation);
	TotalEnemiesSpawned++;

	GetWorld()->GetTimerManager().SetTimer(SpawnEnemyHandle, this, &ThisClass::SpawnEnemy, SpawnRate);
}