// Copyright 2019 Marc O. Rüdel. All Rights Reserved.


#include "MySceneComponent.h"
#include "MyActor.h"
#include "UnrealString.h"
#include "Utils.h"


// Sets default values for this component's properties
UMySceneComponent::UMySceneComponent()
{
	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s': constructor BEGIN"), *GetName());
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	bWantsInitializeComponent = true;
	bWantsOnUpdateTransform = true;

	// ...
	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s': constructor END"), *GetName());
}

// Called from AMyActor when PostRegisterAllComponents is called
void UMySceneComponent::PostRegisterSubComponents()
{
	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s': PostRegisterSubComponents BEGIN"), *GetName());

	TArray<USceneComponent*> ChildrenComponentsArray;
	GetChildrenComponents(false, ChildrenComponentsArray);
	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s':  PostRegisterSubComponents %s"), *GetName(), *(FString("current ChildrenComponents:\n") + ArrayOfUObjectToString(&ChildrenComponentsArray, "\n")));
	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s':  PostRegisterSubComponents %s"), *GetName(), *(FString("ArrangedChildComponents:\n") + ArrayOfUObjectToString(&ArrangedChildComponents, "\n")));

	// Rearrange attached components according to ArrangedChildComponents array
	for (auto item : ArrangedChildComponents) {
		item->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		item->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	}

	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s': PostRegisterSubComponents END"), *GetName());
}

// Called when the game starts
void UMySceneComponent::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s': BeginPlay BEGIN"), *GetName());
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s': BeginPlay END"), *GetName());
}



void UMySceneComponent::Serialize(FArchive & Ar)
{
	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s': Serialize BEGIN with ArchiveName: %s, \n%s"), 
		*GetName(),
		*Ar.GetArchiveName(),
		*(
			FString("") +
			(Ar.IsLoading() ? "IsLoading " : "") +
			(Ar.IsSaving() ? "IsSaving " : "") +
			(Ar.IsPersistent() ? "IsPersistent " : "") +
			(Ar.IsTextFormat() ? "IsTextFormat " : "") +
			(Ar.IsTransacting() ? "IsTransacting " : "") +
			(Ar.ContainsCode() ? "ContainsCode " : "") +  // Quickly tell if an archive contains script code
			(Ar.ArAllowLazyLoading ? "ArAllowLazyLoading " : "") +
			(Ar.ContainsMap() ? "ContainsMap " : "") + // Used to determine whether FArchive contains a level or world
			//"ArCustomPropertyList " + (Ar.ArCustomPropertyList + // Custom property list attribute.
			(Ar.IsError() ? "IsError " : "") + // Whether this archive contains errors
			(Ar.IsCriticalError() ? "IsCriticalError " : "") + // Whether this archive contains critical errors
			(Ar.IsAllowingLazyLoading() ? "IsAllowingLazyLoading " : "") + // Whether to allow lazy loading
			"ArDebugSerializationFlags=" + FString::FromInt(Ar.ArDebugSerializationFlags) + " " +// Custom serialization modifier flags can be used for anything
			(Ar.ForceByteSwapping() ? "ForceByteSwapping " : "") + // Whether we should forcefully swap bytes
			(Ar.IsIgnoringClassRef() ? "IsIgnoringClassRef " : "") + // If truewe will not serialize the ObjectArchetype reference in UObject
			(Ar.ArIgnoreClassRef ? "ArIgnoreArchetypeRef " : "") + // If trueUObject::Serialize will skip serialization of the Class property
			(Ar.ArIgnoreClassGeneratedByRef ? "ArIgnoreClassGeneratedByRef " : "") + // If truewe will not serialize ClassGeneratedBy reference in UClass
			(Ar.ArIgnoreOuterRef ? "ArIgnoreOuterRef " : "") + // If truewe will not serialize the Outer reference in UObject
			(Ar.ArIsCountingMemory ? "ArIsCountingMemory " : "") + // Whether this archive is counting memory and therefore wants e.g.TMaps to be serialized
			(Ar.ArIsFilterEditorOnly ? "ArIsFilterEditorOnly " : "") + // Whether editor only properties are being filtered from the archive(or has been filtered)
			(Ar.ArIsModifyingWeakAndStrongReferences ? "ArIsModifyingWeakAndStrongReferences " : "") + // Whether a reference collector is modifying the references and wants both weak and strong ones
			(Ar.ArIsNetArchive ? "ArIsNetArchive " : "") + // Whether or not this archive is sending / receiving network data
			(Ar.ArIsObjectReferenceCollector ? "ArIsObjectReferenceCollector " : "") + // Whether this archive only cares about serializing object references
			(Ar.IsSaveGame() ? "IsSaveGame " : "") + // Whether this archive is saving / loading game state
			"GetMaxSerializeSize=" + FString::FromInt(Ar.GetMaxSerializeSize()) + " " + // Max size of data that this archive is allowed to serialize
			(Ar.DoDelta() ? "DoDelta " : "") + // If truedo not perform delta serialization of properties
			(Ar.DoIntraPropertyDelta() ? "DoIntraPropertyDelta " : "") + // If truedo not perform delta serialization within properties(e.g.TMaps and TSets)
			(Ar.ArPortFlags ? "ArPortFlags " : "") + // Modifier flags that be used when serializing UProperties
			(Ar.RequiresLocalizationGather() ? "RequiresLocalizationGather " : "") + // Used to determine whether FArchive contains data required to be gathered for localization
			(Ar.IsSerializingDefaults() ? "IsSerializingDefaults " : "") + // Whether we are currently serializing defaults. > 0 means yes<  0 means no
			(Ar.ArShouldSkipBulkData ? "ArShouldSkipBulkData " : "") + // Whether bulk data serialization should be skipped or not
			(Ar.ArUseCustomPropertyList ? "ArUseCustomPropertyList " : "")  // Set TRUE to use the custom property list attribute for serialization
		)
	);

	Super::Serialize(Ar);

	if (Ar.IsSaving()) {
		GetChildrenComponents(false, ArrangedChildComponents);
		UE_LOG(LogTemp, Log, TEXT("%s"), *(FString("set ArrangedChildComponents:\n  - ") + ArrayOfUObjectToString(&ArrangedChildComponents, "\n")));
	}

	UE_LOG(LogTemp, Log, TEXT("UMySceneComponent '%s': Serialize END"), *GetName());

}
