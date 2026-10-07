// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StorageWidget.h"
#include "UI/InventoryWidget.h"
#include "Components/Button.h"

void UStorageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddDynamic(this, &UStorageWidget::CloseStorageWidget);
	}
}

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

void UStorageWidget::CloseStorageWidget()
{
	RemoveFromParent();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
}