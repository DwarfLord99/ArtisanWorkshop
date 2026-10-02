// Fill out your copyright notice in the Description page of Project Settings.


#include "Economy/MerchantCounter.h"
#include "Player/AWorkshopCharacter.h"

// Sets default values
AMerchantCounter::AMerchantCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the MerchantCounterMesh component
	MerchantCounterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MerchantCounterMesh"));
	RootComponent = MerchantCounterMesh;

	// Create the InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void AMerchantCounter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Implement the Interact function from the IInteractable interface
void AMerchantCounter::Interact(AActor* Interactor)
{
	// Implement interaction logic here
	// For example, you could open a UI for the player to sell items

	AAWorkshopCharacter* Player = Cast<AAWorkshopCharacter>(Interactor);
	if (Player && Player->GetInventoryComponent()->InventorySlots.Num() > 0)
	{
		// For debugging purposes, add the first item from the player's inventory to the merchant's inventory
		FInventorySlot& PlayerSlot = Player->GetInventoryComponent()->InventorySlots[0];
		if (PlayerSlot.ItemDefinition && PlayerSlot.Quantity > 0)
		{
			// Add the item to the merchant's inventory
			InventoryComponent->AddItem(PlayerSlot.ItemDefinition);
			// Remove the item from the player's inventory
			Player->GetInventoryComponent()->RemoveItem(PlayerSlot.ItemDefinition);
			UE_LOG(LogTemp, Log, TEXT("Moved item from player to merchant counter."));
		}
	}

	// For demonstration, let's assume we are selling the first item in the merchant's inventory
	if (InventoryComponent->InventorySlots.Num() > 0)
	{
		FInventorySlot& MerchantSlot = InventoryComponent->InventorySlots[0];
		if (MerchantSlot.ItemDefinition && MerchantSlot.Quantity > 0)
		{
			SellItem(MerchantSlot);
		}
	}
}

// Implement the SellItem function
void AMerchantCounter::SellItem(FInventorySlot& ItemSlot)
{
	if (ItemSlot.ItemDefinition && ItemSlot.Quantity > 0)
	{
		// For debugging purposes, log the item being sold
		UE_LOG(LogTemp, Log, TEXT("Selling item: %s, Quantity: %d"), *ItemSlot.ItemDefinition->GetName(), ItemSlot.Quantity);

		// Implement selling logic here
		// For example, you could add currency to the player's inventory and remove the item from the merchant's inventory

		// Clear the item slot after selling
		ItemSlot.ItemDefinition = nullptr;

		UE_LOG(LogTemp, Log, TEXT("Sold item"));

		// For debugging purposes, show current inventory state
		for (const FInventorySlot& Slot : InventoryComponent->InventorySlots)
		{
			if (Slot.ItemDefinition)
			{
				UE_LOG(LogTemp, Log, TEXT("Inventory Slot: %s, Quantity: %d"), *Slot.ItemDefinition->GetName(), Slot.Quantity);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Inventory Slot is empty."));
			}
		}

	}
}

FText AMerchantCounter::GetInteractionPrompt_Implementation() const
{
	return FText::FromString("Use Merchant Counter");
}
