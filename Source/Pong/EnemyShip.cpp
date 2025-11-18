// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShip.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerShip.h"
#include "EnemyFireAmmo.h"
#include "TimerManager.h"
#include "Explotion.h"
#include "GameFramework/Actor.h"
#include "Meteorite.h"

AEnemyShip::AEnemyShip()
  
{ // Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Initialize properties
    MinFireInterval = 1.0f;
    MaxFireInterval = 3.0f;
    EnemySpeed = 100.0f;
    DestructionSoundCue = nullptr;
    FiringSoundCue = nullptr;
    TheShip = nullptr;

    // Set up the collision handling
    OnActorHit.AddDynamic(this, &AEnemyShip::OnCollisionWithPlayer);
}

void AEnemyShip::BeginPlay()
{
    Super::BeginPlay();
    TheShip = Cast<APlayerShip>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerShip::StaticClass()));
    if (!TheShip)
    {
        UE_LOG(LogTemp, Error, TEXT("TheShip is null!"));
        return;
    }
    SetNextFireTimer();
}

void AEnemyShip::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (TheShip)
    {
        MoveTowardsPlayer(DeltaTime);
        AvoidOtherShips();
    }
}

void AEnemyShip::MoveTowardsPlayer(float DeltaTime)
{
    FVector DirectionToPlayer = (TheShip->GetActorLocation() - GetActorLocation()).GetSafeNormal();
    FVector NewLocation = GetActorLocation() + (DirectionToPlayer * EnemySpeed * DeltaTime);
    SetActorLocation(NewLocation);
    UE_LOG(LogTemp, Warning, TEXT("Moving towards player: %s"), *NewLocation.ToString());
}

void AEnemyShip::AvoidOtherShips()
{
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors, AActor::StaticClass());
    FVector AvoidanceVector = FVector::ZeroVector;
    for (AActor* Actor : OverlappingActors)
    {
        if (Actor != this && (Actor->IsA(AEnemyShip::StaticClass()) || Actor->IsA(AMeteorite::StaticClass())))
        {
            FVector AwayFromOther = GetActorLocation() - Actor->GetActorLocation();
            AvoidanceVector += AwayFromOther.GetSafeNormal();
        }
    }
    if (OverlappingActors.Num() > 0)
    {
        AvoidanceVector /= OverlappingActors.Num();
        FVector NewLocation = GetActorLocation() + (AvoidanceVector * EnemySpeed * GetWorld()->GetDeltaSeconds());
        SetActorLocation(NewLocation);
        UE_LOG(LogTemp, Warning, TEXT("Avoiding obstacles: %s"), *NewLocation.ToString());
    }
}

void AEnemyShip::EnemyFire()
{
    UE_LOG(LogTemp, Warning, TEXT("Enemy Firing!"));
    if (FiringSoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FiringSoundCue, GetActorLocation());
    }
    if (FireAmmoClass)
    {
        FVector SpawnLocation = GetActorLocation() + FVector(0, 0, -10); // Adjust the offset as needed
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();
        AEnemyFireAmmo* SpawnedAmmo = GetWorld()->SpawnActor<AEnemyFireAmmo>(FireAmmoClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

        if (SpawnedAmmo)
        {
            SpawnedAmmo->SetDirection(FVector(0, 0, -1));
        }
    }
}

void AEnemyShip::HandleFire()
{
    EnemyFire();
    SetNextFireTimer();
}

void AEnemyShip::SetNextFireTimer()
{
    bool bInvalidSettings = false;

    if (MinFireInterval <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid fire interval settings: MinFireInterval must be greater than 0."));
        bInvalidSettings = true;
    }

    if (MaxFireInterval <= 0.0f)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid fire interval settings: MaxFireInterval must be greater than 0."));
        bInvalidSettings = true;
    }

    if (MinFireInterval > MaxFireInterval)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid fire interval settings: MinFireInterval must be less than or equal to MaxFireInterval."));
        bInvalidSettings = true;
    }

    if (!bInvalidSettings)
    {
        float RandomInterval = FMath::FRandRange(MinFireInterval, MaxFireInterval);
        GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AEnemyShip::HandleFire, RandomInterval, false);
    }
}

void AEnemyShip::DestroyShip()
{
    HandleDestruction();
}

void AEnemyShip::HandleDestruction()
{
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // Spawn the explosion actor at the enemy ship's location
    if (ExplosionClass)
    {
        GetWorld()->SpawnActor<AExplotion>(ExplosionClass, SpawnLocation, SpawnRotation, SpawnParams);
    }
    // Play the destruction sound
    if (DestructionSoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(this, DestructionSoundCue, GetActorLocation());
    }

    Destroy();
}

void AEnemyShip::OnCollisionWithPlayer(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
    APlayerShip* Player = Cast<APlayerShip>(OtherActor);
    if (Player)
    {
        // Destroy both the enemy ship and the player ship
        Player->HandleDestruction();
        HandleDestruction();
    }
}