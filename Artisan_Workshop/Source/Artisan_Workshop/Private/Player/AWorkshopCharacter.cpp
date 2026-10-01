// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AWorkshopCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/Interactable.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AAWorkshopCharacter::AAWorkshopCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a CameraComponent
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FirstPersonCameraOffset); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create an InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

// Called when the game starts or when spawned
void AAWorkshopCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Add the mapping context
			Subsystem->AddMappingContext(FirstPersonContext, 0);
		}
	}
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("We are using Workshop Character."));
}

// Called to bind functionality to input
void AAWorkshopCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Setup action bindings
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAWorkshopCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAWorkshopCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AAWorkshopCharacter::Interact);
		EnhancedInputComponent->BindAction(TestUIAction, ETriggerEvent::Started, this, &AAWorkshopCharacter::ToggleUI);
	}

}

void AAWorkshopCharacter::Move(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// add movement 
		const FVector Right = GetActorRightVector();
		AddMovementInput(Right, MovementVector.X);

		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementVector.Y);
	}
}

void AAWorkshopCharacter::Look(const FInputActionValue& Value)
{
	// Input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAWorkshopCharacter::Interact(const FInputActionValue& Value)
{
	// Handle interaction input here
	// For example, you can call a function to interact with objects in the game world
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Interact action triggered."));
	}

	FHitResult HitResult;
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	FVector End = Start + (FirstPersonCameraComponent->GetForwardVector() * InteractionDistance);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		if (AActor* HitActor = HitResult.GetActor())
		{
			IInteractable* Interactactable = Cast<IInteractable>(HitActor);
			if (Interactactable)
			{
				Interactactable->Interact(this);
			}
		}
	}
}

void AAWorkshopCharacter::ToggleUI(const FInputActionValue& Value)
{
	// Create and add the widget to the viewport if it doesn't exist
	if (ActiveWidget == nullptr && BaseWidgetClass != nullptr)
	{
		ActiveWidget = CreateWidget<UUserWidget>(GetWorld(), BaseWidgetClass);
		if (ActiveWidget)
		{
			ActiveWidget->AddToViewport();
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UI Widget Created and Added to Viewport."));
		}
	}
	else if (ActiveWidget != nullptr)
	{
		// Remove the widget from the viewport if it exists
		ActiveWidget->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("UI Widget Removed from Viewport."));
		ActiveWidget = nullptr;
	}
}

