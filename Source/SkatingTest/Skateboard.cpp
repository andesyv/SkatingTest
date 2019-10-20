// Fill out your copyright notice in the Description page of Project Settings.

#include "Skateboard.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASkateboard::ASkateboard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	playerCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Player collider"));
	RootComponent = playerCollider;

	movementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement Component"));

	skateboard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Skateboard"));
	skateboard->SetupAttachment(playerCollider);
}

// Called when the game starts or when spawned
void ASkateboard::BeginPlay()
{
	Super::BeginPlay();
	
	playerCollider->SetSimulatePhysics(true);

}

// Called every frame
void ASkateboard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	if (!inAir())
		AddMovementInput(GetActorForwardVector() * axis);
}

void ASkateboard::MoveRight(float axis)
{
	// AddMovementInput(GetActorRightVector() * axis);
	auto newVelocity = GetVelocity().RotateAngleAxis(GetVelocity().Size() * axis * TurningStrength, GetActorUpVector());
	UE_LOG(LogTemp, Warning, TEXT("Old velocity: %s, new Velocity: %s"), *GetVelocity().ToString(), *newVelocity.ToString());
	playerCollider->SetAllPhysicsLinearVelocity(newVelocity);
}

bool ASkateboard::inAir() const
{
	FHitResult result;
	auto start = GetActorLocation();
	auto end = start + (-GetActorUpVector()) * (playerCollider->GetScaledCapsuleHalfHeight() + 30.f);
	FCollisionQueryParams collisionParams;

	if (GetWorld()
		->LineTraceSingleByChannel(result, start, end, ECollisionChannel::ECC_GameTraceChannel1, collisionParams))
		{
			return false;
		}
	return true;
}