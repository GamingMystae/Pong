// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFrameWork/Actor.h"
#include "BaseEnemy.generated.h"


UCLASS()
class PONG_API ABaseEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseEnemy();

protected: // entering in protecting for using them from childs
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, Category = "Sprites")
	class UPaperFlipbookComponent* MySprite;// declare a pointer to the class UPaperSprite  with the name MySprite 

	// creat a cappslue component
	UPROPERTY(VisibleAnywhere, Category = "Collider")
	class UCapsuleComponent* MyBodyCollider;
	
	//collison for left side
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* LeftTrigger;

	////collison for right side
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* RightTrigger;

	//collision for head
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* HeadTrigger;
	
	UFUNCTION()
	virtual void OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnHeadOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	
	UPROPERTY(EditAnywhere, Category="Player Properties")
	
	float BounceForce = 10;




public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
