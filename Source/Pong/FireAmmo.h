// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/Actor.h"
#include "FireAmmo.generated.h"

UCLASS()
class PONG_API AFireAmmo : public AActor
{
	GENERATED_BODY()
	
public:
    AFireAmmo();

protected:
    virtual void BeginPlay() override;
    

public:
    void SetDirection(FVector NewDirection);
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UBoxComponent* MyBodyCollider;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UPaperFlipbookComponent* MySprite;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Speed;

    UPROPERTY(EditAnywhere, Category = "Movement")
    FVector Direction;

    UFUNCTION()
    void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};