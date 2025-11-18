// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFireAmmo.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "PlayerShip.h"
#include "EnemyShip.h"

// Sets default values
AEnemyFireAmmo::AEnemyFireAmmo()
{
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("AmmoSprite"));
    RootComponent = MySprite;

    MyBodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("AmmoCollider"));
    MyBodyCollider->SetupAttachment(RootComponent);

    MyBodyCollider->SetCollisionProfileName("Projectile");
    MyBodyCollider->SetGenerateOverlapEvents(true);
    MyBodyCollider->OnComponentBeginOverlap.AddDynamic(this, &AEnemyFireAmmo::OnCollision);

    Speed = 250.0f;
    Direction = FVector(0, 0, -1);
}

// Called when the game starts or when spawned
void AEnemyFireAmmo::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AEnemyFireAmmo::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Ensure the speed is applied to the direction vector
    FVector NewLocation = GetActorLocation() + (Direction * Speed * DeltaTime);
    SetActorLocation(NewLocation);
}

void AEnemyFireAmmo::SetDirection(FVector NewDirection)
{
    Direction = NewDirection;
}

void AEnemyFireAmmo::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherActor != GetOwner())
    {
        UE_LOG(LogTemp, Warning, TEXT("FireAmmo collided with: %s"), *OtherActor->GetName());

        if (OtherActor->IsA(APlayerShip::StaticClass()))
        {
            APlayerShip* PlayerShip = Cast<APlayerShip>(OtherActor);
            if (PlayerShip)
            {
                UE_LOG(LogTemp, Warning, TEXT("PlayerShip found, calling Destroy"));
                PlayerShip->Destroy(); // Destroy the player ship
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("PlayerShip cast failed"));
            }
        }
        Destroy(); // Destroy the ammo itself
    }
}