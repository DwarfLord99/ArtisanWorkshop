// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Inventory/InventoryComponent.h"
#include "AWorkshopCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class ARTISAN_WORKSHOP_API AAWorkshopCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAWorkshopCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> FirstPersonContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> TestUIAction;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UInventoryComponent> InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> BaseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UUserWidget> ActiveWidget;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handle 2D Movement Input
	void Move(const FInputActionValue& Value);

	// Handle Look Input
	void Look(const FInputActionValue& Value);

	// Offset for the camera position
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector FirstPersonCameraOffset = FVector(2.8f, 5.9f, 0.0f);

	// Interaction distance for the interact action
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float InteractionDistance = 200.0f;

	// Handle interaction input
	void Interact(const FInputActionValue& Value);

	// Get the InventoryComponent
	UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	// Handle Test UI input
	void ToggleUI(const FInputActionValue& Value);
};
