// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupableCpp.generated.h"

UENUM(BlueprintType)
enum class EGender : uint8
{
	WINE,
	GRAPE,
	CROWN,
	NONBINARY
};

UCLASS()
class SKATINGTEST_API APickupableCpp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupableCpp();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	EGender type{EGender::NONBINARY};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure)
	EGender getType() const { return type; }

};
