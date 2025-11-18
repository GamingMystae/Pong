// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "InvasionGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API AInvasionGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	
	UFUNCTION(BlueprintCallable)
	void ResetScore();

	UFUNCTION(BlueprintCallable)
	int GetScore();
	UFUNCTION()
	static void AddScore(int ScoreToAdd);
private:
	inline static int PlayerScore;
	

};
