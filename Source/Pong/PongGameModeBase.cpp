#include "PongGameModeBase.h"
#include "Kismet/GameplayStatics.h"

APongGameModeBase::APongGameModeBase()
{
	// Initialize scores
	PlayerScore = 0;
	AIScore = 0;
	WinningScore = 3; // Default winning score is 3, can be adjusted in editor
}

void APongGameModeBase::ResetScore()
{
	PlayerScore = 0;
	AIScore = 0;
}

int APongGameModeBase::GetPlayerScore() const
{
	return PlayerScore;
}

int APongGameModeBase::GetAIScore() const
{
	return AIScore;
}

void APongGameModeBase::AddPlayerScore(int ScoreToAdd)
{
	PlayerScore += ScoreToAdd;
	UE_LOG(LogTemp, Warning, TEXT("Player Score: %d"), PlayerScore);

	CheckForWin();
}

void APongGameModeBase::AddAIScore(int ScoreToAdd)
{
	AIScore += ScoreToAdd;
	UE_LOG(LogTemp, Warning, TEXT("AI Score: %d"), AIScore);

	CheckForWin();
}

void APongGameModeBase::CheckForWin()
{
	if (PlayerScore >= WinningScore)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Wins!"));
		UGameplayStatics::OpenLevel(this, FName("L_PongGameOver"));
		return;
	}
	else if (AIScore >= WinningScore)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Wins!"));
		UGameplayStatics::OpenLevel(this, FName("L_PongGameOver"));
		return;
	}
}
