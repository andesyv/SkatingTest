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
	FName name;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	EGender type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool found;

	FObjectiveItem(FName _name = "INVALID", EGender _type = EGender::NONBINARY, bool _found = false)
		: name(_name), type(_type), found(_found)
	{

	}
};

USTRUCT(BlueprintType)
struct FAvailableObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EGender type;
	UPROPERTY(EditAnywhere)
	FName displayName;
};

/**
 * 
 */
UCLASS() class SKATINGTEST_API ASkateboardsGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<EGender> availableObjectiveItems;

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

	UPROPERTY(BlueprintReadWrite)
	bool gameover = false;

	UPROPERTY(BlueprintReadOnly)
	bool gamePaused = false;

	UFUNCTION(BlueprintCallable)
	void pauseGame();

	UFUNCTION(BlueprintCallable)
	void unPauseGame();

private:
	void generateObjectives();
	TArray<FObjectiveItem> objectiveItems{};

};
