// Fill out your copyright notice in the Description page of Project Settings.


#include "Crafting/CraftingComponent.h"

// Sets default values for this component's properties
UCraftingComponent::UCraftingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UCraftingComponent::CanCraft() const
{
	if (!ActiveRecipe || !InputInventory)
	{
		return false;
	}

	// Check if the input inventory has enough items for the recipe
	for (UItemDefinition* RequiredIngredient : ActiveRecipe->RecipeIngredients)
	{
		bool bFoundIngredient = false;

		for (const FInventorySlot& Slot : InputInventory->InventorySlots)
		{
			if (Slot.ItemDefinition == RequiredIngredient)
			{
				bFoundIngredient = true;
				break;
			}
		}

		if (!bFoundIngredient)
		{
			return false;
		}
	}

	return true;
}

bool UCraftingComponent::ProcessRecipe()
{
	if (bIsProcessing)
	{
		return false; // Already processing a recipe
	}

	if (!CanCraft())
	{
		return false;
	}

	bIsProcessing = true;

	CurrentProgress = 0.0f;

	return true;
}

void UCraftingComponent::CompleteRecipe()
{
	if (!CanCraft())
	{
		return;
	}

	// Remove the required ingredients from the input inventory
	for (UItemDefinition* RequiredIngredient : ActiveRecipe->RecipeIngredients)
	{
		FInventorySlot TempSlot;

		TempSlot.ItemDefinition = RequiredIngredient;

		InputInventory->RemoveItemFrom(TempSlot, 1);

		FInventorySlot OutputSlot;

		OutputSlot.ItemDefinition = ActiveRecipe->RecipeResult;
		OutputInventory->AddItemTo(OutputSlot, ActiveRecipe->RecipeResultQuantity);

		bIsProcessing = false;
		CurrentProgress = 0.0f;
	}
}
