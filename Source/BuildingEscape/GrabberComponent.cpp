// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GrabberComponent.h"

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

void UGrabberComponent::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber grabed"));

	FHitResult Hit = GetFirstActorBodyInReach();
	// See what it hits

	//If it hits something, attach a physics handle to it
	//TODO attach physics handle
}

void UGrabberComponent::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber released"));

	//TODO release physics handle
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

	// Get player's viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint
	(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + Reach * PlayerViewPointRotation.Vector();

	// Draw a line from player, make it to be able to turn on/off
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
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
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* HitActor;

	if (Hit.bBlockingHit)
	{
		HitActor = Hit.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Trace is hitting %s"), *HitActor->GetName());
	}

	return Hit;
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}