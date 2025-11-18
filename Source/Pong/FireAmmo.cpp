// Fill out your copyright notice in the Description page of Project Settings.


#include "FireAmmo.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "PlayerShip.h"
#include "EnemyShip.h"


// Sets default values
AFireAmmo::AFireAmmo()
{
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AmmoSprite"));
    RootComponent = MySprite;

    MyBodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("AmmoCollider"));
    MyBodyCollider->SetupAttachment(RootComponent);

    MyBodyCollider->SetCollisionProfileName("Projectile");
    MyBodyCollider->SetGenerateOverlapEvents(true);// dokimh edo
    MyBodyCollider->OnComponentBeginOverlap.AddDynamic(this, &AFireAmmo::OnCollision);

    Speed = 250.0f;
    Direction = FVector(0, 0, 1); // Default direction is upwards
}

// Called when the game starts or when spawned
void AFireAmmo::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AFireAmmo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector NewLocation = GetActorLocation() + (Direction * Speed * DeltaTime);
    SetActorLocation(NewLocation);
}

void AFireAmmo::SetDirection(FVector NewDirection)
{
    Direction = NewDirection;
}

void AFireAmmo::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherActor != GetOwner())
    {
        UE_LOG(LogTemp, Warning, TEXT("FireAmmo collided with: %s"), *OtherActor->GetName());

        if (OtherActor->IsA(AEnemyShip::StaticClass()))
        {
            AEnemyShip* EnemyShip = Cast<AEnemyShip>(OtherActor);
            if (EnemyShip)
            {
                UE_LOG(LogTemp, Warning, TEXT("EnemyShip found, calling Destroy"));
                EnemyShip->Destroy(); // Destroy the enemy ship
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("EnemyShip cast failed"));
            }
        }
        Destroy(); // Destroy the ammo itself
    }
}