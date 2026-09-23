// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interaction/Interactable.h"
#include "ItemDefinition.generated.h"

/**
 * 
 */
UCLASS()
class ARTISAN_WORKSHOP_API UItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
	// Unique identifier for the item
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Item", GetFName());
	}

	// Item Name
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	// Item Description
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemDescription;

	// Item Value
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 ItemValue;

	// Item Mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UStaticMesh> ItemMesh;
};
