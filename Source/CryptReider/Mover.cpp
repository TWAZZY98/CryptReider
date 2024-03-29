// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"

#include "Math/UnrealMathUtility.h"

using namespace std;

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetOwner()->GetActorLocation();
	
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (shouldMove) {
		FVector currentLocation = GetOwner()->GetActorLocation();
		FVector TargetLocation = OriginalLocation + displacement;
		float velocity = FVector::Distance(OriginalLocation, displacement) / timeOfMovement;

		FVector NewLocation = FMath::VInterpConstantTo(currentLocation, TargetLocation, DeltaTime, velocity);
		GetOwner()->SetActorLocation(NewLocation);
	}
}

