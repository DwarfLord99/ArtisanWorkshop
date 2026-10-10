// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/InventoryComponent.h"
#include "Crafting/CraftingComponent.h"
#include "UI/SmelterWidget.h"
#include "Smelter.generated.h"

UCLASS()
class ARTISAN_WORKSHOP_API ASmelter : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASmelter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smelter")
	TObjectPtr<UStaticMeshComponent> SmelterMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smelter")
	TObjectPtr<UInventoryComponent> InputInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smelter")
	TObjectPtr<UInventoryComponent> OutputInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smelter")
	TObjectPtr<UCraftingComponent> CraftingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Smelter")
	TObjectPtr<USmelterWidget> SmelterWidget;

public:	

	void Interact(AActor* Interactor) override;

	FText GetInteractionPrompt_Implementation() const override;

	UCraftingComponent* GetCraftingComponent() const { return CraftingComponent; }
};
