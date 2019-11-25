// Fill out your copyright notice in the Description page of Project Settings.


#include "Skateboard4Cpp.h"

// Sets default values
ASkateboard4Cpp::ASkateboard4Cpp()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASkateboard4Cpp::AddToTray(APickupableCpp* obj)
{
	if (mTray == nullptr || obj == nullptr)
		return;

	obj->SetActorEnableCollision(false);
	obj->AttachToComponent(mTray, FAttachmentTransformRules{
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepWorld,
		false
	});

	if (mLastTrayItem < 0 || TrayObjects.Num() <= mLastTrayItem)
		return;
	
	auto oldObj = TrayObjects[mLastTrayItem];
	if (oldObj != nullptr && IsValid(oldObj))
	{
		oldObj->Destroy();
	}

	TrayObjects[mLastTrayItem] = obj;

}

// Called when the game starts or when spawned
void ASkateboard4Cpp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkateboard4Cpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASkateboard4Cpp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

