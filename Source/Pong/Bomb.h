// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound/SoundCue.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class PONG_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    ABomb();

    // Function to trigger the bomb explosion
    void Explode();

    void HandleExplosion();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
   

    UPROPERTY(EditAnywhere, Category = "Effects")
    UParticleSystem* ExplosionEffect;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundCue* ExplosionSound;
};
