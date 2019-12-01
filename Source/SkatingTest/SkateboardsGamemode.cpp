// Fill out your copyright notice in the Description page of Project Settings.


#include "SkateboardsGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "PickupableCpp.h"
#include "Engine/World.h"
#include "SkateboardGameInstance.h"

void ASkateboardsGamemode::BeginPlay()
{
    Super::BeginPlay();

    generateObjectives();

	auto instance = Cast<USkateboardGameInstance>(GetGameInstance());
	if (!instance)
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong game instance setup!"))
		return;
	}

	playerCount = instance->numPlayers;

    if (1 < playerCount)
    {
        for (unsigned i{1}; i < playerCount; ++i)
        {
           auto playerController =  UGameplayStatics::CreatePlayer(this, -1, true);
		   playerController->SetInputMode(FInputModeGameOnly());
        }
    }

	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playerController->SetInputMode(FInputModeGameOnly());
	playerController->SetTickableWhenPaused(true);

    setupViewport();


}

void ASkateboardsGamemode::pauseGame()
{
	gamePaused = true;
	UGameplayStatics::SetGamePaused(GetWorld(), gamePaused);
	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playerController->bShowMouseCursor = true;
	playerController->SetInputMode(FInputModeUIOnly());
}

void ASkateboardsGamemode::unPauseGame()
{
	gamePaused = false;
	UGameplayStatics::SetGamePaused(GetWorld(), gamePaused);
	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	playerController->bShowMouseCursor = false;
	playerController->SetInputMode(FInputModeGameOnly());
}

void ASkateboardsGamemode::generateObjectives()
{
    objectiveItems.Reserve(objectiveCount);
    if (0 < availableObjectiveItems.Num())
    {
        for (unsigned int i{0}; i < objectiveCount; ++i)
        {
            auto& obj = availableObjectiveItems[FMath::RandRange(0, availableObjectiveItems.Num() - 1)];
            FName name;
            switch (obj)
            {
                case EGender::GRAPE:
                name = "Grape";
                break;
                case EGender::WINE:
                name = "Wine";
                break;
                case EGender::CROWN:
                name = "Kings crown";
                break;
                case EGender::CHICKEN:
                name = "Chicken";
                break;
                default:
                name = "INVALID";
                break;
            }

            objectiveItems.Push({name, obj});
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No objective items in gamemode!"));
    }
}

TArray<FObjectiveItem> ASkateboardsGamemode::getObjectives() const
{
    return objectiveItems;
}