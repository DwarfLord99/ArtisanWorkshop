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
	// Get the InventoryComponent from the owning actor
	AAWorkshopCharacter* PlayerCharacter = Cast<AAWorkshopCharacter>(GetOwningPlayerPawn());
	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is not valid."));
		return;
	}

	if (PlayerCharacter->GetInventoryComponent())
	{
		for (int32 Index = 0; Index < InventorySlots.Num(); ++Index)
		{
			if (InventorySlots[Index])
			{
				if (PlayerCharacter->GetInventoryComponent()->InventorySlots.IsValidIndex(Index))
				{
					const FInventorySlot& SlotData = PlayerCharacter->GetInventoryComponent()->InventorySlots[Index];
					InventorySlots[Index]->SetItemData(SlotData.ItemDefinition, SlotData.Quantity);
				}
				else
				{
					// If the inventory slot is not valid, set it to empty
					InventorySlots[Index]->ClearSlot();
				}
			}
		}
	}
}
