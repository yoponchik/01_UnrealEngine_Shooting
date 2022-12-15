// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CodeTest.generated.h"

UCLASS()
class SHOOTER_API ACodeTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACodeTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//declare integer variables
	int32 number1;
	int32 number2;

	//declare float variables
	float float1 = 3.14f;
	float float2 = 4.97f;

	//declare string variables
	FString string1 = "Yeo Won Park";
	FString string2 = "Loser";

	//declare boolean variables
	bool isTeacher;					// same as bool isTeacher = false;
	
	bool isStudent = true;



};
