
#include "PeggleBlock.h"
#include "PaperSpriteComponent.h"
// Sets default values
APeggleBlock::APeggleBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MySprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("My Image"));
	
	RootComponent = MySprite;
	
}
// Called when the game starts or when spawned
void APeggleBlock::BeginPlay()
{
	Super::BeginPlay();
	MySprite->OnComponentHit.AddDynamic(this, &APeggleBlock::OnHit);
	
}
// Called every frame
void APeggleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void APeggleBlock::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("HIT!"));
	if (!DestroyTimer.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting Timer"));
		GetWorld()->GetTimerManager().SetTimer(DestroyTimer,
			this, &APeggleBlock::DestroyThisObject, 1.0, false);

	}
}
void APeggleBlock::DestroyThisObject()
{
	Destroy();
}
void APeggleBlock::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (MySprite)
	{
		MySprite->SetNotifyRigidBodyCollision(true);
	}
}
