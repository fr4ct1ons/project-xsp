// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DynamicTwoWorldsActor.generated.h"

/**
 * 
 */
UINTERFACE()
class UDynamicTwWorldsActor : public UInterface
{
	GENERATED_BODY()
};

class IDynamicTwWorldsActor
{
	GENERATED_BODY()
	
public:
	void OnChangedPast(); 
};
