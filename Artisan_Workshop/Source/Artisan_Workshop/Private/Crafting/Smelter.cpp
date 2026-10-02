// Fill out your copyright notice in the Description page of Project Settings.


#include "Crafting/Smelter.h"
#include "Player/AWorkshopCharacter.h"

// Sets default values
ASmelter::ASmelter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the SmelterMesh component
	SmelterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SmelterMesh"));
	RootComponent = SmelterMesh;

	// Create the InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	// Create the CraftingComponent
	CraftingComponent = CreateDefaultSubobject<UCraftingComponent>(TEXT("CraftingComponent"));

}

// Called when the game starts or when spawned
void ASmelter::BeginPlay()
{
	Super::BeginPlay();
	
	if (CraftingComponent)
	{
		CraftingComponent->InventoryComponent = InventoryComponent;
	}
}

// Implement the Interact function from the IInteractable interface
void ASmelter::Interact(AActor* Interactor)
{
	// Add item from the player inventory to the smelter's inventory for testing
	AAWorkshopCharacter* Player = Cast<AAWorkshopCharacter>(Interactor);
	if (Player && Player->GetInventoryComponent()->InventorySlots.Num() > 0)
	{
		// Remove item from player inventory and add to smelter inventory
		// For demonstration, let's assume we are removing the first item in the player's inventory
		FInventorySlot& PlayerSlot = Player->GetInventoryComponent()->InventorySlots[0];
		if (PlayerSlot.ItemDefinition && PlayerSlot.Quantity > 0)
		{
			// Add the item to the smelter's inventory
			InventoryComponent->AddItem(PlayerSlot.ItemDefinition);
			// Remove the item from the player's inventory
			Player->GetInventoryComponent()->RemoveItem(PlayerSlot.ItemDefinition);
			UE_LOG(LogTemp, Log, TEXT("Moved item from player to smelter."));
		}
	}

	if (CraftingComponent && CraftingComponent->ActiveRecipe)
	{
		if (CraftingComponent->CanCraft())
		{
			CraftingComponent->ProcessRecipe();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot craft the recipe: %s"), *CraftingComponent->ActiveRecipe->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No active recipe set in the CraftingComponent."));
	}
}

// Set the interaction prompt text for the smelter
FText ASmelter::GetInteractionPrompt_Implementation() const
{
	return FText::FromString(TEXT("Use Smelter"));
}
