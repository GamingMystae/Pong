// Fill out your copyright notice in the Description page of Project Settings.
#include "PongBall.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Math/UnitConversion.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundBase.h"
#include "PongGameModeBase.h"



// Sets default values
APongBall::APongBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Ball"));
	RootComponent = MySprite;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Ball Hit Box"));
	MyCollider->SetBoxExtent(FVector(32, 32, 32));
	MyCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	MyCollider->SetupAttachment(RootComponent);
	

	CollisionSound = nullptr; // the sound pointer
	PlayerScore = 0;
	AIScore = 0;
	

}

// Called when the game starts or when spawned
void APongBall::BeginPlay()
{
	Super::BeginPlay();
	
	// set the reset potition as the start of the actorlocation
	ResetPotition = GetActorLocation();

	

	// set the start velocity
	MyVelocity = FVector(0, 500, 500);

	//magic numbers from the camera OrthoWidth / aspect ratio
	HalfPlayFieldHeight = (2048 / 1.777) / 2;
	HalfPlayFieldWidth = (2048 / 2);

	//Start the event for the collider box
	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &APongBall::OnCollision);
	// Load the sound asset
	CollisionSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Pong/Material/sound.sound"));
	if (!CollisionSound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load collision sound asset: /Game/Pong/Material/sound.sound"));
	}
	// Initial score logs
	UE_LOG(LogTemp, Warning, TEXT("Initial Player Score: %d"), PlayerScore);
	UE_LOG(LogTemp, Warning, TEXT("Initial AI Score: %d"), AIScore);
	
	
}

void APongBall::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MyVelocity.Y *= -1;

	UE_LOG(LogTemp, Warning, TEXT("I HIT THE BAT"));
	
	// Get the position of the ball and the bat
	FVector BallPosition = GetActorLocation();
	FVector BatPosition = OtherActor->GetActorLocation();
	//get potition of the ball relative to the bat
	float RelativeHitPosition = (BallPosition.Z - BatPosition.Z) / MyCollider->GetScaledBoxExtent().Z;

	// divide the bat in 5 parts. Top, Top midlle, Bottom,Bottom midlle and center and giving angles to the ball
	if (RelativeHitPosition < -0.6f) //Bottom 
	{
		MyVelocity.Z = -700; //diangle downwards
	}
	else if (RelativeHitPosition < -0.2f) //Bottom middle 
	{
		MyVelocity.Z = -300; //diagon with smaller angle downwards
	}
	else if (RelativeHitPosition < 0.2f) //Center 
	{
		MyVelocity.Z = 0; //straight
	}
	else if (RelativeHitPosition < 0.6f) //Top middle 
	{
		MyVelocity.Z = 300; // diagon with smaller angle upwards
	}
	else // Top 
	{
		MyVelocity.Z = 700; //Angle upwards
	}

	// Play the collision sound
	if (CollisionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, CollisionSound, GetActorLocation());
	}
}

// Called every frame
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector MyUptatedLocation = GetActorLocation() + (MyVelocity * DeltaTime);

	// ball bounce on z axis
	if (MyUptatedLocation.Z > HalfPlayFieldHeight)
	{
		MyVelocity.Z = -500; // Magic number
	}
	else if (MyUptatedLocation.Z < -HalfPlayFieldHeight)
	{
		MyVelocity.Z = 500;

	}
	//Check if the ball pass the Y or -Y size of the screen 

	if (MyUptatedLocation.Y > HalfPlayFieldWidth)
	{
		APongGameModeBase* PongGameMode = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (PongGameMode)
		{
			PongGameMode->AddAIScore(1); // Increase AI score by 1
		}
		ResetBall();
		return;
	}
	else if (MyUptatedLocation.Y < -HalfPlayFieldWidth)
	{
		APongGameModeBase* PongGameMode = Cast<APongGameModeBase>(UGameplayStatics::GetGameMode(this));
		if (PongGameMode)
		{
			PongGameMode->AddPlayerScore(1); // Increase Player score by 1
		}
		ResetBall();
		return;
	}
    SetActorLocation(MyUptatedLocation);
}

	
//void for using reset ball from the start potiotion
void APongBall::ResetBall()
{
	SetActorLocation(ResetPotition);
	MyVelocity = FVector(0, 500, 500);
	
	UE_LOG(LogTemp, Warning, TEXT("Ball reset to initial position"));
}

