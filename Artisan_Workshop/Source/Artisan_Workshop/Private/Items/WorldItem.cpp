// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WorldItem.h"
#include "Player/AWorkshopCharacter.h"

// Sets default values
AWorldItem::AWorldItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMeshComponent;
}

// Called when the game starts or when spawned
void AWorldItem::BeginPlay()
{
	Super::BeginPlay();
	
	if (ItemDefinition)
	{
		ItemName = ItemDefinition->ItemName;
		ItemDescription = ItemDefinition->ItemDescription;
		ItemValue = ItemDefinition->ItemValue;
		if (ItemDefinition->ItemMesh)
		{
			ItemMeshComponent->SetStaticMesh(ItemDefinition->ItemMesh);
		}
	}
}

void AWorldItem::Interact(AActor* Interactor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Interacted with: ") + ItemName.ToString());
	}

	AAWorkshopCharacter* Player = Cast<AAWorkshopCharacter>(Interactor);
	if (Player && Player->GetInventoryComponent())
	{
		Player->GetInventoryComponent()->AddItem(ItemDefinition);

		UE_LOG(LogTemp, Log, TEXT("Added %s to inventory."), *ItemName.ToString());

		// Destroy the item in the world after adding it to the inventory
		Destroy();
	}

}

FText AWorldItem::GetInteractionPrompt_Implementation() const
{
	return FText::FromString("Pick up " + ItemName.ToString());
}
