// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "PeggleBallLauncher.generated.h"

UCLASS()
class PONG_API APeggleBallLauncher : public APawn
{
	GENERATED_BODY()
	

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	TSubclassOf<AActor> BallBPClass ; /// INHERITING AN OBJECT WITH THE SPECIFIC TYPE

public:
	// Sets default values for this pawn's properties
	APeggleBallLauncher();
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MovePlayer(float input);
	void  Fire();
	float ShotPower;


protected:
		
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Declaration for the sprite in the editor
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* MySprite;
	virtual void OnConstruction(const FTransform& Transform) override;
	

};

