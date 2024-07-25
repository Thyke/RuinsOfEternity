// // Copyright (C) 2023 Thyke. All Rights Reserved.


#include "Components/RuinHeroComponent.h"

// Sets default values for this component's properties
URuinHeroComponent::URuinHeroComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URuinHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URuinHeroComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

