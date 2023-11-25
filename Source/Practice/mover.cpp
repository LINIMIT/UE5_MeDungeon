// Fill out your copyright notice in the Description page of Project Settings.


#include "mover.h"

// Sets default values for this component's properties
Umover::Umover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Umover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Umover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	AActor* Owner = GetOwner();
	FString Name = (*Owner).GetActorNameOrLabel();
	FVector ActorLocation = (*Owner).GetActorLocation();
	FString OwnerLocationString = ActorLocation.ToCompactString();


	UE_LOG(LogTemp, Display, TEXT("%s"), *OwnerLocationString);

}

