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
	if (!ActiveRecipe || !InventoryComponent)
	{
		return false;
	}

	for (const TObjectPtr<UItemDefinition>& Ingredient : ActiveRecipe->RecipeIngredients)
	{
		bool bHasItem = false;

		InventoryComponent->HasItem(Ingredient, 1, bHasItem);

		if (!bHasItem)
		{
			return false;
		}
	}

	return true;
}

bool UCraftingComponent::ProcessRecipe()
{
	if (!CanCraft())
	{
		return false;
	}

	UE_LOG(LogTemp, Log, TEXT("Crafting recipe: %s"), *ActiveRecipe->GetName());

	// Remove ingredients from inventory
	for (const TObjectPtr<UItemDefinition>& Ingredient : ActiveRecipe->RecipeIngredients)
	{
		UE_LOG(LogTemp, Log, TEXT("Removing ingredient: %s"), *Ingredient->GetName());
		InventoryComponent->RemoveItem(Ingredient);
	}

	// Add the result item to inventory
	if (ActiveRecipe->RecipeResult)
	{
		UE_LOG(LogTemp, Log, TEXT("Adding result item: %s"), *ActiveRecipe->RecipeResult->GetName());
		InventoryComponent->AddItem(ActiveRecipe->RecipeResult);

		// Print out the current inventory for debugging
		UE_LOG(LogTemp, Log, TEXT("Current Inventory:"));
		for (const FInventorySlot& Slot : InventoryComponent->InventorySlots)
		{
			if (Slot.ItemDefinition)
			{
				UE_LOG(LogTemp, Log, TEXT(" - %s: %d"), *Slot.ItemDefinition->GetName(), Slot.Quantity);
			}
		}
	}

	return true;
}
