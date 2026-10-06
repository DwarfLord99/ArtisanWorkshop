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
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Populating Inventory Grid."));
		}

		UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, InventorySlotWidgetClass);
		if (NewSlot)
		{
			InventoryGrid->AddChildToWrapBox(NewSlot);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Added Inventory Slot %d to Grid."), Index));
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
