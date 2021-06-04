// Fill out your copyright notice in the Description page of Project Settings.
//I CHOOSED A WRONG CLASS, TOO LASY TO DELETE, COS IT'S ALOT OF MOVES!
//I CHOOSED A WRONG CLASS, TOO LASY TO DELETE, COS IT'S ALOT OF MOVES!
//I CHOOSED A WRONG CLASS, TOO LASY TO DELETE, COS IT'S ALOT OF MOVES!
//I CHOOSED A WRONG CLASS, TOO LASY TO DELETE, COS IT'S ALOT OF MOVES!
//I CHOOSED A WRONG CLASS, TOO LASY TO DELETE, COS IT'S ALOT OF MOVES!
//I CHOOSED A WRONG CLASS, TOO LASY TO DELETE, COS IT'S ALOT OF MOVES!

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabComponent.generated.h"

UCLASS()
class BUILDINGESCAPE_API AGrabComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
