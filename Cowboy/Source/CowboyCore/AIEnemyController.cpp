#include "AIEnemyController.h"
#include "Kismet/GameplayStatics.h"

void AAIEnemyController::BeginPlay()
{
	Super::BeginPlay();

	TargetPlayer = Cast<ACowboyPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACowboyPlayer::StaticClass()));

	GetPathFollowingComponent()->PostProcessMove.BindUObject(this, &ThisClass::OnMovementProcessed);
	GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &ThisClass::OnFollowCompleted);
	FollowPlayer();
}

void AAIEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	FollowPlayer();
}

void AAIEnemyController::FollowPlayer()
{
	if (TargetPlayer && GetPawn())
	{
		MoveToActor(TargetPlayer, -1.f, false);
	}
}

void AAIEnemyController::OnMovementProcessed(UPathFollowingComponent* Component, FVector& Velocity)
{
	FVector Direction = Velocity;
	Direction.Z = 0.f;
	GetPawn()->SetActorRotation(Direction.Rotation());
}

void AAIEnemyController::OnFollowCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	FollowPlayer();
}