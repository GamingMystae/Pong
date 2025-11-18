// Fill out your copyright notice in the Description page of Project Settings.


#include "Meteorite.h"
#include "Components/BoxComponent.h"
#include "PaperFlipbookComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerShip.h"

// Sets default values
AMeteorite::AMeteorite()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MeteoriteSprite"));
    RootComponent = MySprite;

    MyBodyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("MeteoriteCollider"));
    MyBodyCollider->SetupAttachment(RootComponent);
    MyBodyCollider->SetCollisionProfileName("BlockAllDynamic");
    MyBodyCollider->OnComponentBeginOverlap.AddDynamic(this, &AMeteorite::OnCollision);

    Speed = 100.0f; // Adjust as needed
    Direction = FVector(0, 0, -1); // Moving downwards by default

}

// Called when the game starts or when spawned
void AMeteorite::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeteorite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    FVector NewLocation = GetActorLocation() + (Direction * Speed * DeltaTime);
    SetActorLocation(NewLocation);

}
void AMeteorite::OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && OtherActor != GetOwner())
    {
        if (OtherActor->IsA(APlayerShip::StaticClass()))
        {
            Cast<APlayerShip>(OtherActor)->DestroyShip(); // Call DestroyShip on the player ship
        }
        Destroy();
    }
}