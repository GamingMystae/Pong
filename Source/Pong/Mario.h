// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperFlipbookComponent.h"
#include "MarioGameMode.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Mario.generated.h"

UENUM()
enum class  RedHatBoy :uint8
{
	AS_IDLE,
	AS_WALKING_RIGHT,
	AS_WALKING_LEFT,
	AS_JUMPING,  
	AS_EMPTY,
	AS_DEAD,
};
UCLASS()
class PONG_API AMario : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMario();

	// Declaration for the sprite component
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;

	// Capsule component
	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;

	// Spring arm component for the camera to follow Mario
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
	class USpringArmComponent* MySpringArm;

	// Camera component
	UPROPERTY(VisibleAnywhere, Category = "Camera Setup")
	class UCameraComponent* MyCamera;

	// Properties for player movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
	float JumpForce = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
	float PlayerAcceleration = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Properties")
	float PlayerMaxSpeed = 32.0f;

	// List of animations for this actor
	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_WalkingRight;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Idle;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Dead;


	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	class UPaperFlipbook* Flipbook_Jumping;  // Added flipbook for jumping animation

	// Current and previous animation state of the actor
	UPROPERTY(VisibleAnywhere, Category = "Animations")
	RedHatBoy CurrentAnimationState;

	UPROPERTY(VisibleAnywhere, Category = "Animations")
	RedHatBoy OldAnimationState;

	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

	void KillMario();
	void BounceMario(float Force);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnOverlapWithWinningSprite(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void IdentifyAnimStates();
	void ProcessAnimStateMachine();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MovePlayerHorizontal(float Value);
	void Jump();
	bool bIsJumping;
	// Function to show UI screen after delay
	void ShowDeathScreen();
	FTimerHandle DeathTimerHandle;

	// Delay before showing the death screen
	UPROPERTY(EditDefaultsOnly, Category = "Player Properties")
	float DeathScreenDelay = 1.0f; // Delay in seconds
	// Flag to indicate if Mario is dead
	bool bIsDead;

	// Y-level threshold for death
	UPROPERTY(EditDefaultsOnly, Category = "Player Properties")
	float WaterLevelThreshold = -200.0f; // when mario falls or out of the level

};