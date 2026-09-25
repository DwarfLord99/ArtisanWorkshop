// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// Print out the current inventory for debugging
	UE_LOG(LogTemp, Log, TEXT("Current Inventory:"));
	for (const FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.ItemDefinition)
		{
			UE_LOG(LogTemp, Log, TEXT(" - %s: %d"), *Slot.ItemDefinition->GetName(), Slot.Quantity);
		}
	}
}

void UInventoryComponent::AddItem(UItemDefinition* ItemDefinition)
{
	if (!ItemDefinition) return;

	// Check if the item already exists in the inventory
	for (FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.ItemDefinition == ItemDefinition)
		{
			// If it exists, increase the quantity
			Slot.Quantity++;
			return;
		}
	}

	// If it doesn't exist, add a new slot
	FInventorySlot NewSlot;
	NewSlot.ItemDefinition = ItemDefinition;
	NewSlot.Quantity = 1;
	InventorySlots.Add(NewSlot);

	// Print out the current inventory for debugging
	UE_LOG(LogTemp, Log, TEXT("Current Inventory:"));
	for (const FInventorySlot& Slot : InventorySlots)
	{
		UE_LOG(LogTemp, Log, TEXT(" - %s: %d"), *Slot.ItemDefinition->GetName(), Slot.Quantity);
	}
}

void UInventoryComponent::RemoveItem(UItemDefinition* ItemDefinition)
{
	if (!ItemDefinition) return;

	for (int32 i = 0; i < InventorySlots.Num(); ++i)
	{
		if (InventorySlots[i].ItemDefinition == ItemDefinition)
		{
			// Decrease the quantity
			InventorySlots[i].Quantity--;
			// If quantity reaches zero, remove the slot
			if (InventorySlots[i].Quantity <= 0)
			{
				InventorySlots.RemoveAt(i);
			}
			return;
		}
	}
}

void UInventoryComponent::HasItem(UItemDefinition* ItemDefinition, int32 Quantity, bool& bHasItem) const
{
	bHasItem = false;
	if (!ItemDefinition) return;
	for (const FInventorySlot& Slot : InventorySlots)
	{
		if (Slot.ItemDefinition == ItemDefinition && Slot.Quantity >= Quantity)
		{
			bHasItem = true;
			return;
		}
	}
}
