// Fill out your copyright notice in the Description page of Project Settings.


#include "Skateboard4.h"

// Sets default values
ASkateboard4::ASkateboard4()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkateboard4::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkateboard4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkateboard4::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

