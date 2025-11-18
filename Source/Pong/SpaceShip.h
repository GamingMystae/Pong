// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

UCLASS()
class PONG_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Sprite component
    UPROPERTY(VisibleAnywhere, Category = "Sprites")
    class UPaperFlipbookComponent* MySprite;

    // Capsule component
    UPROPERTY(VisibleAnywhere, Category = "Collider")
    class UCapsuleComponent* MyBodyCollider;

    UFUNCTION()
    virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    FVector MyVelocity;
    float HalfBatHeight;
    float HalfBatWidth;
    float HalfPlayFieldHeight;
    float HalfPlayFieldWidth;
};
