// Fill out your copyright notice in the Description page of Project Settings.


#include "Mario.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h"
#include "MarioGameMode.h"


// Sets default values
AMario::AMario()
{
    // Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MySprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("MarioBodySprite"));
    MyBodyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MarioBodyCapsule"));
    MySpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MarioSpringArm"));
    MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MarioBodyCamera"));

    // Set up component hierarchy
    RootComponent = MyBodyCollider; // Make collider root so the sprite follows collider
    MySprite->SetupAttachment(RootComponent); // Attach the sprite to the collider
    MySpringArm->SetupAttachment(RootComponent); // Attach the spring arm to the root
    MyCamera->SetupAttachment(MySpringArm); // Attach the camera to the spring arm

    MyBodyCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // Initialize dead flag
    bIsDead = false;
}

// Called when the game starts or when spawned
void AMario::BeginPlay()
{
    Super::BeginPlay();

    // Bind the OnCollision function
    MyBodyCollider->OnComponentHit.AddDynamic(this, &AMario::OnCollision);
    MyBodyCollider->OnComponentBeginOverlap.AddDynamic(this, &AMario::OnOverlapWithWinningSprite); 

    // Set the default animation states
    CurrentAnimationState = RedHatBoy::AS_IDLE;
    OldAnimationState = RedHatBoy::AS_EMPTY;

    // Process the state to set the initial state
    ProcessAnimStateMachine();
}
void AMario::OnOverlapWithWinningSprite(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bIsDead && OtherActor->ActorHasTag("WinningCondition")) // Check for the tag "WinningCondition"
    {
        UE_LOG(LogTemp, Warning, TEXT("Mario overlapped with Winning Sprite!"));
        // Handle winning condition here
        UGameplayStatics::OpenLevel(GetWorld(), "L_WinScreen"); // Example: Load a win screen level
    }
}

void AMario::MovePlayerHorizontal(float Value)
{
    if (!bIsDead) {
        MyBodyCollider->AddForce(FVector(0, 1, 0) * Value * PlayerAcceleration, NAME_None, true);
    }
}

void AMario::Jump()
{
    if (!bIsDead) {
        // Log message to check if jumping
        UE_LOG(LogTemp, Warning, TEXT("Trying to Jump"));
        if (!bIsJumping)
        {
            MyBodyCollider->AddImpulse(FVector(0, 0, 1) * JumpForce);
            bIsJumping = true;
            CurrentAnimationState = RedHatBoy::AS_JUMPING; // Set animation state to jumping
            UE_LOG(LogTemp, Warning, TEXT("Jump Done")); // Log if jump is successful
        }
    }
}

// Called every frame
void AMario::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!bIsDead) {
        // Clamp maximum speed in the Y direction to player speed
        FVector ClampedSpeed = MyBodyCollider->GetPhysicsLinearVelocity();
        ClampedSpeed.Y = FMath::Clamp(ClampedSpeed.Y, -PlayerMaxSpeed, PlayerMaxSpeed);
        MyBodyCollider->SetPhysicsLinearVelocity(ClampedSpeed);

        // Check if Mario has fallen below the water level
        if (GetActorLocation().Z < WaterLevelThreshold) {
            KillMario();
        }

        // Update the animation state every frame
       // IdentifyAnimStates();
        //ProcessAnimStateMachine();
    }
    IdentifyAnimStates();
    ProcessAnimStateMachine();
}

// Called to bind functionality to input
void AMario::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Bind input for horizontal movement and jump action
    PlayerInputComponent->BindAxis("Horizontal", this, &AMario::MovePlayerHorizontal);
    PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AMario::Jump);
}

void AMario::IdentifyAnimStates()
{
    if (!bIsDead) {
        OldAnimationState = CurrentAnimationState;
        float CurrentSpeed = MyBodyCollider->GetPhysicsLinearVelocity().Y;

        if (bIsJumping)
        {
            CurrentAnimationState = RedHatBoy::AS_JUMPING;
        }
        else if (CurrentSpeed > 5)
        {
            CurrentAnimationState = RedHatBoy::AS_WALKING_RIGHT;
        }
        else if (CurrentSpeed < -5)
        {
            CurrentAnimationState = RedHatBoy::AS_WALKING_LEFT;
        }
        else
        {
            CurrentAnimationState = RedHatBoy::AS_IDLE;
        }
        UE_LOG(LogTemp, Warning, TEXT("Current Speed: %f, Animation State: %d"), CurrentSpeed, (int32)CurrentAnimationState);
    }
}

void AMario::ProcessAnimStateMachine()
{
    if (CurrentAnimationState == OldAnimationState)
    {
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Changing Animation State from %d to %d"), (int32)OldAnimationState, (int32)CurrentAnimationState);

    switch (CurrentAnimationState)
    {
    case RedHatBoy::AS_IDLE:
        MySprite->SetFlipbook(Flipbook_Idle);
        UE_LOG(LogTemp, Warning, TEXT("Set to Idle Animation"));
        break;
    case RedHatBoy::AS_WALKING_RIGHT:
        MySprite->SetFlipbook(Flipbook_WalkingRight);
        UE_LOG(LogTemp, Warning, TEXT("Set to Walking Right Animation"));
        MySpringArm->SetRelativeRotation(FRotator(0, 0, 180));
        break;
    case RedHatBoy::AS_WALKING_LEFT:
        MySprite->SetFlipbook(Flipbook_WalkingRight);
        UE_LOG(LogTemp, Warning, TEXT("Set to Walking Left Animation"));
        MySpringArm->SetRelativeRotation(FRotator(0, 0, -180));
        break;
    case RedHatBoy::AS_JUMPING:
        MySprite->SetFlipbook(Flipbook_Jumping);
        UE_LOG(LogTemp, Warning, TEXT("Set to Jumping Animation"));
        break;
    case RedHatBoy::AS_DEAD:
        MySprite->SetFlipbook(Flipbook_Dead);
        UE_LOG(LogTemp, Warning, TEXT("Set to Dead Animation"));
        break;
    }
    OldAnimationState = CurrentAnimationState;
}

void AMario::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
    FVector NormalImpulse, const FHitResult& Hit)
{
    if (!bIsDead) {
        // Log message for the collision, get name when Mario collides
        UE_LOG(LogTemp, Warning, TEXT("Collision with %s"), *OtherActor->GetName());
        if (OtherActor->Tags.Contains("Floor"))
        {
            bIsJumping = false;
            UE_LOG(LogTemp, Warning, TEXT("Collision with Floor: Mario can jump again"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Collision with non-floor object"));
        }
    }
}

void AMario::KillMario()
{
    if (bIsDead) return;

    bIsDead = true;
    UE_LOG(LogTemp, Warning, TEXT("Mario is dead!!"));
    CurrentAnimationState = RedHatBoy::AS_DEAD;
    ProcessAnimStateMachine();

    // Disable physics simulation and collision
    MyBodyCollider->SetSimulatePhysics(false);
    MyBodyCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MyBodyCollider->SetCollisionResponseToAllChannels(ECR_Ignore); // Ensure no collision responses
    DisableInput(nullptr);

    // Set a timer to show the death screen after a delay
    GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AMario::ShowDeathScreen, DeathScreenDelay, false);

    UE_LOG(LogTemp, Warning, TEXT("Death timer set for %f seconds"), DeathScreenDelay);
}

void AMario::ShowDeathScreen()
{
    UE_LOG(LogTemp, Warning, TEXT("Timer completed, showing death screen"));
    UGameplayStatics::OpenLevel(GetWorld(), "L_EndGame");
}

void AMario::BounceMario(float Force)
{
    if (!bIsDead) {
        MyBodyCollider->AddImpulse(FVector(0, 0, Force));
    }
}
