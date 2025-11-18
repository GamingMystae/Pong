// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Explotion.h"
#include "Sound/SoundCue.h"
#include "EnemyFireAmmo.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "SpaceShip.h"
#include "EnemyShip.generated.h"


/**
 * 
 */
UCLASS()
class PONG_API AEnemyShip : public ASpaceShip
{
	GENERATED_BODY()
	
public:
    // Sets default values for this pawn's properties
    AEnemyShip();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to handle firing logic
    void EnemyFire();

    // Function to handle the destruction of the enemy ship
    void HandleDestruction();

    // Function to handle collision with player ships
    UFUNCTION()
    void OnCollisionWithPlayer(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

    // Function to be called to destroy the ship
    void DestroyShip();

private:
    // Function to handle firing with a delay
    void HandleFire();

    // Function to set the next fire timer
    void SetNextFireTimer();

    // Function to move towards the player
    void MoveTowardsPlayer(float DeltaTime);

    // Function to avoid other enemy ships
    void AvoidOtherShips();

    // Properties
    UPROPERTY(EditAnywhere, Category = "Combat")
    TSubclassOf<class AEnemyFireAmmo> FireAmmoClass;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float MinFireInterval;

    UPROPERTY(EditAnywhere, Category = "Combat")
    float MaxFireInterval;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float EnemySpeed;

    UPROPERTY(EditAnywhere, Category = "Effects")
    TSubclassOf<class AExplotion> ExplosionClass;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* DestructionSoundCue;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundBase* FiringSoundCue;

    // Timer handle for firing
    FTimerHandle FireTimerHandle;
    AActor* TheShip;
};