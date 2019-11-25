// Fill out your copyright notice in the Description page of Project Settings.


#include "SkateboardsGamemode.h"
#include "Kismet/GameplayStatics.h"

void ASkateboardsGamemode::BeginPlay()
{
    Super::BeginPlay();

    if (multiplayer)
    {
        UGameplayStatics::CreatePlayer(this, -1, true);
        UGameplayStatics::CreatePlayer(this, -1, true);
        UGameplayStatics::CreatePlayer(this, -1, true);
    }
    else
    {
         
    }
}
