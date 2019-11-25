// Fill out your copyright notice in the Description page of Project Settings.


#include "SkateboardsGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "PickupableCpp.h"

void ASkateboardsGamemode::BeginPlay()
{
    Super::BeginPlay();

    if (1 < playerCount)
    {
        for (unsigned i{1}; i < playerCount; ++i)
        {
            UGameplayStatics::CreatePlayer(this, -1, true);
        }
    }

    setupViewport();


}

void ASkateboardsGamemode::generateObjectives()
{
    for (unsigned int i{0}; i < objectiveCount; ++i)
    {
        auto obj = availableObjectiveItems[FMath::RandRange(0, availableObjectiveItems.Num())];
        objectiveItems.Push({obj->GetName(), obj->StaticClass(), nullptr});
    }
}

TArray<FObjectiveItem> ASkateboardsGamemode::getObjectives() const
{
    return objectiveItems;
}