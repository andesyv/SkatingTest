// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkateboardsGamemode.generated.h"

class APickupableCpp;

/**
 * 
 */
UCLASS() class SKATINGTEST_API ASkateboardsGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<APickupableCpp>> availableObjectiveItems;

	UPROPERTY(EditDefaultsOnly)
	unsigned int playerCount = 3;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
