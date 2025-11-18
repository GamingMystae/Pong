// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MarioGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API AMarioGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	//we call it from blueprint code
	UFUNCTION(BlueprintCallable, Category = "Score")
	void ResetScore();

	//we call it from blueprint code
	UFUNCTION(BlueprintCallable)
	int GetScore();

	//
	UFUNCTION()
	static void AddScore(int ScoreToAdd);
	
private:
	// orizo to palyer score os static
	inline static int PlayerScore;
};
