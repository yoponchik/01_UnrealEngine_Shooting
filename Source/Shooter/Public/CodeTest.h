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

	//Editable Variables
	UPROPERTY(EditAnywhere)
	int32 editAnywhere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 blueprintReadWrite;
	UPROPERTY(EditDefaultsOnly)
	int32 editDefaultsOnly;
	UPROPERTY(EditInstanceOnly)
	int32 editInstanceOnly;


	//Read only varibles
	UPROPERTY(VisibleAnywhere)
	int32 visibleAnywhere;
	UPROPERTY(VisibleDefaultsOnly)
	int32 visibleDefaultsOnly;
	UPROPERTY(VisibleInstanceOnly)
	int32 visibleInstanceOnly;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 blueprintReadOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CodeVariable)
	int32 variableWithCodeVariable;

	//Day 2 Functions
	int32 Add(int32 number1, int32 number2);				//declaring function



};
