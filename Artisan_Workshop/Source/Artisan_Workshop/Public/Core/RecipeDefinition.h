// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDefinition.h"
#include "RecipeDefinition.generated.h"

/**
 * 
 */
UCLASS()
class ARTISAN_WORKSHOP_API URecipeDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	// Recipe Name
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	FText RecipeName;

	// Recipe Description
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	FText RecipeDescription;

	// Recipe Ingredients
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	TArray<TObjectPtr<UItemDefinition>> RecipeIngredients;

	// Recipe Result
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	TObjectPtr<UItemDefinition> RecipeResult;
};
