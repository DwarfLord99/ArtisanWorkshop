// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SmelterWidget.h"
#include "UI/InventoryWidget.h"
#include "Crafting/CraftingComponent.h"
#include "Components/Button.h"

void USmelterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (CloseButton)
	{
		CloseButton->OnClicked.AddUniqueDynamic(this, &USmelterWidget::CloseSmelterWidget);
	}
}

void USmelterWidget::SetInventorySource(UInventoryComponent* PlayerInventorySource)
{
	if (PlayerInventoryPanel)
	{
		PlayerInventoryPanel->PopulateInventoryGrid();
		PlayerInventoryPanel->SetInventoryTitle(FText::FromString("Inventory")); // Set the player inventory title
		PlayerInventoryPanel->SetInventorySource(PlayerInventorySource);
		PlayerInventoryPanel->OnInventoryItemDoubleClicked.AddUniqueDynamic(this, &USmelterWidget::HandleSmelterItemDoubleClicked);
	}
}

void USmelterWidget::SetCraftingComponent(UCraftingComponent* InCraftingComponent)
{
	CraftingComponent = InCraftingComponent;
}

void USmelterWidget::UpdateSmeltProgress(float Progress)
{
	// STUB for updating the smelt progress bar
}

void USmelterWidget::SetSmelterTitle(const FText& NewTitle)
{
	// STUB for setting the smelter title
}

void USmelterWidget::SetCurrentRecipe(const FText& RecipeText)
{
	// STUB for setting the current recipe text
}

void USmelterWidget::ResetSmelterDisplay()
{
	if (!CraftingComponent) return;

	UInventoryComponent* InputInventory = CraftingComponent->GetInputInventory();
	UInventoryComponent* OutputInventory = CraftingComponent->GetOutputInventory();

	// Reset the input slot display
	if (InputInventory && InputInventory->InventorySlots.Num() > 0)
	{
		const FInventorySlot& InputSlot = InputInventory->InventorySlots[0];

		if (SmelterInputSlot)
		{
			SmelterInputSlot->SetItemData(InputSlot.ItemDefinition, InputSlot.Quantity);
		}
		else
		{
			SmelterInputSlot->ClearSlot();
		}
	}

	// Reset the output slot display
	if (OutputInventory && OutputInventory->InventorySlots.Num() > 0)
	{
		const FInventorySlot& OutputSlot = OutputInventory->InventorySlots[0];
		if (SmelterOutputSlot)
		{
			SmelterOutputSlot->SetItemData(OutputSlot.ItemDefinition, OutputSlot.Quantity);
		}
		else
		{
			SmelterOutputSlot->ClearSlot();
		}
	}
}

void USmelterWidget::CloseSmelterWidget()
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

void USmelterWidget::HandleSmelterItemDoubleClicked(UInventoryComponent* SourceInventory, int32 SlotIndex)
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
		UE_LOG(LogTemp, Warning,
			TEXT("CraftingComponent: %s"),
			*GetNameSafe(CraftingComponent));
		DestinationInventory = CraftingComponent ? CraftingComponent->GetInputInventory() : nullptr;
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
	ResetSmelterDisplay();
}

void USmelterWidget::HandleSmelterOutputSlotDoubleClicked()
{
	if (!CraftingComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("CraftingComponent is not valid."));
		return;
	}

	UInventoryComponent* OutputInventory = CraftingComponent->GetOutputInventory();

	if (!OutputInventory || OutputInventory->InventorySlots.Num() == 0)
	{
		return;
	}

	const FInventorySlot& OutputSlot = OutputInventory->InventorySlots[0];

	if (!OutputSlot.ItemDefinition || OutputSlot.Quantity <= 0)
	{
		return;
	}

	UInventoryComponent* PlayerInventory = PlayerInventoryPanel ? PlayerInventoryPanel->GetInventorySource() : nullptr;

	if (!PlayerInventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerInventory is not valid."));
		return;
	}

	if (PlayerInventory->AddItemTo(OutputSlot, 1))
	{
		OutputInventory->RemoveItemFrom(OutputSlot, 1);
	}

	PlayerInventoryPanel->RefreshInventoryGrid();
}
