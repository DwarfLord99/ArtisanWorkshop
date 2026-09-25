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
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

}

// Called when the game starts or when spawned
void AStorageCrate::BeginPlay()
{
	Super::BeginPlay();

	// Print out the current inventory for debugging
	UE_LOG(LogTemp, Log, TEXT("Storage Crate Inventory:"));
	for (const FInventorySlot& Slot : InventoryComponent->InventorySlots)
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
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Interacted with Storage Crate."));
	}

	AAWorkshopCharacter* Player = Cast<AAWorkshopCharacter>(Interactor);
	if (Player && Player->GetInventoryComponent())
	{
		// Remove item from player inventory and add to crate inventory
		// For demonstration, let's assume we are removing the first item in the player's inventory
		if (Player->GetInventoryComponent()->InventorySlots.Num() > 0)
		{
			FInventorySlot& PlayerSlot = Player->GetInventoryComponent()->InventorySlots[0];
			if (PlayerSlot.ItemDefinition && PlayerSlot.Quantity >= 0)
			{
				// Add the item to the crate's inventory
				InventoryComponent->AddItem(PlayerSlot.ItemDefinition);
				// Remove the item from the player's inventory
				Player->GetInventoryComponent()->RemoveItem(PlayerSlot.ItemDefinition);
				UE_LOG(LogTemp, Log, TEXT("Moved item from player to Storage Crate."));

				// Print out the current inventory for debugging for both player and crate
				UE_LOG(LogTemp, Log, TEXT("Player Inventory:"));
				for (const FInventorySlot& Slot : Player->GetInventoryComponent()->InventorySlots)
				{
					if (Slot.ItemDefinition)
					{
						UE_LOG(LogTemp, Log, TEXT(" - %s: %d"), *Slot.ItemDefinition->GetName(), Slot.Quantity);
					}
				}
				UE_LOG(LogTemp, Log, TEXT("Storage Crate Inventory:"));
				for (const FInventorySlot& Slot : InventoryComponent->InventorySlots)
				{
					if (Slot.ItemDefinition)
					{
						UE_LOG(LogTemp, Log, TEXT(" - %s: %d"), *Slot.ItemDefinition->GetName(), Slot.Quantity);
					}
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player has no items to move to Storage Crate."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player's inventory is empty."));
		}
	}
}
