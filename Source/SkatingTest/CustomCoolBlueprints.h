// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomCoolBlueprints.generated.h"

/**
 * 
 */
UCLASS()
class SKATINGTEST_API UCustomCoolBlueprints : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	public:
	UFUNCTION(BlueprintPure, Category = "Math|Rotator")
	static FQuat toQuat(const FRotator& rot);
};
