// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakOutBat.h"
#include "Math/UnitConversion.h"

/**
 * 
 *
 * 
 */
void ABreakOutBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    InputComponent->BindAxis("Horizontal", this, &ABreakOutBat::MovePlayer);
    Super::SetupPlayerInputComponent(PlayerInputComponent);
      
   
}
void ABreakOutBat::MovePlayer(float input)
{

    SetActorLocation(GetActorLocation() + FVector(0, 3 * input, 0));
}
