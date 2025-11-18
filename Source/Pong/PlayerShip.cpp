// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerShip.h"
#include "FireAmmo.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Explotion.h"
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h"
#include "EnemyShip.h"
#include "Bomb.h"
#include "Meteorite.h"
#include "EngineUtils.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include <Camera/CameraActor.h>

// Sets default values
APlayerShip::APlayerShip()
{
    PrimaryActorTick.bCanEverTick = true;
    VerticalSpeed = 100.0f;
    HorizontalSpeed = 100.0f;

    // Set up the collision handling
    OnActorHit.AddDynamic(this, &APlayerShip::OnCollisionWithEnemy);

    // Initialize the camera component
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(RootComponent);
    // Ensure the camera is set to orthographic mode
    CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
    CameraComponent->OrthoWidth = 600.0f;
    CameraComponent->AspectRatio = 0.75f; // Ensure this matches the value in your settings
}


void APlayerShip::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerShip::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FVector CurrentLocation = GetActorLocation();
    UE_LOG(LogTemp, Warning, TEXT("Player location: %s"), *CurrentLocation.ToString());
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Vertical", this, &APlayerShip::MoveVertical);
    PlayerInputComponent->BindAxis("Horizontal", this, &APlayerShip::MoveHorizontal);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerShip::Fire);
    PlayerInputComponent->BindAction("Bomb", IE_Pressed, this, &APlayerShip::Bomb);
}

void APlayerShip::MoveVertical(float Input)
{
    FVector CurrentLocation = GetActorLocation();
    CurrentLocation.Z += Input * VerticalSpeed * GetWorld()->GetDeltaSeconds();
    SetActorLocation(CurrentLocation);
}

void APlayerShip::MoveHorizontal(float Input)
{
    FVector CurrentLocation = GetActorLocation();
    CurrentLocation.X += Input * HorizontalSpeed * GetWorld()->GetDeltaSeconds();
    SetActorLocation(CurrentLocation);
}

void APlayerShip::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("Firing!"));

    if (FiringSoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FiringSoundCue, GetActorLocation());
    }
    if (FireBPClass)
    {
        FVector SpawnLocation = GetActorLocation() + FVector(0, 0, 10);
        FRotator SpawnRotation = FRotator::ZeroRotator;
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.Instigator = GetInstigator();

        AFireAmmo* SpawnedAmmo = GetWorld()->SpawnActor<AFireAmmo>(FireBPClass, SpawnLocation, SpawnRotation, SpawnParams);
        if (SpawnedAmmo)
        {
            SpawnedAmmo->SetDirection(FVector(0, 0, 1));
        }
    }
}

void APlayerShip::Bomb()
{
    if (BombClass)
    {
        const int32 NumberOfExplosions = 10;
        FVector2D ScreenMin, ScreenMax;
        GetScreenBounds(ScreenMin, ScreenMax);

        // Debug logging for screen bounds
        UE_LOG(LogTemp, Warning, TEXT("ScreenMin: %s, ScreenMax: %s"), *ScreenMin.ToString(), *ScreenMax.ToString());

        for (int32 i = 0; i < NumberOfExplosions; ++i)
        {
            // Randomize X and Z, keep Y fixed at 0
            FVector RandomLocation = FVector(FMath::RandRange(ScreenMin.X, ScreenMax.X), 0.0f, FMath::RandRange(ScreenMin.Y, ScreenMax.Y));

            // Debug logging for random locations
            UE_LOG(LogTemp, Warning, TEXT("RandomLocation: %s"), *RandomLocation.ToString());

            if (BombClass)
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = this;
                SpawnParams.Instigator = GetInstigator();

                ABomb* Bomb = GetWorld()->SpawnActor<ABomb>(BombClass, RandomLocation, FRotator::ZeroRotator, SpawnParams);
                if (Bomb)
                {
                    Bomb->Explode();
                }
            }
        }

        DestroyAllEnemiesAndObstacles();
    }
}

void APlayerShip::DestroyAllEnemiesAndObstacles()
{
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        AActor* Actor = *It;
        if (Actor->ActorHasTag("Background"))
        {
            continue; // Skip background actors
        }

        if (Actor->IsA<AEnemyShip>() || Actor->IsA<AFireAmmo>() || Actor->IsA<AMeteorite>() || Actor->IsA<AEnemyFireAmmo>())
        {
            Actor->Destroy();
        }
    }
}

void APlayerShip::DestroyShip()
{
    HandleDestruction();
}

void APlayerShip::HandleDestruction()
{
    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // Spawn the explosion actor at the player ship's location
    if (ExplosionClass)
    {
        GetWorld()->SpawnActor<AExplotion>(ExplosionClass, SpawnLocation, SpawnRotation, SpawnParams);
    }

    // Play the destruction sound
    if (DestructionSoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(this, DestructionSoundCue, GetActorLocation());
    }

    // Hide the player ship instead of destroying it immediately
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);

    // Set a timer to call the OnDestructionComplete function after 3 seconds
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APlayerShip::OnDestructionComplete, 3.0f, false);
}

void APlayerShip::OnDestructionComplete()
{
    // Load the game over level or show the UI
    UGameplayStatics::OpenLevel(GetWorld(), "L_GameOverInvasion");

    // Destroy the actor after loading the level or showing the UI
    Destroy();
}

void APlayerShip::OnCollisionWithEnemy(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    AEnemyShip* Enemy = Cast<AEnemyShip>(OtherActor);
    if (Enemy)
    {
        // Destroy the enemy ship
        Enemy->HandleDestruction();

        // Destroy the player ship
        HandleDestruction();
    }
}

void APlayerShip::GetScreenBounds(FVector2D& OutMin, FVector2D& OutMax)
{
    float OrthoWidth = CameraComponent->OrthoWidth;
    float AspectRatio = CameraComponent->AspectRatio;
    float OrthoHeight = OrthoWidth / AspectRatio;

    OutMin = FVector2D(-OrthoWidth / 2, -OrthoHeight / 2);
    OutMax = FVector2D(OrthoWidth / 2, OrthoHeight / 2);
}