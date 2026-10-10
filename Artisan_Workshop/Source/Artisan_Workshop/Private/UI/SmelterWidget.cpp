// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SmelterWidget.h"
#include "UI/InventoryWidget.h"
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
	}
}

void USmelterWidget::SetSmelterInputSlot(UItemDefinition* ItemDefinition, int32 Quantity)
{
	// STUB for setting the smelter input slot
}

void USmelterWidget::SetSmelterOutputSlot(UItemDefinition* ItemDefinition, int32 Quantity)
{
	// STUB for setting the smelter output slot
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
