// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABomb::ABomb()
{
    PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
    Super::BeginPlay();
}

void ABomb::Explode()
{
    HandleExplosion();

    // Destroy the bomb actor after explosion
    Destroy();
}

void ABomb::HandleExplosion()
{
    if (ExplosionEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
    }

    if (ExplosionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
    }

    // Logic to destroy nearby actors (if needed) can be added here
}
