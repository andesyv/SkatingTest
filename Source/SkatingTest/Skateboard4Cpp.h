// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Skateboard4Cpp.generated.h"
#include "PickupableCpp.h"
#include "Components/ActorComponent.h"

UCLASS()
class SKATINGTEST_API ASkateboard4Cpp : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkateboard4Cpp();

	TArray<APickupableCpp*> TrayObjects;

	void AddToTray(APickupableCpp* obj);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* mTray = nullptr;

	int mLastTrayItem{0};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
