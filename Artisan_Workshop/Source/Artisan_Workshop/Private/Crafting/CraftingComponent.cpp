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
	// STUB for checking if the crafting component can craft the active recipe
	return false;
}

bool UCraftingComponent::ProcessRecipe()
{
	// STUB for processing the active recipe
	return false;
}
