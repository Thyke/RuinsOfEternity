// // Copyright (C) 2023 Thyke. All Rights Reserved.


#include "Character/RuinCharacter.h"

// Sets default values
ARuinCharacter::ARuinCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARuinCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARuinCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARuinCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

