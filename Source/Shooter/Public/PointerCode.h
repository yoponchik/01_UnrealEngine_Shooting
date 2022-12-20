// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointerCode.generated.h"

UCLASS()
class SHOOTER_API APointerCode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointerCode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Variables
	UPROPERTY(EditAnywhere)
	int32 pointerNumber = 30;

	//UPROPERTY(EditAnywhere)				//can't make a pointer a uproperty
	float* myAge;
	UPROPERTY(EditAnywhere)
	float realAge = 20;

};
