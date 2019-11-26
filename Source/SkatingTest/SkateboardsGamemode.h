// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SkateboardsGamemode.generated.h"

class APickupableCpp;

USTRUCT(BlueprintType)
struct FObjectiveItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UClass* objectiveType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APickupableCpp* object;

	FObjectiveItem(FString _name = "INVALID", UClass* _type = nullptr, APickupableCpp* _obj = nullptr)
		: name(_name), objectiveType(_type), object(_obj)
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<TSubclassOf<APickupableCpp>> availableObjectiveItems;

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

};
