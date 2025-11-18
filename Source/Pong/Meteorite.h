// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Meteorite.generated.h"

UCLASS()
class PONG_API AMeteorite : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeteorite();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
    UPROPERTY(VisibleAnywhere)
    class UPaperFlipbookComponent* MySprite;

    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* MyBodyCollider;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float Speed;

    UPROPERTY(EditAnywhere, Category = "Movement")
    FVector Direction;

    UFUNCTION()
    void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};

