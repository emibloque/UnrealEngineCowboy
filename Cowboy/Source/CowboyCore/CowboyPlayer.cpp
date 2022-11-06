#include "CowboyPlayer.h"

#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

ACowboyPlayer::ACowboyPlayer()
{
	bUseControllerRotationYaw = false;
	ShootingComponent = CreateDefaultSubobject<UShootingComponent>("ShootingComponent");
}

void ACowboyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ACowboyPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACowboyPlayer::MoveRight);
	InputComponent->BindAxis("RotateUp", this, &ACowboyPlayer::RotateUp);
	InputComponent->BindAxis("RotateRight", this, &ACowboyPlayer::RotateRight);
	InputComponent->BindAction("Shoot", IE_Pressed, ShootingComponent, &UShootingComponent::Shoot);
}

void ACowboyPlayer::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
							  bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse,
							  const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	if (Cast<AEnemy>(Other))
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
	}
}

void ACowboyPlayer::MoveForward(float Value)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ACowboyPlayer::MoveRight(float Value)
{
	const FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ACowboyPlayer::RotateUp(float Value)
{
	CurrentRotationDirection.X = Value;

	if (FMath::IsNearlyZero(Value)) return;
	SetActorRotation(CurrentRotationDirection.Rotation());
}

void ACowboyPlayer::RotateRight(float Value)
{
	CurrentRotationDirection.Y = Value;

	if (FMath::IsNearlyZero(Value)) return;
	SetActorRotation(CurrentRotationDirection.Rotation());
}
