// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "BreakOutBat.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API ABreakOutBat : public ABasePongBat
{
	GENERATED_BODY()
	
public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MovePlayer(float input);

};
