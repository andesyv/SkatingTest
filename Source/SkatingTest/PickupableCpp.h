// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupableCpp.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class SKATINGTEST_API APickupableCpp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupableCpp();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UBoxComponent* pickupBox = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
