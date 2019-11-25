// Fill out your copyright notice in the Description page of Project Settings.


#include "SkateboardsGamemode.h"
#include "Kismet/GameplayStatics.h"

void ASkateboardsGamemode::BeginPlay()
{
    Super::BeginPlay();

    if (playerCount > 1)
    {
        for (unsigned i{0}; i < playerCount; ++i)
        {
            UGameplayStatics::CreatePlayer(this, -1, true);
        }
    }
    else
    {
        
    }
}
