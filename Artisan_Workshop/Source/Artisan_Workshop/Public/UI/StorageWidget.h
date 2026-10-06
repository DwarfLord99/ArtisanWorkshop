// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "Inventory/InventoryComponent.h"
#include "UI/InventorySlotWidget.h"
#include "StorageWidget.generated.h"

class UInventoryWidget;
class UInventoryComponent;

/**
 * 
 */
UCLASS()
class ARTISAN_WORKSHOP_API UStorageWidget : public UBaseWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryWidget> StorageInventoryPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryWidget> PlayerInventoryPanel;

public:
	void SetInventorySources(UInventoryComponent* PlayerInventorySource, UInventoryComponent* StorageInventorySource);
};
