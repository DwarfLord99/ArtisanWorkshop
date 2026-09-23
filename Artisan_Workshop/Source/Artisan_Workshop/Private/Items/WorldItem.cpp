// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WorldItem.h"

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

// Called every frame
void AWorldItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldItem::Interact()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Interacted with: ") + ItemName.ToString());
	}
}
