// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Mario.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("EnemyBodySprite"));
	MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("EnemyBodyCapsule"));
	LeftTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Left Collider"));
	RightTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Right Collider"));
	HeadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("My Head Collider"));

	RootComponent = MyBodyCollider;
	MySprite->SetupAttachment(RootComponent);
	LeftTrigger->SetupAttachment(RootComponent);
	RightTrigger->SetupAttachment(RootComponent);
	HeadTrigger->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	MyBodyCollider -> OnComponentHit.AddDynamic(this, &ABaseEnemy::OnCollision);
	HeadTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseEnemy::OnHeadOverlap);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABaseEnemy::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->KillMario();
	}
}
void ABaseEnemy::OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor->IsA(AMario::StaticClass()))
	{
		Cast<AMario>(OtherActor)->BounceMario(BounceForce);
		Destroy();
	}
}
// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

