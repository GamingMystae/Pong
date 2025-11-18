// Fill out your copyright notice in the Description page of Project Settings.


#include "PeggleBall.h"
#include "PaperSpriteComponent.h"

APeggleBall::APeggleBall()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create and configure the sprite component
    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MySprite"));
    RootComponent = MySprite;

    // Enable physics on the sprite component
    MySprite->SetSimulatePhysics(true);
    MySprite->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MySprite->SetCollisionProfileName(TEXT("PhysicsActor")); 
}

void APeggleBall::BeginPlay()
{
    Super::BeginPlay();
    // Additional initialization can be done here
}

void APeggleBall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Add any specific tick behavior here if necessary
}


