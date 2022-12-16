﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeTest.h"

// Sets default values
ACodeTest::ACodeTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACodeTest::BeginPlay()
{
	Super::BeginPlay();

#pragma region Day 1 - Variables

	//Day1 - Variables
	/*
	//assign variable number with integer 3
	number1 = 3;

	number2 = -7;
	

	//print value of variable number in console window
	UE_LOG(LogTemp, Warning, TEXT("Number1 is %d, Number2 is %d"), number1, number2);
	UE_LOG(LogTemp, Warning, TEXT("float1 is %.2f, float2 is %.2f"), float1, float2);
	UE_LOG(LogTemp, Warning, TEXT("Hello World! %s"), *string1);						//string formating
	

	//why do we declare it in the source file?
	FString string3 = FString(TEXT("한국어"));
	UE_LOG(LogTemp, Warning, TEXT("printing in Korean %s"), *string3);

	isTeacher = false;

	if (isTeacher) {
		UE_LOG(LogTemp, Warning, TEXT("He is a teacher."));
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("He is a student."));
	}
	*/

#pragma endregion Day 1 - Variables

#pragma region Day 2.1 - Functions: Function Implementation
	//Day 2 - Functions
	//int32 additionResult = Add(8, 4);							//Declaring a local variable and assigning a return value from function
	//UE_LOG(LogTemp, Warning, TEXT("Addition : %d"), additionResult);

	//int32 subtractResult = Subtract(10, 2);
	//UE_LOG(LogTemp, Warning, TEXT("Subtraction : %d"), subtractResult);

	//int32 multResult = Multiply(1, 2);
	//UE_LOG(LogTemp, Warning, TEXT("Multiplication : %d"), multResult);
	//
	//int32 divResult = Divide(1, 2);
	//UE_LOG(LogTemp, Warning, TEXT("Division : %d"), divResult);

	//float divFloatResult = DivideToFraction(1, 2);
	//UE_LOG(LogTemp, Warning, TEXT("Result : %.2f"), divFloatResult);					//note that this has %f
	//
#pragma endregion Day 2.1 - Functions: Function Implementation

#pragma region Day 2.2 - Conditionals: Implementation

	//if, else if, else
	//age = 20;

	//if (age > 26) {
	//	UE_LOG(LogTemp, Warning, TEXT("Too Old"));
	//}
	//else if (age == 26){
	//	UE_LOG(LogTemp, Warning, TEXT("Perfect"));
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Too Young"));
	//}

	//Using logical conditions

	//age = 26;
	//height = 166;

	//if (age >= 20 && height >= 160) {

	//	UE_LOG(LogTemp, Warning, TEXT("Welcome"));
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Get out of here."));
	//}

	age = 26;
	nationality = "Korean";

	if (nationality == "Korean" && ((20 <= age) && (age < 40))) {
		UE_LOG(LogTemp, Warning, TEXT("Korean Young Adult"));
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("Not Korean Young Adult"));
	}

#pragma endregion Day 2.2 - Conditionals: Implementation

}

// Called every frame
void ACodeTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Day 2.1 - Functions: Function Definition
//Day 2
//int32 ACodeTest::Add(int32 parameter1, int32 parameter2) {
//
//	return parameter1 + parameter2;
//}
//
//int32 ACodeTest::Subtract(int32 parameter1, int32 parameter2) {
//
//	return parameter1 - parameter2;
//}
//
//int32 ACodeTest::Multiply(int32 parameter1, int32 parameter2) {
//
//	return parameter1 * parameter2;
//}
//
//int32 ACodeTest::Divide(int32 parameter1, int32 parameter2) {
//
//	return parameter1 / parameter2;
//}
//
//float ACodeTest::DivideToFraction(int32 parameter1, int32 parameter2) {
//
//	return float(parameter1) / float(parameter2);

//}
#pragma endregion Day 2 - Functions: Function Definition
