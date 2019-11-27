// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skateboard.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UCharacterMovementComponent;
class APickupableCpp;

UCLASS()
class SKATINGTEST_API ASkateboard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASkateboard();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float axis);

	void MoveRight(float axis);
	void doRotation();

	UFUNCTION(BlueprintCallable)
	void AddToTray(APickupableCpp* pickupable);

	UFUNCTION(BlueprintPure)
	TArray<APickupableCpp*> getTrayObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* skateboard = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Tray = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float TurningStrength = 0.0001f;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeedFactor = 0.001f;

	UPROPERTY(EditDefaultsOnly)
	float RotateLerping = 0.3f;

	FVector rotationVector;

	UPROPERTY(EditDefaultsOnly)
	float TraceLength = 20.f;

	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* movementComponent;

	UPROPERTY(EditDefaultsOnly)
	float TrayRadius = 40.f;

	int LastTrayItem = 0;

	TArray<APickupableCpp*> TrayObjects;

private:
	FVector GetPosOnTray(int index);

	FVector groundNormal;
};
