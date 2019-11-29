// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupableCpp.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Skateboard.h"

// Sets default values
APickupableCpp::APickupableCpp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	object = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object"));
	RootComponent = object;

	pickupZone = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupZone"));
	pickupZone->SetupAttachment(object);
	pickupZone->SetCollisionProfileName("OverlapAllDynamic");
	pickupZone->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void APickupableCpp::BeginPlay()
{
	Super::BeginPlay();
	
	// pickupZone->OnComponentBeginOverlap.AddDynamic(this, &APickupableCpp::OnOverlap);
}

// Called every frame
void APickupableCpp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupableCpp::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
								int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Yo!"));

	if (auto skateboard = Cast<ASkateboard>(OtherActor))
		skateboard->AddToTray(this);
}

