// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PongBall.h"
#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "PlayerPongBat.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APlayerPongBat : public ABasePongBat
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MovePlayer(float input);
	
	
};
