// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PeggleBall.generated.h"

UCLASS()
class PONG_API APeggleBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APeggleBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "My Ball");
	class UPaperSpriteComponent* MySprite;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
