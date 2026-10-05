// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "Components/TextBlock.h"
#include "InventorySlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTISAN_WORKSHOP_API UInventorySlotWidget : public UBaseWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;

	// Widget references for displaying item name and quantity
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ItemQuantityText;

public:
	void SetItemData(const FText& Name, int32 Quantity);
};
