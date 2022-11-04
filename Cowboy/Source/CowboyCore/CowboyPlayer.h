﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShootingComponent.h"
#include "GameFramework/Character.h"
#include "CowboyPlayer.generated.h"

UCLASS()
class COWBOYCORE_API ACowboyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACowboyPlayer();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = "Cowboy Shooting")
	UShootingComponent* ShootingComponent;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateUp(float Value);
	void RotateRight(float Value);
	
	FVector CurrentRotationDirection = FVector::ZeroVector;
};
