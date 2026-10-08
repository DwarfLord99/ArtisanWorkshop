// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "Components/WrapBox.h"
#include "Inventory/InventoryComponent.h"
#include "Player/AWorkshopCharacter.h"

void UInventoryWidget::PopulateInventoryGrid()
{
	if (!InventoryGrid || !InventorySlotWidgetClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InventoryGrid or InventorySlotWidgetClass is not valid."));
		return;
	}

	// Clear existing children in the grid
	InventoryGrid->ClearChildren();
	InventorySlots.Empty();

	// Populate the grid with inventory slots
	const int32 NumberofSlots = 28;

	for (int32 Index = 0; Index < NumberofSlots; ++Index)
	{
		UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, InventorySlotWidgetClass);
		if (NewSlot)
		{
			NewSlot->SetSlotIndex(Index);
			InventoryGrid->AddChildToWrapBox(NewSlot);
			NewSlot->OnInventorySlotDoubleClicked.AddUniqueDynamic(this, &UInventoryWidget::OnInventorySlotDoubleClicked);
			InventorySlots.Add(NewSlot);
		}
	}
}

void UInventoryWidget::RefreshInventoryGrid()
{
	if (!InventorySource)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventorySource is not valid."));
		return;
	}

	if (InventorySource)
	{
		for (int32 Index = 0; Index < InventorySlots.Num(); ++Index)
		{
			if (!InventorySlots[Index])
			{
				continue;
			}

			if (InventorySource->InventorySlots.IsValidIndex(Index))
			{
				const FInventorySlot& SlotData = InventorySource->InventorySlots[Index];
				InventorySlots[Index]->SetItemData(SlotData.ItemDefinition, SlotData.Quantity);
			}
			else
			{
				InventorySlots[Index]->ClearSlot();
			}
		}
	}
}

void UInventoryWidget::SetInventorySource(UInventoryComponent* NewInventorySource)
{
	if (NewInventorySource)
	{
		InventorySource = NewInventorySource;
		RefreshInventoryGrid();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NewInventorySource is not valid."));
	}
}

void UInventoryWidget::SetInventoryTitle(const FText& NewTitle)
{
	if (InventoryTitle)
	{
		InventoryTitle->SetText(NewTitle);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryTitle is not valid."));
	}
}

void UInventoryWidget::OnInventorySlotDoubleClicked(int32 SlotIndex)
{
	if (!InventorySource)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventorySource is not valid."));
		return;
	}
	if (InventorySource->InventorySlots.IsValidIndex(SlotIndex))
	{
		const FInventorySlot& SlotData = InventorySource->InventorySlots[SlotIndex];
		if (SlotData.ItemDefinition)
		{
			// Handle the double-clicked item here
			OnInventoryItemDoubleClicked.Broadcast(InventorySource, SlotIndex);
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Double-clicked on an empty slot."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid slot index: %d"), SlotIndex);
	}
}
