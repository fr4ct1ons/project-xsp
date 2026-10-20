// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityStaticTimeTracker.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TwoWorldsToolsFunctions.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXSP_API UTwoWorldsToolsFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static void TryConnectActors(AActor* FutureActor, AActor* PastActor, TSubclassOf<UEditorUtilityStaticTimeTracker> TrackerClass);
};
