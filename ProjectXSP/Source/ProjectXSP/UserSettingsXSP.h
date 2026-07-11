// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "UserSettingsXSP.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXSP_API UUserSettingsXSP : public UGameUserSettings
{
	// no idea why but GENERATED_BODY does not work
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentCulture(FString newCulture);

	UFUNCTION(BlueprintCallable)
	void SetDefaultStylingEnabled(bool newDefaultStylingEnabled, AProjectXSPGameMode* gameMode);

	UFUNCTION(BlueprintCallable)
	void SetRayTracedLightingEnabled(bool newRayTracedLightingEnabled, AProjectXSPGameMode* gameMode);

	UFUNCTION(BlueprintCallable)
	void SetRayTracedReflectionsEnabled(bool newRayTracedReflectionsEnabled, AProjectXSPGameMode* gameMode);

	UFUNCTION(BlueprintCallable)
	void SetRenderScale(float newRenderScale);

	UFUNCTION(BlueprintCallable)
	void SetAntiAliasMethod(int AntiAliasMethod);

	// Getters

	UFUNCTION(BlueprintPure)
	FString GetCurrentCulture() const;

	UFUNCTION(BlueprintPure)
	bool GetDefaultStylingEnabled() const;

	UFUNCTION(BlueprintPure)
	bool GetRayTracedLightingEnabled() const;

	UFUNCTION(BlueprintPure)
	bool GetRayTracedReflectionsEnabled() const;

	UFUNCTION(BlueprintPure)
	float GetRenderScale() const;
	
	UFUNCTION(BlueprintPure)
	float GetAppliedRenderScale() const;
	
	UFUNCTION(BlueprintPure)
	int GetAntiAliasMethod() const;
	
	UFUNCTION(BlueprintPure)
	float GetStylizedScreenPercentage() const;

	UFUNCTION(BlueprintCallable)
	static UUserSettingsXSP* GetUserSettingsXSP();
	
	UFUNCTION(BlueprintCallable)
	void RefreshRenderScale();
	
	UFUNCTION(BlueprintCallable)
	void RefreshAfterUpdatingRT();
	
	UFUNCTION(BlueprintCallable)
	void RefreshAntiAliasMethod();

	
protected:
	UPROPERTY(Config)
	FString CurrentCulture;
	
	UPROPERTY(Config)
	bool bDefaultStylingEnabled;
	UPROPERTY(Config)
	bool bRayTracedLightingEnabled;
	UPROPERTY(Config)
	bool bRayTracedReflectionsEnabled;
	UPROPERTY(Config)
	int AntiAliasMethod;
	UPROPERTY(Config)
	float RenderScale;
};
