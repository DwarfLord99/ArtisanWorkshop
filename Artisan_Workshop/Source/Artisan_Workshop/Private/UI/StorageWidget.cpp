// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StorageWidget.h"
#include "UI/InventoryWidget.h"

void UStorageWidget::SetInventorySources(UInventoryComponent* PlayerInventorySource, UInventoryComponent* StorageInventorySource)
{
	if (StorageInventoryPanel)
	{
		StorageInventoryPanel->PopulateInventoryGrid();
		StorageInventoryPanel->SetInventorySource(StorageInventorySource);
	}

	if (PlayerInventoryPanel)
	{
		PlayerInventoryPanel->PopulateInventoryGrid();
		PlayerInventoryPanel->SetInventorySource(PlayerInventorySource);
	}
}