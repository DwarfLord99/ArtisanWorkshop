// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/StorageWidget.h"
#include "UI/InventoryWidget.h"
#include "Components/Button.h"

void UStorageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CloseButton)
	{
		CloseButton->OnClicked.AddUniqueDynamic(this, &UStorageWidget::CloseStorageWidget);
	}
}

void UStorageWidget::SetInventorySources(UInventoryComponent* PlayerInventorySource, UInventoryComponent* StorageInventorySource)
{
	if (StorageInventoryPanel)
	{
		StorageInventoryPanel->PopulateInventoryGrid();
		StorageInventoryPanel->SetInventoryTitle(FText::FromString("Storage")); // Set the storage inventory title
		StorageInventoryPanel->SetInventorySource(StorageInventorySource);
		StorageInventoryPanel->OnInventoryItemDoubleClicked.AddUniqueDynamic(this, &UStorageWidget::HandleInventoryItemDoubleClicked);
	}

	if (PlayerInventoryPanel)
	{
		PlayerInventoryPanel->PopulateInventoryGrid();
		PlayerInventoryPanel->SetInventoryTitle(FText::FromString("Inventory")); // Set the player inventory title
		PlayerInventoryPanel->SetInventorySource(PlayerInventorySource);
		PlayerInventoryPanel->OnInventoryItemDoubleClicked.AddUniqueDynamic(this, &UStorageWidget::HandleInventoryItemDoubleClicked);
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

void UStorageWidget::HandleInventoryItemDoubleClicked(UInventoryComponent* SourceInventory, int32 SlotIndex)
{
	if (!SourceInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("SourceInventory is not valid."));
		return;
	}

	if (!SourceInventory->InventorySlots.IsValidIndex(SlotIndex))
	{
		return;
	}

	const FInventorySlot& SlotData = SourceInventory->InventorySlots[SlotIndex];

	if (!SlotData.ItemDefinition)
	{
		return;
	}

	UInventoryComponent* DestinationInventory = nullptr;

	if (SourceInventory == PlayerInventoryPanel->GetInventorySource())
	{
		DestinationInventory = StorageInventoryPanel->GetInventorySource();
	}
	else
	{
		DestinationInventory = PlayerInventoryPanel->GetInventorySource();
	}

	if (!DestinationInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("DestinationInventory is not valid."));
		return;
	}

	if (DestinationInventory->AddItemTo(SlotData, 1))
	{
		SourceInventory->RemoveItemFrom(SlotData, 1);
	}

	PlayerInventoryPanel->RefreshInventoryGrid();
	StorageInventoryPanel->RefreshInventoryGrid();
}