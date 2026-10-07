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
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryWidget> StorageInventoryPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryWidget> PlayerInventoryPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CloseButton;

public:
	void SetInventorySources(UInventoryComponent* PlayerInventorySource, UInventoryComponent* StorageInventorySource);

	UFUNCTION()
	void CloseStorageWidget();
};
