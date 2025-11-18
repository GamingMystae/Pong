// Fill out your copyright notice in the Description page of Project Settings.


#include "Spike.h"
#include "PaperSpriteComponent.h"
#include "Mario.h"

// Sets default values
ASpike::ASpike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set the sprite.
	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	RootComponent = MySprite;

}

void ASpike::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->KillMario();
	}
}

// Called when the game starts or when spawned
void ASpike::BeginPlay()
{
	Super::BeginPlay();
	MySprite->OnComponentHit.AddDynamic(this, &ASpike::OnCollision);
}

// Called every frame
void ASpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

