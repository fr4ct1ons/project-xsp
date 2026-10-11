// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Combat/HeldInteractable.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "CommonDelegates.h"
#include "Combat/ModularHitscanWeapon.h"
#include "Core/Subsystems/PlayerHUDSubsystem.h"
#include "ProjectXSPCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AProjectXSPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

	/** Reload Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReloadAction;

	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;
	
	TObjectPtr<UPlayerHUDSubsystem> HUD;
	
public:
	AProjectXSPCharacter();

protected:
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:

	/////////////////////////////////////////////////////// Stamina
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxStamina = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CurrentStamina;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool StaminaRegenerating = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StaminaRegenRate = 3.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float StaminaRegenDelay = 2.0f;

	FTimerHandle StaminaRegenTimer;

	void OnStaminaRegenTimerEnd();

	///////////////////////////////////////////////////////
	
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void Fire(const FInputActionValue& Value);

	void Reload(const FInputActionValue& Value);

	void Pause(const FInputActionValue& Value);

	virtual void Jump() override;

	void ResetStaminaRegen();
	
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsTeleporting = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<AHeldInteractable>> DefaultInteractables = TArray<TSubclassOf<AHeldInteractable>>();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AHeldInteractable*> CurrentInteractables = TArray<AHeldInteractable*>();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USceneComponent> HandR;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<AHeldInteractable> CurrentInteractable;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIntDelegate OnUpdateCurrentMag;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FIntDelegate OnUpdateCarriedAmmo;

public:
	/** Returns FirstPersonCameraComponent subobject **/
	TObjectPtr<UCameraComponent> GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetAmmo(int32& OutCurrentMag, int32& OutCarriedAmmo);
};

