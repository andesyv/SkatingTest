// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "King.generated.h"

UCLASS()
class SKATINGTEST_API AKing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKing();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
	bool hasWon(class ASkateboard* player);

	class ASkateboardsGamemode* Gamemode;
};
