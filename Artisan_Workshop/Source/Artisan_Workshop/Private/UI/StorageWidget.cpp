// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StorageWidget.h"
#include "UI/InventoryWidget.h"

void UStorageWidget::SetInventorySources(UInventoryComponent* PlayerInventorySource, UInventoryComponent* StorageInventorySource)
{
	if (StorageInventoryPanel)
	{
		StorageInventoryPanel->PopulateInventoryGrid();
		StorageInventoryPanel->SetInventoryTitle(FText::FromString("Storage")); // Set the storage inventory title
		StorageInventoryPanel->SetInventorySource(StorageInventorySource);
	}

	if (PlayerInventoryPanel)
	{
		PlayerInventoryPanel->PopulateInventoryGrid();
		PlayerInventoryPanel->SetInventoryTitle(FText::FromString("Inventory")); // Set the player inventory title
		PlayerInventoryPanel->SetInventorySource(PlayerInventorySource);
	}
}