// Fill out your copyright notice in the Description page of Project Settings.


#include "Explotion.h"
#include "PaperFlipbookComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AExplotion::AExplotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ExplosionFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("ExplosionFlipbook"));
	RootComponent = ExplosionFlipbook;

	// Bind the OnFinishedPlaying function to the OnFinishedPlaying event of the flipbook
	ExplosionFlipbook->OnFinishedPlaying.AddDynamic(this, &AExplotion::OnFinishedPlaying);
}

// Called when the game starts or when spawned
void AExplotion::BeginPlay()
{
	Super::BeginPlay();
	// Start playing the flipbook animation
	if (ExplosionFlipbook && ExplosionFlipbook->GetFlipbook())
	{
		ExplosionFlipbook->PlayFromStart();
	}
	
}

// Called every frame
void AExplotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AExplotion::Initialize(FVector Location, USoundBase* ExplosionSound)
{
	SetActorLocation(Location);

	// Play the explosion sound
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, Location);
	}
}
void AExplotion::OnFinishedPlaying()
{
	Destroy();
}

