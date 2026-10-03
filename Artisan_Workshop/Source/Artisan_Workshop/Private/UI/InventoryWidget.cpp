// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "Components/WrapBox.h"

void UInventoryWidget::PopulateInventoryGrid()
{
	if (!InventoryGrid || !InventorySlotWidgetClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InventoryGrid or InventorySlotWidgetClass is not valid."));
		return;
	}

	// Clear existing children in the grid
	InventoryGrid->ClearChildren();

	// Populate the grid with inventory slots
	const int32 NumberofSlots = 20;

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
		}
	}
}
