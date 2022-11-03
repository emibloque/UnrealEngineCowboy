#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class COWBOYCORE_API AEnemySpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/* Area within where enemies will be spawned */
	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	UBoxComponent* SpawningArea;
	
	
	/* Class of enemies to be spawned */
	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	TSubclassOf<AEnemy> EnemyClass = AEnemy::StaticClass();

	/* Time in seconds between enemy spawns */
	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	float SpawnRate = 1.f;

	/* Amount of enemies to be spawned. If -1, infinite enemies will be spawned */
	UPROPERTY(EditAnywhere, Category = "Enemy Spawner")
	int32 NumberOfEnemiesToSpawn = -1;

	int32 TotalEnemiesSpawned = 0;

private:
	void SpawnEnemy();
	
	FTimerHandle SpawnEnemyHandle; 
};