// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PickupableCpp.h"
#include "SkateboardsGamemode.generated.h"

USTRUCT(BlueprintType)
struct FObjectiveItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSubclassOf<class APickupableCpp> objectType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APickupableCpp* comparisonObject;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APickupableCpp* object;

	FObjectiveItem(TSubclassOf<class APickupableCpp> _type = {}, FString _name = "INVALID", APickupableCpp* _compObj = nullptr, APickupableCpp* _obj = nullptr)
		: name(_name), objectType(_type), comparisonObject(_compObj), object(_obj)
	{

	}
};

/**
 * 
 */
UCLASS() class SKATINGTEST_API ASkateboardsGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class APickupableCpp>> availableObjectiveItems;

	UPROPERTY(EditDefaultsOnly)
	unsigned int playerCount = 3;

	UPROPERTY(EditDefaultsOnly)
	unsigned int objectiveCount = 3;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void setupViewport();

	UFUNCTION(BlueprintPure)
	TArray<FObjectiveItem> getObjectives() const;

private:
	void generateObjectives();
	TArray<FObjectiveItem> objectiveItems{};

private:
	void spawnDummyObjects();

};
