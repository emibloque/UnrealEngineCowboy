// Fill out your copyright notice in the Description page of Project Settings.


#include "CowboyPlayer.h"


// Sets default values
ACowboyPlayer::ACowboyPlayer()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called to bind functionality to input
void ACowboyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

