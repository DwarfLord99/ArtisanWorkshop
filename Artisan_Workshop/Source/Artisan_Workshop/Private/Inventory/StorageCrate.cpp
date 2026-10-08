// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/StorageCrate.h"
#include "Player/AWorkshopCharacter.h"

// Sets default values
AStorageCrate::AStorageCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a StaticMeshComponent for the crate
	CrateMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrateMesh"));
	RootComponent = CrateMeshComponent;

	// Create the InventoryComponent
	StorageInventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

}

// Called when the game starts or when spawned
void AStorageCrate::BeginPlay()
{
	Super::BeginPlay();

	// Print out the current inventory for debugging
	UE_LOG(LogTemp, Log, TEXT("Storage Crate Inventory:"));
	for (const FInventorySlot& Slot : StorageInventoryComponent->InventorySlots)
	{
		if (Slot.ItemDefinition)
		{
			UE_LOG(LogTemp, Log, TEXT(" - %s: %d"), *Slot.ItemDefinition->GetName(), Slot.Quantity);
		}
	}
	
}

// Implement the Interact function from IInteractable
void AStorageCrate::Interact(AActor* Interactor)
{
	// Open the storage UI for the player interacting with the crate
	if (AAWorkshopCharacter* WorkshopCharacter = Cast<AAWorkshopCharacter>(Interactor))
	{
		if (StorageWidget)
		{
			StorageWidget->AddToViewport();
			StorageWidget->SetInventorySources(WorkshopCharacter->GetInventoryComponent(), StorageInventoryComponent);

			APlayerController* PlayerController = Cast<APlayerController>(WorkshopCharacter->GetController());
			if (PlayerController)
			{
				PlayerController->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PlayerController->SetInputMode(InputMode);
			}
		}
	}
}

FText AStorageCrate::GetInteractionPrompt_Implementation() const
{
	return FText::FromString("Open Storage Crate");
}
