// Fill out your copyright notice in the Description page of Project Settings.


#include "MarioGameMode.h"

void AMarioGameMode::ResetScore()
{
	PlayerScore = 0;
}
int AMarioGameMode::GetScore()
{
	return PlayerScore;
}
void AMarioGameMode::AddScore(int ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
}