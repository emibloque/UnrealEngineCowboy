// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CowboyPlayer.generated.h"

UCLASS()
class COWBOYCORE_API ACowboyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACowboyPlayer();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
