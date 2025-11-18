// Fill out your copyright notice in the Description page of Project Settings.

#include "BreakOutBalll.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Math/UnitConversion.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "BreakBrick.h"
#include "BasePongBat.h"
#include "Sound/SoundBase.h"
#include "BreakOutBat.h"

// Sets default values
ABreakOutBalll::ABreakOutBalll()
{
    PrimaryActorTick.bCanEverTick = true;
    BallSpeed = 300;
	//BallHalfWidth = MySprite->Bounds.GetBox().GetSize().Y / 2;

    MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Ball"));
    RootComponent = MySprite;

    MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
	MyCollider->SetBoxExtent(FVector(BallHalfWidth, BallHalfWidth, BallHalfWidth));

    MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MyCollider->SetupAttachment(RootComponent);

    CollisionSound = nullptr; // the sound pointer
}

// Called when the game starts or when spawned
void ABreakOutBalll::BeginPlay()
{
    Super::BeginPlay();
	    
	MyVelocity = FVector(0, BallSpeed, BallSpeed);

    AActor* GameCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
    if (ACameraActor* CameraActor = Cast<ACameraActor>(GameCamera))
    {
        UCameraComponent* GameCameraComponent = CameraActor->GetCameraComponent();
        if (GameCameraComponent)
        {
            HalfPlayFieldHeight = (GameCameraComponent->OrthoWidth / GameCameraComponent->AspectRatio) / 2;
            HalfPlayFieldWidth = GameCameraComponent->OrthoWidth / 2;

            MyCollider->OnComponentBeginOverlap.AddDynamic(this, &ABreakOutBalll::OnCollision);
        }
    }
    // Load the sound asset
    CollisionSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Pong/Material/sound.sound"));
    if (!CollisionSound)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load collision sound asset: /Game/Pong/Material/sound.sound"));
    }
}
void ABreakOutBalll::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MyVelocity.Z *= -1;

	FVector BatPosition = GetActorLocation();  // Only declaration needed

	if (OtherActor->IsA(ABreakOutBat::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("I HIT THE BAT"));
		// Play the collision sound
		if (CollisionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CollisionSound, GetActorLocation());
		}
		// Use BatPosition directly, no need to re-declare it
		MyVelocity.Z = BallSpeed;
	}
	else if (OtherActor->IsA(ABreakBrick::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("I HIT THE Brick"));
		// Play the collision sound
		if (CollisionSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, CollisionSound, GetActorLocation());
		}
		// Use BatPosition directly, no need to re-declare it
		MyVelocity.Z = BallSpeed;

		//Deflect the ball
		FVector HitDirection = (GetActorLocation() - OtherActor->GetActorLocation()).GetSafeNormal();
		MyVelocity = HitDirection * BallSpeed;
		if (abs(HitDirection.Y) > abs(HitDirection.Z))
		{
			if (HitDirection.Y > 0)
			{
				MyVelocity.Y = BallSpeed;

			}
			else if (HitDirection.Y < 0)
			{
				MyVelocity.Y = -BallSpeed;
			}
		}

		//Destroy actor
		OtherActor->Destroy();
	}
}

// Called every frame
void ABreakOutBalll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MyUpdatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);

	// Check vertical boundaries and adjust if necessary
	if (MyUpdatedLocation.Z > HalfPlayFieldHeight) {
		MyVelocity.Z = -MyVelocity.Z;  // Reverse vertical direction
		MyUpdatedLocation.Z = 2 * HalfPlayFieldHeight - MyUpdatedLocation.Z;  // Reflect the position about the boundary
	}
	/*else if (MyUpdatedLocation.Z < -HalfPlayFieldHeight) {
		MyVelocity.Z = -MyVelocity.Z;  // Reverse vertical direction
		MyUpdatedLocation.Z = -2 * HalfPlayFieldHeight - MyUpdatedLocation.Z;  // Reflect the position about the boundary
	}*/

	// Check horizontal boundaries and adjust if necessary
	if (MyUpdatedLocation.Y > HalfPlayFieldWidth) {
		MyVelocity.Y = -MyVelocity.Y;  // Reverse horizontal direction
		MyUpdatedLocation.Y = 2 * HalfPlayFieldWidth - MyUpdatedLocation.Y;  // Reflect the position about the boundary
	}
	else if (MyUpdatedLocation.Y < -HalfPlayFieldWidth) {
		MyVelocity.Y = -MyVelocity.Y;  // Reverse horizontal direction
		MyUpdatedLocation.Y = -2 * HalfPlayFieldWidth - MyUpdatedLocation.Y;  // Reflect the position about the boundary
	}
	SetActorLocation(MyUpdatedLocation, false, NULL, ETeleportType::TeleportPhysics);
}
