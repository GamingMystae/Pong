// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "DumbGoombah.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API ADumbGoombah : public ABaseEnemy
{
	GENERATED_BODY()
	
public:
	//caled every frame
	void Tick(float DeltaTime);
	
	UPROPERTY(EditAnywhere, Category="Player Properties")
	float EnemyHorizontalAcceleration = 1000;

	UPROPERTY(EditAnywhere, Category="Player Properies")
	float EnemyMaxSpeed = 1000;


};
