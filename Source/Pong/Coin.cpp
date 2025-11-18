// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "PaperSpriteComponent.h"
#include "Mario.h"

// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the sprite.
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;
}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	// no hit that why using overlap.
	MySprite->OnComponentBeginOverlap.AddDynamic(this, &ACoin::BeginOverlap);
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);

}
//  ftiaxno thn coid gia to overlap
void ACoin::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
	Destroy();

}

