// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Grabber.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const{

	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr){
		UE_LOG(LogTemp, Error, TEXT("Grabber needs a physics handle"));
	}
	return PhysicsHandle;

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();
	
	//if(PhysicsHandle->GetGrabbedComponent() != nullptr){
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	//}
	//FString a = GetForwardVector().ToCompactString();
	//UE_LOG(LogTemp, Display, TEXT("forward vector %s"), *a);
}

void UGrabber::Grab()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit) {
		//UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent-> WakeAllRigidBodies();
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

void UGrabber::Release()
{
	UPhysicsHandleComponent *PhysicsHandle = GetPhysicsHandle();

	if(PhysicsHandle->GetGrabbedComponent() != nullptr){
		PhysicsHandle->GetGrabbedComponent() -> WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}


bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const{

	FVector Start = GetComponentLocation();
	FVector End = Start + (GetForwardVector()* MaxGrabDistance);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10,10,FColor::Blue,false,5);
	
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);
}





