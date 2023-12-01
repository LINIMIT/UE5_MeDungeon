// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
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


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhyscisHandle = GetPhyscisHandle();
	if (PhyscisHandle == nullptr)
	{
		return;
	}

	if (PhyscisHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhyscisHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}


	FVector Location = GetComponentLocation();
	FVector End = Location + GetForwardVector() * MaxGrabDistance;


	DrawDebugSphere(GetWorld(), Location, 25.f, 24, FColor::Red);
	DrawDebugLine(GetWorld(), Location, End, FColor::Blue);
	DrawDebugPoint(GetWorld(), End, 15.f, FColor::Red);

}

void UGrabber::Grab() //물건을 잡았을 때
{

	UPhysicsHandleComponent* PhyscisHandle = GetPhyscisHandle();

	if (PhyscisHandle == nullptr)
	{
		return;
	}
	FVector Location = GetComponentLocation();
	FVector End = Location + GetForwardVector() * MaxGrabDistance;


	/*DrawDebugSphere(GetWorld(), Location, 25.f, 24, FColor::Red, false, 5);
	DrawDebugLine(GetWorld(), Location, End, FColor::Blue, false, 5);
	DrawDebugPoint(GetWorld(), End, 15.f, FColor::Red, false, 5);*/

	FHitResult HitResult;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();


		PhyscisHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}

}
void UGrabber::Release()
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhyscisHandle();
	if (PhysicsHandle == nullptr)
	{
		return;
	}
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->ReleaseComponent();
	}

}
UPhysicsHandleComponent* UGrabber::GetPhyscisHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Grabber requires a UPhysicshandleComponent"));

	}
	return Result;
}
