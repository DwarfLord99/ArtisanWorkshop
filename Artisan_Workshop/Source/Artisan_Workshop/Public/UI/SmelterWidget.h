// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "SmelterWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSmelterItemDoubleClicked, UInventoryComponent*, InventorySource, int32, SlotIndex);

class UCraftingComponent;
class UInventoryWidget;
class UInventorySlotWidget;
class UInventoryComponent;

/**
 * 
 */
UCLASS()
class ARTISAN_WORKSHOP_API USmelterWidget : public UBaseWidget
{
	GENERATED_BODY()
	
private:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UWrapBox* SmelterPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventoryWidget> PlayerInventoryPanel;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventorySlotWidget> SmelterInputSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInventorySlotWidget> SmelterOutputSlot;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UButton> CloseButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> SmeltProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SmelterTitle;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentRecipe;

	UPROPERTY()
	TObjectPtr<UCraftingComponent> CraftingComponent;

public:
	void SetInventorySource(UInventoryComponent* PlayerInventorySource);
	void SetCraftingComponent(UCraftingComponent* CraftingComponent);
	void ResetSmelterDisplay();
	void UpdateSmeltProgress(float Progress);
	void SetSmelterTitle(const FText& NewTitle);
	void SetCurrentRecipe(const FText& RecipeText);

	UFUNCTION()
	void CloseSmelterWidget();

	UFUNCTION()
	void HandleSmelterItemDoubleClicked(UInventoryComponent* SourceInventory, int32 SlotIndex);

	UFUNCTION()
	void HandleSmelterOutputSlotDoubleClicked();
};
