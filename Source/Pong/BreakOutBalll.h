// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundBase.h"
#include "BreakOutBalll.generated.h"

UCLASS()
class PONG_API ABreakOutBalll : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABreakOutBalll();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Declaration for the sprite the sprite
	UPROPERTY(VisibleAnywhere, Category = "My Ball")
	class UPaperSpriteComponent* MySprite;// declare a pointer to the class UPaperSprite  with the name MySprite 

	//declaration for collosionbox
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* MyCollider;
	UFUNCTION()
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// variable to hold the sound
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* CollisionSound;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	FVector MyVelocity;
	float HalfPlayFieldHeight;
	float HalfPlayFieldWidth;
	float BallHalfWidth;
	float BallSpeed;
};