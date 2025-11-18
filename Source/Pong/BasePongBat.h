#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "BasePongBat.generated.h"

UCLASS()
class PONG_API ABasePongBat : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ABasePongBat();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Declaration for the sprite
    UPROPERTY(VisibleAnywhere, Category = "Sprite")
    class UPaperSpriteComponent* MySprite;

    // Declaration for collision box
    UPROPERTY(VisibleAnywhere, Category = "Collision")
    class UBoxComponent* MyCollider;

    UFUNCTION()
    virtual void OnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
    
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    FVector MyVelocity;
    float HalfBatHeight;
    float HalfBatWidth;
    float HalfPlayFieldHeight;
    float HalfPlayFieldWidth;
};



