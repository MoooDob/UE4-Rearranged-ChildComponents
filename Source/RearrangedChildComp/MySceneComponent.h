// Copyright 2019 Marc O. Rüdel. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CoreGlobals.h"
#include "MySceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class REARRANGEDCHILDCOMP_API UMySceneComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMySceneComponent();

	// Called from AMyActor when PostRegisterAllComponents is called
	virtual void PostRegisterSubComponents();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "DEBUG")
	TArray<USceneComponent*> ArrangedChildComponents;

public:	
	
	/* UObject override BEGIN */ 

	// Handles reading, writing, and reference collecting using FArchive. This implementation handles all UProperty serialization, but can be overridden for native variables.
	virtual void Serialize(FArchive & Ar) override;	
		
	/* UObject override END */

};
