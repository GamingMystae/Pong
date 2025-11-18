// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPongBat.h"
#include "PongBall.h"

void APlayerPongBat::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerPongBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponet)
{
    PlayerInputComponet->BindAxis("Vertical", this, &APlayerPongBat::MovePlayer);
    
	Super::SetupPlayerInputComponent(PlayerInputComponet);
}

void APlayerPongBat::MovePlayer(float input)
{
	SetActorLocation(GetActorLocation() + FVector(0, 0, 2 * input));
}
