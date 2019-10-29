// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupActor.h"

// Sets default values
APickupActor::APickupActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Mesh as a root.
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMesh"));
	MainMesh->SetupAttachment(RootComponent);

	// Enable physics for the root component
	MainMesh->SetGenerateOverlapEvents(false);
	MainMesh->SetCollisionProfileName(TEXT("BlockAll"));
	MainMesh->SetSimulatePhysics(true);

	// Setup collider for forcer
	PickupCollider = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollider"));
	PickupCollider->InitSphereRadius(50.0f);
	PickupCollider->SetupAttachment(MainMesh);

	// Set up forcer collider overlap responses
	PickupCollider->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnPickupOverlapBegin);
	PickupCollider->OnComponentEndOverlap.AddDynamic(this, &APickupActor::OnPickupOverlapEnd);
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupActor::OnPickupOverlapBegin(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AMainPlayerCharacter *PlayerCharacter = Cast<AMainPlayerCharacter>(OtherActor);
		if (PlayerCharacter != nullptr)
		{
			AMainPlayerController *PlayerContr = Cast<AMainPlayerController>(PlayerCharacter->GetController());
			PlayerContr->OverlappingPickupActors.AddUnique(this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Pickup-Component: overlapped with player"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pickup-Component: all casts failed"));
		}
	}
}

void APickupActor::OnPickupOverlapEnd(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor, class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AMainPlayerCharacter *PlayerCharacter = Cast<AMainPlayerCharacter>(OtherActor);
		if (PlayerCharacter != nullptr)
		{
			AMainPlayerController *PlayerContr = Cast<AMainPlayerController>(PlayerCharacter->GetController());
			PlayerContr->OverlappingPickupActors.Remove(this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Pickup-Component: overlap with player ended"));
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Pickup-Component: all casts failed on overlap end"));
		}
	}
}

void APickupActor::Interact_Implementation(AMainPlayerController *PlayerControllerRef)
{
	int RestAmount = 0;
	bool Success = PlayerControllerRef->Inventory->AddItem(ItemNameToAdd, Amount, RestAmount);
	LiveOrDie(Success, RestAmount);
}

void APickupActor::LiveOrDie(bool bWasSuccessful, int RestAmount)
{
	if (bWasSuccessful)
	{
		if (RestAmount == 0)
		{
			Destroy();
		}
		else
		{
			Amount = RestAmount;
		}
		
	}
}

