// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialDoorYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoorAngle += InitialDoorYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("The actor called %s has OpenDoor component attached, but no TriggerVolume set."), *GetOwner()->GetName());
	}

	ActorThatIntersects = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatIntersects))
	{
		OpenDoor(DeltaTime);
		LastTimeDoorOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - LastTimeDoorOpened > DoorOpenTimeDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator CurrentDoorRotation = GetOwner()->GetActorRotation();
	CurrentDoorYaw = CurrentDoorRotation.Yaw;

	CurrentDoorRotation.Yaw = FMath::FInterpTo(CurrentDoorYaw, OpenDoorAngle, DeltaTime, DoorOpenSpeed);

	GetOwner()->SetActorRotation(CurrentDoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator CurrentDoorRotation = GetOwner()->GetActorRotation();
	CurrentDoorYaw = CurrentDoorRotation.Yaw;

	CurrentDoorRotation.Yaw = FMath::FInterpTo(CurrentDoorYaw, InitialDoorYaw, DeltaTime, DoorShutSpeed);

	GetOwner()->SetActorRotation(CurrentDoorRotation);
}

