// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PeggleBlock.generated.h"

UCLASS()
class PONG_API APeggleBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeggleBlock();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Declaration for the sprite the sprite
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperSpriteComponent* MySprite;

	virtual void OnConstruction(const FTransform& Transform) override;

private:
	FTimerHandle DestroyTimer;
	void DestroyThisObject();
};
