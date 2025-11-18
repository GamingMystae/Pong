// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Explotion.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the sprite component
    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpaceShipSprite"));
    RootComponent = MySprite;

    // Create the body collider
    MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SpaceShipCapsule"));
    MyBodyCollider->SetupAttachment(RootComponent);

    // Enable collision
    MyBodyCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MyBodyCollider->SetGenerateOverlapEvents(true);

}

void ASpaceShip::BeginPlay()
{
    Super::BeginPlay();

    // Get the game camera
    AActor* GameCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
    if (ACameraActor* CameraActor = Cast<ACameraActor>(GameCamera))
    {
        UCameraComponent* GameCameraComponent = CameraActor->GetCameraComponent();
        if (GameCameraComponent)
        {
            // Calculate half play field dimensions
            HalfPlayFieldHeight = (GameCameraComponent->OrthoWidth / GameCameraComponent->AspectRatio) / 2;
            HalfPlayFieldWidth = GameCameraComponent->OrthoWidth / 2;

            // Bind collision overlap event
            MyBodyCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpaceShip::OnCollision);
        }
    }

    // Set collider size based on sprite bounds
    MyBodyCollider->SetCapsuleHalfHeight(MySprite->Bounds.BoxExtent.Z);
    MyBodyCollider->SetCapsuleRadius(MySprite->Bounds.BoxExtent.X);

    // Calculate half bat height and width
    HalfBatHeight = MySprite->Bounds.BoxExtent.Z;
    HalfBatWidth = MySprite->Bounds.BoxExtent.X;
}

void ASpaceShip::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Calculate updated location
    FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);

    // Clamp the location to stay within the play field
    MyUpdatedLocation.Z = FMath::Clamp(MyUpdatedLocation.Z, -HalfPlayFieldHeight + HalfBatHeight, HalfPlayFieldHeight - HalfBatHeight);
    MyUpdatedLocation.X = FMath::Clamp(MyUpdatedLocation.X, -HalfPlayFieldWidth + HalfBatWidth, HalfPlayFieldWidth - HalfBatWidth);

    // Set the updated location
    SetActorLocation(MyUpdatedLocation);
}

void ASpaceShip::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Handle collision logic here
}

void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind input actions here if needed
}
