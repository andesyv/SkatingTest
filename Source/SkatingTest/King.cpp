// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "Skateboard.h"
#include "SkateboardsGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
AKing::AKing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKing::BeginPlay()
{
	Super::BeginPlay();

	Gamemode = Cast<ASkateboardsGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

// Called every frame
void AKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AKing::hasWon(ASkateboard* player)
{
	if (!player)
		return false;

	auto objectives = Gamemode->getObjectives();
	auto playerObjects = player->getTrayObjects();

	for (int i = 0; i < playerObjects.Num(); ++i)
	{
		// Because we intialize all tray objects to nullptr.
		if (playerObjects[i] == nullptr)
			continue;

		for (int j = 0; j < objectives.Num(); ++j)
		{
			if (playerObjects[i]->getType() == objectives[j].type)
			{
				objectives.RemoveAt(j);
				break;
			}
		}
	}

	Gamemode->gameover = objectives.Num() == 0;

	return objectives.Num() == 0;
}

