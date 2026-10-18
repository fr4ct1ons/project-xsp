// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityActorComponent.h"
#include "EditorUtilityStaticTimeTracker.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXSP_API UEditorUtilityStaticTimeTracker : public UEditorUtilityActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsFutureWorld = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UEditorUtilityStaticTimeTracker> Other;

public:
	UFUNCTION(BlueprintCallable)
	void ExternalSetup(bool newIsFutureWorld, UEditorUtilityStaticTimeTracker* newOther);
};
