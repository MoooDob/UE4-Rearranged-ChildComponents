// Copyright 2019 Marc O. Rüdel. All Rights Reserved.


#include "MyActor.h"
#include "MySceneComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyActor::PostRegisterAllComponents()
{
	UE_LOG(LogTemp, Log, TEXT("AMyActor '%s': PostRegisterAllComponents BEGIN"), *GetName())

	Super::PostRegisterAllComponents();
	
	TArray<UActorComponent*> MySceneComponents = GetComponentsByClass(UMySceneComponent::StaticClass());
	for (UActorComponent* comp : MySceneComponents) {
		UMySceneComponent* myscenecomponent = Cast<UMySceneComponent>(comp);
		if (myscenecomponent) {
			myscenecomponent->PostRegisterSubComponents();
		}
	}

	UE_LOG(LogTemp, Log, TEXT("AMyActor '%s': PostRegisterAllComponents END"), *GetName())
}
