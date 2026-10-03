// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "UI/InventorySlotWidget.h"
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
	class UUniformGridPanel* InventoryGrid;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UInventorySlotWidget> InventorySlotWidgetClass;

public:
	void PopulateInventoryGrid();
};
