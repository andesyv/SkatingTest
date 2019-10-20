// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Skateboard.generated.h"

class UFloatingPawnMovement;
class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class SKATINGTEST_API ASkateboard : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASkateboard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UFloatingPawnMovement* movementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCapsuleComponent* playerCollider = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* skateboard = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TurningStrength = 0.0001f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float axis);

	void MoveRight(float axis);

	bool inAir() const;

};
