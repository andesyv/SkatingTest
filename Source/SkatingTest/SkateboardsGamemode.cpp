// Fill out your copyright notice in the Description page of Project Settings.


#include "SkateboardsGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "PickupableCpp.h"
#include "Engine/World.h"

void ASkateboardsGamemode::BeginPlay()
{
    Super::BeginPlay();

    generateObjectives();

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
    objectiveItems.Reserve(objectiveCount);
    if (0 < availableObjectiveItems.Num())
    {
        for (unsigned int i{0}; i < objectiveCount; ++i)
        {
            auto& obj = availableObjectiveItems[FMath::RandRange(0, availableObjectiveItems.Num() - 1)];
            objectiveItems.Push({obj, obj->GetDisplayNameText().ToString(), nullptr, nullptr});
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No objective items in gamemode!"));
    }

    spawnDummyObjects();
}

TArray<FObjectiveItem> ASkateboardsGamemode::getObjectives() const
{
    return objectiveItems;
}

void ASkateboardsGamemode::spawnDummyObjects()
{
    auto world = GetWorld();
    if (!world)
        return;

    for (auto &item : objectiveItems)
    {
        FActorSpawnParameters spawnParams{};
        spawnParams.Name = FName{*FString{"Dummy_" + item.name}};
        const FTransform spawnTrans{FQuat::Identity, FVector{0.f, 0.f, -100.f}};
        auto actor = world->SpawnActor<APickupableCpp>(item.objectType, spawnTrans, spawnParams);
        item.comparisonObject = actor;
    }
}