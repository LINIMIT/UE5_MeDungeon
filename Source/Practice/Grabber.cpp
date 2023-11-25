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

	// ...

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//FRotator MyRotation = GetComponentRotation(); //컴포넌트의 회전값을 가져옴
	//FString RotationString = MyRotation.ToCompactString();

	//UE_LOG(LogTemp, Display, TEXT("Grabber Rotation : %s"), *RotationString);

	//float Time = GetWorld()->TimeSeconds;
	//UE_LOG(LogTemp, Display, TEXT("Time : %f"), Time);

	UWorld* world = GetWorld();
	if (world)
	{
		FVector Location = GetComponentLocation();
		FVector End = Location + GetForwardVector() *MaxGrabDistance;

		DrawDebugSphere(world, Location, 25.f, 24, FColor::Red);
		DrawDebugLine(world, Location, End, FColor::Blue);
		DrawDebugPoint(world, End, 15.f, FColor::Red);
	}

}

