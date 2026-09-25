// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Core/RecipeDefinition.h"
#include "CraftingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARTISAN_WORKSHOP_API UCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCraftingComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TObjectPtr<UInventoryComponent> InventoryComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TObjectPtr<URecipeDefinition> ActiveRecipe;

	bool CanCraft() const;

	bool ProcessRecipe();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

		
};
