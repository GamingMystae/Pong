// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePongBat.h"
#include "AIPongBat.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API AAIPongBat : public ABasePongBat
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "ReferencedActors")
	class AActor* TheBall;
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
