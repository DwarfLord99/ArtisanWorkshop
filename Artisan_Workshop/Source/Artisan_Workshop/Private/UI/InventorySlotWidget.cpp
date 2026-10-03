// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InventorySlotWidget.h"

#include "Components/TextBlock.h"

void UInventorySlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Additional initialization if needed

	// Debugging: Log the widget construction
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("InventorySlotWidget constructed."));
	}

	UE_LOG(LogTemp, Warning,
		TEXT("Constructed Slot: %p"), this);

	// Ensure that the widget references are valid
	if (!ItemNameText)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemNameText is not valid."));
	}
	else
	{
		// Debugging: Log the initial text of the ItemNameText
		FString InitialText = ItemNameText->GetText().ToString();
		UE_LOG(LogTemp, Log, TEXT("Initial ItemNameText: %s"), *InitialText);
	}

	if (!ItemQuantityText)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemQuantityText is not valid."));
	}
	else
	{
		// Debugging: Log the initial text of the ItemQuantityText
		FString InitialText = ItemQuantityText->GetText().ToString();
		UE_LOG(LogTemp, Log, TEXT("Initial ItemQuantityText: %s"), *InitialText);
	}
}

void UInventorySlotWidget::SetItemData(const FString& Name, int32 Quantity)
{
	UE_LOG(LogTemp, Warning,
		TEXT("Slot Widget: %p"), this);

	if (ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(Name));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemNameText is not valid."));
	}

	if (ItemQuantityText)
	{
		ItemQuantityText->SetText(FText::FromString(FString::FromInt(Quantity)));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemQuantityText is not valid."));
	}
}
