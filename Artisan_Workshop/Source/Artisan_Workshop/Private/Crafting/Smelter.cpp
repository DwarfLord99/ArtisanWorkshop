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
	// Open the storage UI for the player interacting with the crate
	if (AAWorkshopCharacter* WorkshopCharacter = Cast<AAWorkshopCharacter>(Interactor))
	{
		if (SmelterWidget)
		{
			SmelterWidget->AddToViewport();
			SmelterWidget->SetInventorySource(WorkshopCharacter->GetInventoryComponent());

			APlayerController* PlayerController = Cast<APlayerController>(WorkshopCharacter->GetController());
			if (PlayerController)
			{
				PlayerController->bShowMouseCursor = true;
				FInputModeUIOnly InputMode;
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				PlayerController->SetInputMode(InputMode);
			}
		}
	}
}

// Set the interaction prompt text for the smelter
FText ASmelter::GetInteractionPrompt_Implementation() const
{
	return FText::FromString(TEXT("Use Smelter"));
}
