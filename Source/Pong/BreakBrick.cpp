// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakBrick.h"
#include "Components/BoxComponent.h"
#include "Math/UnitConversion.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BreakOutBalll.h"

// Sets default values
ABreakBrick::ABreakBrick()
{
    // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create and set up the sprite component
    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Brick"));
    RootComponent = MySprite;

    // Create and set up the collision box component
    MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit The Brick"));
    MyCollider->SetBoxExtent(FVector(20, 20, 20));
    MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MyCollider->SetupAttachment(RootComponent);
    MyCollider->SetGenerateOverlapEvents(true);

    // Starting health, editable in Unreal Editor
    Health = 3;
    UE_LOG(LogTemp, Warning, TEXT("Brick initial health: %d"), Health);
}

// Called when the game starts or when spawned
void ABreakBrick::BeginPlay()
{
    Super::BeginPlay();

    // Bind the OnCollision function to the collider's overlap event
    MyCollider->OnComponentBeginOverlap.AddDynamic(this, &ABreakBrick::OnCollision);

    // Directly set the collision box extent from the sprite's bounds
    MyCollider->SetBoxExtent(MySprite->Bounds.GetBox().GetSize());
}

// Called every frame
void ABreakBrick::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ABreakBrick::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if OtherActor is valid, not the brick itself, and not a self-collision
    if (OtherActor && OtherActor != this && OtherComp != MyCollider)
    {
        UE_LOG(LogTemp, Warning, TEXT("Collision detected with: %s"), *OtherActor->GetName());

        // Call function to handle damage
        HandleTakeDamage(1.0f);
    }
}

void ABreakBrick::HandleTakeDamage(float DamageAmount)
{
    // Decrease health
    Health -= DamageAmount;

    // Log health after decrement
    UE_LOG(LogTemp, Warning, TEXT("Brick hit! Remaining health: %d"), Health);

    // Check if health is zero or less
    if (Health <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Brick destroyed!"));

        // Destroy the brick
        Destroy();
    }
}

float ABreakBrick::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    // Call the internal handle damage function
    HandleTakeDamage(DamageAmount);

    return DamageAmount;
}
