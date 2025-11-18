// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound/SoundCue.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explotion.generated.h"

UCLASS()
class PONG_API AExplotion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to initialize the explosion with location and sound
	void Initialize(FVector Location, USoundBase* ExplosionSound);

private:
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* ExplosionFlipbook;

	UFUNCTION()
	void OnFinishedPlaying();
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* ExplosionSoundCue;
};
