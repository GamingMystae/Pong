#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

UCLASS()
class PONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Constructor
	APongGameModeBase();

	// Reset the score to 0
	UFUNCTION(BlueprintCallable, Category = "Score")
	void ResetScore();

	// Get the player's current score
	UFUNCTION(BlueprintCallable)
	int GetPlayerScore() const;

	// Get the AI's current score
	UFUNCTION(BlueprintCallable)
	int GetAIScore() const;

	// Add to the player's score
	UFUNCTION(BlueprintCallable)
	void AddPlayerScore(int ScoreToAdd);

	// Add to the AI's score
	UFUNCTION(BlueprintCallable)
	void AddAIScore(int ScoreToAdd);

	// Check if either player has won
	UFUNCTION(BlueprintCallable)
	void CheckForWin();

private:
	// Store the player's score
	UPROPERTY()
	int PlayerScore;

	// Store the AI's score
	UPROPERTY()
	int AIScore;

	// Score limit to win the game
	UPROPERTY(EditAnywhere, Category = "Score")
	int WinningScore;
};
