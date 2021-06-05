// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	float GetTotalMassOfOverlapingActors() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float InitialDoorYaw;
	float CurrentDoorYaw;
	float LastTimeDoorOpened = 0.f;

	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);

	UPROPERTY(EditAnywhere)
		float OpenDoorAngle = 90.f;
	
	UPROPERTY(EditAnywhere)
		float DoorOpenTimeDelay = 0.5f;

	UPROPERTY(EditAnywhere)
		float DoorOpenSpeed = 3.f;

	UPROPERTY(EditAnywhere)
		float DoorShutSpeed = 5.f;

	UPROPERTY(EditAnywhere)
		float OpenMass = 8.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		AActor* ActorThatIntersects;
};
