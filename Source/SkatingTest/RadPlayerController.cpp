// Fill out your copyright notice in the Description page of Project Settings.


#include "RadPlayerController.h"

void ARadPlayerController::UpdateUI()
{
    if (OnUIUpdate.IsBound())
        OnUIUpdate.Broadcast();
}