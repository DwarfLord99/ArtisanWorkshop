// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/InventoryComponent.h"
#include "Crafting/CraftingComponent.h"
#include "Workbench.generated.h"

UCLASS()
class ARTISAN_WORKSHOP_API AWorkbench : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorkbench();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Workbench")
	TObjectPtr<UStaticMeshComponent> WorkbenchMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Workbench")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Workbench")
	TObjectPtr<UCraftingComponent> CraftingComponent;

public:

	void Interact(AActor* Interactor) override;
};
