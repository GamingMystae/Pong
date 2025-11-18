// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePongBat.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ABasePongBat::ABasePongBat()
{
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;

	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
	MyCollider->SetBoxExtent(FVector(32, 32, 32));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetupAttachment(RootComponent);

}


// Called when the game starts or when spawned
void ABasePongBat::BeginPlay()
{
	Super::BeginPlay();
	AActor* GameCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());
	if (ACameraActor* CameraActor = Cast<ACameraActor>(GameCamera))
	{
		UCameraComponent* GameCameraComponent = CameraActor->GetCameraComponent();
		if (GameCameraComponent)
		{
			HalfPlayFieldHeight = (GameCameraComponent->OrthoWidth / GameCameraComponent->AspectRatio) / 2;
			HalfPlayFieldWidth = GameCameraComponent->OrthoWidth / 2;

			MyCollider->OnComponentBeginOverlap.AddDynamic(this, &ABasePongBat::OnCollision);
		}
	}
	MyCollider->SetBoxExtent(MySprite->Bounds.GetBox().GetSize()); //directly setting the bat hit box from the sprite

	// calculate for getting the half height of the bat and use it with the half height of the screen of dont getting out the screen
	HalfBatHeight = MySprite->Bounds.BoxExtent.Z;
	HalfBatWidth = MySprite->Bounds.BoxExtent.Y;

	
}


void ABasePongBat::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

// Called every frame
void ABasePongBat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector MyUptatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);
	// Dont let the bat get out from the size of the screen using the half screen height and the half bat size 
	MyUptatedLocation.Z = FMath::Clamp(MyUptatedLocation.Z, -HalfPlayFieldHeight + HalfBatHeight, HalfPlayFieldHeight - HalfBatHeight);
	// Clamp the Y-coordinate (X-axis in 2D) of the bat's location
	MyUptatedLocation.Y = FMath::Clamp(MyUptatedLocation.Y, -HalfPlayFieldWidth +HalfBatWidth, HalfPlayFieldWidth - HalfBatWidth);



	SetActorLocation(MyUptatedLocation);
}

// Called to bind functionality to input
void ABasePongBat::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

