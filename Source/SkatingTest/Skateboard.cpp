// Fill out your copyright notice in the Description page of Project Settings.

#include "Skateboard.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "RadPlayerController.h"
#include "SkateboardsGamemode.h"
#include "PickupableCpp.h"

// Sets default values
ASkateboard::ASkateboard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	skateboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skateboard"));
	skateboard->SetupAttachment(RootComponent);

	Tray = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tray"));
	Tray->SetupAttachment(skateboard);

}

// Called when the game starts or when spawned
void ASkateboard::BeginPlay()
{
	Super::BeginPlay();

	TrayObjects.Init(nullptr, 6);

	movementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());

	gamemode = Cast<ASkateboardsGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void ASkateboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!gamemode->gameover)
		doRotation();

	if(Tray)
	{
		if (0.1f < FMath::Abs(lerpingTrayRotation - desiredTrayRotation))
			lerpingTrayRotation = FMath::Lerp(lerpingTrayRotation, desiredTrayRotation, 0.3f);
		Tray->SetWorldRotation(FRotator(GetActorRotation().Pitch, skateboard->GetComponentRotation().Yaw + lerpingTrayRotation, GetActorRotation().Roll));
	}
}

// Called to bind functionality to input
void ASkateboard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASkateboard::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASkateboard::MoveRight);
	FInputActionBinding ab("RotateTrayRight", EInputEvent::IE_Pressed);
	ab.ActionDelegate.GetDelegateForManualSet().BindLambda([&](){
		ScrollTray(1);
	});
	PlayerInputComponent->AddActionBinding(ab);
	ab = FInputActionBinding{"RotateTrayLeft", EInputEvent::IE_Pressed};
	ab.ActionDelegate.GetDelegateForManualSet().BindLambda([&](){
		ScrollTray(-1);
	});
	PlayerInputComponent->AddActionBinding(ab);
}

void ASkateboard::MoveForward(float axis)
{
	if (gamemode->gameover)
		return;

	if (axis != 0.0f && !movementComponent->IsFalling())
		AddMovementInput(skateboard->GetForwardVector() * axis);
}

void ASkateboard::MoveRight(float axis)
{
	if (axis == 0.0f || gamemode->gameover) return;

	auto velocityMagnitude = GetVelocity().Size();

	auto angle = axis * RotationSpeedFactor * velocityMagnitude;

	if (velocityMagnitude < 1.0f)
		return;

	rotationVector = UKismetMathLibrary::RotateAngleAxis(GetVelocity(), angle, GetActorUpVector());

	movementComponent->Velocity = rotationVector;
}

void ASkateboard::doRotation()
{
	auto skateBoardWorldRotation = skateboard->GetComponentRotation();
	auto rotation = rotationVector.Rotation();

	if (movementComponent->IsFalling())
	{
		rotation.Pitch = FMath::Clamp(rotation.Pitch, -70.f, 70.f);
		auto newRotation = UKismetMathLibrary::RLerp(skateBoardWorldRotation, rotation, RotateLerping, true);
		skateboard->SetWorldRotation(newRotation);
	}
	else
	{
		FHitResult hitResult;
		auto start = GetActorLocation();
		auto end = start + (GetActorUpVector() * -(GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + TraceLength));

		if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_GameTraceChannel1))
		{
			groundNormal = hitResult.Normal;
			auto cross = FVector::CrossProduct(skateboard->GetForwardVector(), groundNormal);
			auto otherCross = FVector::CrossProduct(hitResult.Normal, skateboard->GetRightVector());
			auto rotator = UKismetMathLibrary::MakeRotFromYX(cross, otherCross);
			rotator.Roll = -rotator.Roll;
			rotator.Pitch = -rotator.Pitch;
			rotator.Yaw = rotation.Yaw;

			auto newRotation = UKismetMathLibrary::RLerp(skateBoardWorldRotation, rotator, RotateLerping, true);
			skateboard->SetWorldRotation(newRotation);
		}
	}
}

void ASkateboard::ScrollTray(int right)
{
	if (gamemode->gameover)
		return;

	desiredTrayRotation += right * (360.f / TrayObjects.Num());
}

void ASkateboard::AddToTray(APickupableCpp* pickupable)
{
	pickupable->SetActorEnableCollision(false);
	pickupable->AttachToComponent(Tray, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepWorld, false));

	if (auto lastPickupable = TrayObjects[LastTrayItem])
	{
		lastPickupable->Destroy();
	}

	TrayObjects[LastTrayItem] = pickupable;
	TrayObjects[LastTrayItem]->SetActorLocation(GetPosOnTray(LastTrayItem));

	LastTrayItem = ++LastTrayItem % TrayObjects.Num();

	auto controller = GetController();
	if (controller)
	{
		auto playercon = Cast<ARadPlayerController>(controller);
		if (IsValid(playercon))
		{
			playercon->UpdateUI();
		}
	}
}


FVector ASkateboard::GetPosOnTray(int index)
{
	FVector vector{TrayRadius, 0, 0};
	vector = UKismetMathLibrary::RotateAngleAxis(vector, (360.f / TrayObjects.Num()) * index, Tray->GetUpVector());
	return Tray->GetComponentQuat().RotateVector(vector) + Tray->GetComponentLocation();
}

TArray<APickupableCpp*> ASkateboard::getTrayObjects()
{
	return TrayObjects;
}
