// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/ItemDefinition.h"
#include "Interaction/Interactable.h"
#include "WorldItem.generated.h"

UCLASS()
class ARTISAN_WORKSHOP_API AWorldItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UItemDefinition> ItemDefinition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* ItemMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	FText ItemDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	int32 ItemValue;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
};
