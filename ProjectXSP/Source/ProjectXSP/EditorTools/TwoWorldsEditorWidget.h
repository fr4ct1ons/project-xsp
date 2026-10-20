// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "EditorUtilityStaticTimeTracker.h"
#include "EditorUtilityWidgetComponents.h"
#include "Components/TextBlock.h"
#include "Selection.h"
#include "Subsystems/EditorActorSubsystem.h"


#include "TwoWorldsEditorWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXSP_API UTwoWorldsEditorWidget : public UEditorUtilityWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditorUtilityButton> ConnectActorsButton_Alt1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEditorUtilityButton> ConnectActorsButton_Alt2;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActorLabel_Alt1;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ActorLabel_Alt2;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> Actor_Alt1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> Actor_Alt2;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> ConnectionInfoText;

	FDelegateHandle CurrentHandle;

	void OnSelectionChanged(UObject* obj);

	virtual void NativePreConstruct() override;

	virtual void NativeDestruct() override;
	
	
	UFUNCTION(BlueprintCallable)
	void TryConnectActors(AActor* FutureActor, AActor* PastActor, TSubclassOf<UEditorUtilityStaticTimeTracker> TrackerClass);
};
