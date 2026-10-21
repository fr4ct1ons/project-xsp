// Fill out your copyright notice in the Description page of Project Settings.


#include "TwoWorldsEditorWidget.h"

#include "SubobjectDataSubsystem.h"


void UTwoWorldsEditorWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

#if WITH_EDITOR
	FDelegateHandle handle = USelection::SelectObjectEvent.AddUObject(this, &UTwoWorldsEditorWidget::OnSelectionChanged);
	CurrentHandle = handle;
#endif
}

void UTwoWorldsEditorWidget::NativeDestruct()
{
	Super::NativeDestruct();

#if WITH_EDITOR
	USelection::SelectObjectEvent.Remove(CurrentHandle);
	CurrentHandle.Reset();
#endif
}

void UTwoWorldsEditorWidget::OnSelectionChanged(UObject* obj)
{

#if WITH_EDITOR
	TObjectPtr<UEditorActorSubsystem> system = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();
	TArray<AActor*> actors = system->GetSelectedLevelActors();
	
	ConnectActorsButton_Alt1->SetIsEnabled(false);
	ConnectActorsButton_Alt2->SetIsEnabled(false);
	
	ActorLabel_Alt1->SetText(FText::FromString("..."));
	ActorLabel_Alt2->SetText(FText::FromString("..."));

	if (actors.Num() > 0 && actors.Num() <= 2)
	{
		if (IsValid(actors[0]))
		{
			Actor_Alt1 = actors[0];

			if(IsValid(Actor_Alt1->GetComponentByClass<UEditorUtilityStaticTimeTracker>()))
			{
				ConnectionInfoText->SetText(FText::FromString(Actor_Alt1->GetActorLabel() + " already has a tracker!"));
				ConnectionInfoText->SetColorAndOpacity(FColor::Red);
				return;
			}

			ActorLabel_Alt1->SetText(FText::FromString(Actor_Alt1->GetActorLabel()));
			ActorLabel_Alt2->SetText(FText::FromString("..."));
		}
		if(actors.Num() == 2 && IsValid(actors[1]))
		{
			Actor_Alt2 = actors[1];

			if(IsValid(Actor_Alt2->GetComponentByClass<UEditorUtilityStaticTimeTracker>()))
			{
				ConnectionInfoText->SetText(FText::FromString(Actor_Alt2->GetActorLabel() + " already has a tracker!"));
				ConnectionInfoText->SetColorAndOpacity(FColor::Red);
				return;
			}
			ActorLabel_Alt2->SetText(FText::FromString(Actor_Alt2->GetActorLabel()));
			
			ConnectActorsButton_Alt1->SetIsEnabled(true);
			ConnectActorsButton_Alt2->SetIsEnabled(true);

			ConnectionInfoText->SetText(FText::FromString("Two actors were selected!"));
			ConnectionInfoText->SetColorAndOpacity(FColor::Green);
		}
	}
	else
	{
		ConnectionInfoText->SetText(FText::FromString("Number of selected actors is different from two."));
		ConnectionInfoText->SetColorAndOpacity(FColor::Orange);
	}
#endif
	
}

void UTwoWorldsEditorWidget::TryConnectActors(AActor* FutureActor, AActor* PastActor, TSubclassOf<UEditorUtilityStaticTimeTracker> TrackerClass)
{
	if(!IsValid(FutureActor) || !IsValid(PastActor))
	{
		return;
	}

	if(IsValid(FutureActor->GetComponentByClass<UEditorUtilityStaticTimeTracker>()))
	{
		return;
	}

	if(IsValid(PastActor->GetComponentByClass<UEditorUtilityStaticTimeTracker>()))
	{
		return;
	}
	

	GEditor->BeginTransaction(TEXT("Connecting two world objects"), FText::FromString("Adding UEditorUtilityStaticTimeTracker to two Actors"), FutureActor);
	FutureActor->Modify();
	PastActor->Modify();
	
	TObjectPtr<UEditorUtilityStaticTimeTracker> CompFuture = NewObject<UEditorUtilityStaticTimeTracker>(FutureActor, TrackerClass); //Cast<UEditorUtilityStaticTimeTracker>(FutureActor->AddComponentByClass(TrackerClass, false, FutureActor->GetTransform(), true));
	TObjectPtr<UEditorUtilityStaticTimeTracker> CompPast   = NewObject<UEditorUtilityStaticTimeTracker>(PastActor, TrackerClass); //Cast<UEditorUtilityStaticTimeTracker>(PastActor->AddComponentByClass(TrackerClass, false, FutureActor->GetTransform(), true));

	CompFuture->Modify();
	CompPast->Modify();
	
	FutureActor->AddInstanceComponent(CompFuture);
	PastActor->AddInstanceComponent(CompPast);

	CompFuture->RegisterComponent();
	CompPast->RegisterComponent();
	
	CompFuture->ExternalSetup(true, CompPast);
	CompPast->ExternalSetup(false, CompFuture);

	GEditor->EndTransaction();

	
	ConnectActorsButton_Alt1->SetIsEnabled(false);
	ConnectActorsButton_Alt2->SetIsEnabled(false);
	ConnectionInfoText->SetText(FText::FromString("Actors connected successfully!"));
	ConnectionInfoText->SetColorAndOpacity(FColor::Cyan);
}
