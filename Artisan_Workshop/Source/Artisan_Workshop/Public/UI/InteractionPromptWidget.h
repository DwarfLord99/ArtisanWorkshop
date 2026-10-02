// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/BaseWidget.h"
#include "InteractionPromptWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARTISAN_WORKSHOP_API UInteractionPromptWidget : public UBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> InteractionPromptText;
	
public:
	void SetInteractionPrompt(const FText& PromptText);
};
