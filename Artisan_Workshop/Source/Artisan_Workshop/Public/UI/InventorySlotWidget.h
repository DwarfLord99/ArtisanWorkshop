// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Core/ItemDefinition.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTISAN_WORKSHOP_API UInventorySlotWidget : public UBaseWidget
{
	GENERATED_BODY()
	
protected:
	// Widget references for displaying item icon and quantity
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ItemIconImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantityText;

	int32 SlotIndex = INDEX_NONE;

	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void SetItemData(UItemDefinition* ItemDefinition, int32 Quantity);
	void ClearSlot();
	void SetSlotIndex(int32 NewIndex) { SlotIndex = NewIndex; }
};
