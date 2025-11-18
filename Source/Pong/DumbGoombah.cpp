// Fill out your copyright notice in the Description page of Project Settings.


#include "DumbGoombah.h"
#include "Components/CapsuleComponent.h"

void ADumbGoombah::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyBodyCollider->AddForce(FVector(0, 1, 0) * EnemyHorizontalAcceleration);
	FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
	ClampedSpeed.Y = FMath::Clamp(ClampedSpeed.Y, -EnemyMaxSpeed, EnemyMaxSpeed);
	MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);
}

