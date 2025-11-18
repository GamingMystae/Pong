// Fill out your copyright notice in the Description page of Project Settings.


#include "InvasionGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"



void AInvasionGameMode::ResetScore()
{
	PlayerScore = 0;
}

int AInvasionGameMode::GetScore()
{
	return PlayerScore;
}

void AInvasionGameMode::AddScore(int ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
}
