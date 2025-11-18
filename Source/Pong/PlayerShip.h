// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound/SoundCue.h"
#include "Explotion.h"
#include "CoreMinimal.h"
#include "SpaceShip.h"
#include "PlayerShip.generated.h"

/**
 * 
 */
UCLASS()
class PONG_API APlayerShip : public ASpaceShip
{
	GENERATED_BODY()

public:
    APlayerShip();
    void DestroyShip();
    void HandleDestruction();

    UPROPERTY(EditAnywhere, Category = "Bomb")
    TSubclassOf<class ABomb> BombClass; // Bomb class reference

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void MoveVertical(float Input);
    void MoveHorizontal(float Input);
    void Fire();
    void Bomb();  // Function to trigger the bomb

    void DestroyAllEnemiesAndObstacles();  // Helper function to destroy enemies and obstacles
    void GetScreenBounds(FVector2D& OutMin, FVector2D& OutMax);  // Helper function to get screen bounds

    UPROPERTY(EditAnywhere, Category = "Movement")
    float VerticalSpeed;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float HorizontalSpeed;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    TSubclassOf<class AFireAmmo> FireBPClass;

    UPROPERTY(EditDefaultsOnly, Category = "Destruction")
    TSubclassOf<class AExplotion> ExplosionClass;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundCue* DestructionSoundCue;

    UPROPERTY(EditAnywhere, Category = "Sound")
    USoundCue* FiringSoundCue;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* CameraComponent;

    void OnDestructionComplete();
    void OnCollisionWithEnemy(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
	
