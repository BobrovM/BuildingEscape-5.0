// Fill out your copyright notice in the Description page of Project Settings.

#include "GrabberComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	CheckForPhysicsHandle();

	SetUpInputComponent();
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{
		//Move the object we are holding
		PhysicsHandle->SetTargetLocation
		(
			GetReachEnd()
		);
	}
}

void UGrabberComponent::Grab()
{
	//If it hits something, attach a physics handle to it
	FHitResult HitResult = GetFirstActorBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation
		(
			ComponentToGrab,
			NAME_None,
			GetReachEnd()
		);
	}
}

void UGrabberComponent::Release()
{
	PhysicsHandle->ReleaseComponent();
}

void UGrabberComponent::CheckForPhysicsHandle()
{
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR: Physics handle component is not found in %s!"), *GetOwner()->GetName())
	}
}

void UGrabberComponent::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabberComponent::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabberComponent::Release);
	}
}

FHitResult UGrabberComponent::GetFirstActorBodyInReach() const
{
	// Draw a line from player, make it to be able to turn on/off
	DrawDebugLine(
		GetWorld(),
		GetPlayerWorldPosition(),
		GetReachEnd(),
		FColor(0, 0, 255),
		false,
		5.f,
		0,
		5.f
	);

	// Use raycast to a 'reach distance'
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType
	(
		OUT Hit,
		GetPlayerWorldPosition(),
		GetReachEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return Hit;
}

FVector UGrabberComponent::GetReachEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + Reach * PlayerViewPointRotation.Vector();
}

FVector UGrabberComponent::GetPlayerWorldPosition() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}