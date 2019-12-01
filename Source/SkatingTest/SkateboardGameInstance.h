// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SkateboardGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SKATINGTEST_API USkateboardGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int numPlayers{ 1 };
	
};
