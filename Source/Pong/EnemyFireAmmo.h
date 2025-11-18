// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyFireAmmo.generated.h"

UCLASS()
class PONG_API AEnemyFireAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFireAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetDirection(FVector NewDirection);
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* MyBodyCollider;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPaperFlipbookComponent* MySprite;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector Direction;

	
	void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
