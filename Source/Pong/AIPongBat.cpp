// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPongBat.h"
#include "PongBall.h"

#include "Kismet/GamePlayStatics.h"

void AAIPongBat::BeginPlay()
{
	Super::BeginPlay(); // this runs the base begin play method in our classQQ
	UE_LOG(LogTemp, Warning, TEXT("BEGIN PLAY CALLED!!"));
	TheBall = UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass());
}
void AAIPongBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); //run the tick method in our base class
	if (GetActorLocation().Z > TheBall->GetActorLocation().Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0, 0, -460 *DeltaTime));
	}
	if (GetActorLocation().Z < TheBall->GetActorLocation().Z)
	{
		SetActorLocation(GetActorLocation() + FVector(0, 0, 460 *DeltaTime));
	}
}
	