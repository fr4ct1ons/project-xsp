// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CommonDelegates.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIntDelegate, int32, IntValue);

/**
 * 
 */
UCLASS()
class PROJECTXSP_API UCommonDelegates : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
