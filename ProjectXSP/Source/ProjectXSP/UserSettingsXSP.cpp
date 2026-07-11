// Fill out your copyright notice in the Description page of Project Settings.


#include "UserSettingsXSP.h"

#include "ProjectXSPGameMode.h"
#include "Kismet/KismetStringLibrary.h"

UUserSettingsXSP::UUserSettingsXSP(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	CurrentCulture = TEXT("en");
	bDefaultStylingEnabled = true;
	bRayTracedLightingEnabled = false;
	bRayTracedReflectionsEnabled = false;
	RenderScale = 75.0f;
	AntiAliasMethod = 0;
}

void UUserSettingsXSP::SetCurrentCulture(FString newCulture)
{
	CurrentCulture = newCulture;
}

void UUserSettingsXSP::SetDefaultStylingEnabled(bool newDefaultStylingEnabled, AProjectXSPGameMode* gameMode)
{
	bDefaultStylingEnabled = newDefaultStylingEnabled;
	
	gameMode->OnUpdateRTLighting(bRayTracedLightingEnabled);
	gameMode->OnUpdateRTReflections(bRayTracedReflectionsEnabled);
	
	RefreshAfterUpdatingRT();
	RefreshRenderScale();
	RefreshAntiAliasMethod();
}

void UUserSettingsXSP::SetRayTracedLightingEnabled(bool newRayTracedLightingEnabled, AProjectXSPGameMode* gameMode)
{
	bRayTracedLightingEnabled = newRayTracedLightingEnabled;

	gameMode->OnUpdateRTLighting(bRayTracedLightingEnabled);
	
	RefreshAfterUpdatingRT();
}

void UUserSettingsXSP::SetRayTracedReflectionsEnabled(bool newRayTracedReflectionsEnabled, AProjectXSPGameMode* gameMode)
{
	bRayTracedReflectionsEnabled = newRayTracedReflectionsEnabled;
	
	gameMode->OnUpdateRTReflections(bRayTracedReflectionsEnabled);
	
	RefreshAfterUpdatingRT();
}

void UUserSettingsXSP::SetRenderScale(float newRenderScale)
{
	RenderScale = newRenderScale;
	RefreshRenderScale();
}

void UUserSettingsXSP::SetAntiAliasMethod(int newAntiAliasMethod)
{
	if (newAntiAliasMethod == 3) // Method 3 means MSAA, which is not supported on the deferred renderer
	{
		newAntiAliasMethod = 4;
	}
	AntiAliasMethod = newAntiAliasMethod;
	RefreshAntiAliasMethod();
}

void UUserSettingsXSP::RefreshAntiAliasMethod()
{
	int aaMethod = AntiAliasMethod;

	if (bDefaultStylingEnabled)
	{
		aaMethod = 0;
	}
	
	GEngine->Exec(nullptr, *(FString("r.AntiAliasingMethod ") + FString::FromInt(aaMethod)));

	if (aaMethod == 0)
	{
		SetAntiAliasingQuality(0);
	}
	else
	{
		SetAntiAliasingQuality(3);
	}
}

FString UUserSettingsXSP::GetCurrentCulture() const
{
	return CurrentCulture;
}

bool UUserSettingsXSP::GetDefaultStylingEnabled() const
{
	return bDefaultStylingEnabled;
}

bool UUserSettingsXSP::GetRayTracedLightingEnabled() const
{
	return bRayTracedLightingEnabled;
}

bool UUserSettingsXSP::GetRayTracedReflectionsEnabled() const
{
	return bRayTracedReflectionsEnabled;
}

float UUserSettingsXSP::GetRenderScale() const
{
	return RenderScale;
}

float UUserSettingsXSP::GetAppliedRenderScale() const
{
	float scale = RenderScale;
	if (bDefaultStylingEnabled)
	{
		scale = static_cast<float>(GetStylizedScreenPercentage());
	}

	return scale;
}

int UUserSettingsXSP::GetAntiAliasMethod() const
{
	return AntiAliasMethod;
}

UUserSettingsXSP* UUserSettingsXSP::GetUserSettingsXSP()
{
	return Cast<UUserSettingsXSP>(UGameUserSettings::GetGameUserSettings());
}

void UUserSettingsXSP::RefreshAfterUpdatingRT()
{
	if (bDefaultStylingEnabled || !(bRayTracedLightingEnabled || bRayTracedReflectionsEnabled))
	{
		GEngine->AddOnScreenDebugMessage(-1, 9.2f, FColor::Red, TEXT("Disabled upscaling!"));
		GEngine->Exec(nullptr, TEXT("r.Upscale.Softness 0"));
		GEngine->Exec(nullptr, TEXT("r.Upscale.Quality 0"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 9.2f, FColor::Green, TEXT("Enabled upscaling!"));
		GEngine->Exec(nullptr, TEXT("r.Upscale.Softness 1"));
		GEngine->Exec(nullptr, TEXT("r.Upscale.Quality 3"));
	}
}

void UUserSettingsXSP::RefreshRenderScale()
{
	float scale = RenderScale;
	if (bDefaultStylingEnabled)
	{
		scale = GetStylizedScreenPercentage();
	}

	//GEngine->AddOnScreenDebugMessage(-1, 9.2f, FColor::Green, TEXT("New Render Scale::::: ") + FString::SanitizeFloat(scale));

	FString cmd = FString("r.ScreenPercentage ") + FString::SanitizeFloat(scale);
	bool worked = GEngine->Exec(nullptr, *cmd);
	//GEngine->AddOnScreenDebugMessage(-1, 9.2f, FColor::Green, TEXT("New Render Scale worked: ") + UKismetStringLibrary::Conv_BoolToString(worked));
}

float UUserSettingsXSP::GetStylizedScreenPercentage() const
{
	FVector2D Result = FVector2D( 1, 1 );
	float currentRes = GSystemResolution.ResY;
	float multiplier = 1.0f;
	
	multiplier = currentRes / (360.0f);

	return (1.0f/multiplier) * 100.0f;
}
