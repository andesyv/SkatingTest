// Fill out your copyright notice in the Description page of Project Settings.

#include "Skateboard.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
ASkateboard::ASkateboard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	skateboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skateboard"));
	skateboard->SetupAttachment(RootComponent);

	plate = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plate"));
	plate->SetupAttachment(skateboard);



	UE_LOG(LogTemp, Warning, TEXT("Hallo"))
}

// Called when the game starts or when spawned
void ASkateboard::BeginPlay()
{
	Super::BeginPlay();

	if (plate)
		UE_LOG(LogTemp, Warning, TEXT("Plate created"))
	else
		UE_LOG(LogTemp, Warning, TEXT("What"))

	movementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent());
}

// Called every frame
void ASkateboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(plate)
		plate->SetWorldRotation(FRotator(0, GetActorRotation().Yaw, 0));

}

// Called to bind functionality to input
void ASkateboard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASkateboard::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASkateboard::MoveRight);
}

void ASkateboard::MoveForward(float axis)
{
	if (axis != 0.0f && !movementComponent->IsFalling())
		AddMovementInput(GetActorForwardVector() * axis);
}

void ASkateboard::MoveRight(float axis)
{
	if (axis == 0.0f) return;

	auto velocityMagnitude = GetVelocity().Size();
	if (velocityMagnitude < 1.0f) return;

	auto angle = axis * RotationSpeedFactor * velocityMagnitude;
	auto rotationVector = UKismetMathLibrary::RotateAngleAxis(GetVelocity(), angle, GetActorUpVector());

	movementComponent->Velocity = rotationVector;

	auto skateBoardWorldRotation = skateboard->GetComponentRotation();

	if (movementComponent->IsFalling())
	{
		auto rotation = rotationVector.Rotation();
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
			auto cross = FVector::CrossProduct(skateboard->GetForwardVector(), hitResult.Normal);
			auto otherCross = FVector::CrossProduct(hitResult.Normal, skateboard->GetRightVector());
			auto rotator = UKismetMathLibrary::MakeRotFromYX(cross, otherCross);
			rotator.Roll = -rotator.Roll;
			rotator.Pitch = -rotator.Pitch;

			auto newRotation = UKismetMathLibrary::RLerp(skateBoardWorldRotation, rotator, RotateLerping, true);
			skateboard->SetWorldRotation(newRotation);
		}
	}
}