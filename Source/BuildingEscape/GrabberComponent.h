// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/ActorComponent.h"
#include "GrabberComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabberComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//Reach distance
	float Reach = 150.f;

	//nullptr to protect from crashing
	UPROPERTY()
		UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UPROPERTY()
		UInputComponent* InputComponent = nullptr;

	void Grab();
	void Release();

	void CheckForPhysicsHandle();
	void SetUpInputComponent();

	//return the first actor within reach
	FHitResult GetFirstActorBodyInReach() const;
	FVector GetReachEnd() const;
	FVector GetPlayerWorldPosition() const;
};