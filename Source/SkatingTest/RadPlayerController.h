// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RadPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUIUpdateEvent);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class SKATINGTEST_API ARadPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void UpdateUI();

	UPROPERTY(BlueprintAssignable)
	FUIUpdateEvent OnUIUpdate;
};	
