// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "BreakBrick.generated.h"

UCLASS()
class PONG_API ABreakBrick : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABreakBrick();

    // Function to handle collision
    UFUNCTION()
    void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Declaration for the sprite component
    UPROPERTY(VisibleAnywhere, Category = "Sprite")
    UPaperSpriteComponent* MySprite;

    // Declaration for the collision box component
    UPROPERTY(VisibleAnywhere, Category = "Collision")
    UBoxComponent* MyCollider;

    // Health property, editable in Unreal Editor
    UPROPERTY(EditAnywhere, Category = "Brick Properties")
    int32 Health;

    // Function to take damage
    void HandleTakeDamage(float DamageAmount);
};
