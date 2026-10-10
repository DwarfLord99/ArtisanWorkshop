// Fill out your copyright notice in the Description page of Project Settings.


#include "Crafting/Workbench.h"
#include "Player/AWorkshopCharacter.h"

// Sets default values
AWorkbench::AWorkbench()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create the WorkbenchMesh component
	WorkbenchMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorkbenchMesh"));
	RootComponent = WorkbenchMesh;

	// Create the InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	// Create the CraftingComponent
	CraftingComponent = CreateDefaultSubobject<UCraftingComponent>(TEXT("CraftingComponent"));
}

// Called when the game starts or when spawned
void AWorkbench::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Implement the Interact function from the IInteractable interface
void AWorkbench::Interact(AActor* Interactor)
{
	// Add item from the player inventory to the workbench's inventory for testing
	AAWorkshopCharacter* Player = Cast<AAWorkshopCharacter>(Interactor);
	if (Player && Player->GetInventoryComponent()->InventorySlots.Num() > 0)
	{
		// Remove item from player inventory and add to workbench inventory
		// For demonstration, let's assume we are removing the first item in the player's inventory
		FInventorySlot& PlayerSlot = Player->GetInventoryComponent()->InventorySlots[0];
		if (PlayerSlot.ItemDefinition && PlayerSlot.Quantity > 0)
		{
			// Add the item to the workbench's inventory
			InventoryComponent->AddItem(PlayerSlot.ItemDefinition);
			// Remove the item from the player's inventory
			Player->GetInventoryComponent()->RemoveItem(PlayerSlot.ItemDefinition);
			UE_LOG(LogTemp, Log, TEXT("Moved item from player to workbench."));
		}
	}
	if (CraftingComponent && CraftingComponent->ActiveRecipe)
	{
		if (CraftingComponent->CanCraft())
		{
			CraftingComponent->ProcessRecipe();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No active recipe set in the CraftingComponent."));
	}
}

FText AWorkbench::GetInteractionPrompt_Implementation() const
{
	return FText::FromString("Use Workbench");
}
