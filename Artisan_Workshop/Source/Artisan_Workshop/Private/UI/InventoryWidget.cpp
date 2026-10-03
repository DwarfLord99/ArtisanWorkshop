// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventoryWidget.h"

#include "Components/UniformGridPanel.h"

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
	const int32 Columns = 5; // Number of columns in the grid

	for (int32 Index = 0; Index < NumberofSlots; ++Index)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Populating Inventory Grid."));
		}

		UInventorySlotWidget* NewSlot = CreateWidget<UInventorySlotWidget>(this, InventorySlotWidgetClass);
		if (NewSlot)
		{
			int32 Row = Index / Columns;
			int32 Column = Index % Columns;
			InventoryGrid->AddChildToUniformGrid(NewSlot, Row, Column);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Added slot %d at Row: %d, Column: %d"), Index, Row, Column));
		}
	}
}
