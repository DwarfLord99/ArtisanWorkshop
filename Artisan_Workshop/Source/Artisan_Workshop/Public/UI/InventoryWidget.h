// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "UI/InventorySlotWidget.h"
#include "Inventory/InventoryComponent.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTISAN_WORKSHOP_API UInventoryWidget : public UBaseWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* InventoryGrid;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* InventoryTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventorySlotWidget> InventorySlotWidgetClass;

	// Inventory Slot Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UInventorySlotWidget>> InventorySlots;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventorySource;

public:
	void SetInventorySource(UInventoryComponent* NewInventorySource);
	void SetInventoryTitle(const FText& NewTitle);
	void PopulateInventoryGrid();
	void RefreshInventoryGrid();
};
