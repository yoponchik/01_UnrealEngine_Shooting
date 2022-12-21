// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeTest.h"
#include "PointerCode.h"


#pragma warning (disable: 4458)				//disabling error C4458


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

#pragma endregion 

#pragma region Day 2.1 - Functions: Function Implementation
	//Day 2 - Functions
	//int32 additionresult = add(8, 4);							//declaring a local variable and assigning a return value from function
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

	//FString fullName = AppendString("Yeo Won", "Park");
	//UE_LOG(LogTemp, Warning, TEXT("Your name is: %s"), *fullName);

#pragma endregion Day 2.1 - Functions: Function Implementation

#pragma region Day 2.2 - Conditionals: Implementation

	//Check Age

	//if, else if, else
	//age = 20;

	//if (age > 26) {
	//	ue_log(logtemp, warning, text("too old"));
	//}
	//else if (age == 26){
	//	ue_log(logtemp, warning, text("perfect"));
	//}
	//else {
	//	ue_log(logtemp, warning, text("too young"));
	//}

	//using logical conditions

	//age = 26;
	//height = 166;

	//if (age >= 20 && height >= 160) {

	//	ue_log(logtemp, warning, text("welcome"));
	//}
	//else {
	//	ue_log(logtemp, warning, text("get out of here."));
	//}


	//Check Nationality

	//age = 26;
	//nationality = "Korean";

	//if (nationality == "Korean" && ((20 <= age) && (age < 40))) {
	//	UE_LOG(LogTemp, Warning, TEXT("Korean Young Adult"));
	//}
	//else{
	//	UE_LOG(LogTemp, Warning, TEXT("Not Korean Young Adult"));
	//}


	//Check if odd or even

	//int32 checker =123;

	//if ((checker % 2) == 0) {
	//	UE_LOG(LogTemp, Warning, TEXT("Even"));
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Odd"));
	//}


#pragma endregion Day 2.2 - Conditionals: Implementation

#pragma region Day 3 - Loops: Loop Implementation


	//Numbering 1 to 9
	//for (int32 i = 0; i < 10; i++) {						//i + 1 after going the next line
	////for (int32 i = 0; i < 10; ++i) {						//i + 1 before going to the next line
	//	UE_LOG(LogTemp, Warning, TEXT("%d"), i);
	//}

	//Calling Multiplication Function
	/*Multiplication(7);*/


#pragma endregion 

#pragma region Day 4.1 - Arrays and Maps: Implementation
	//Arrays
	//UE_LOG(LogTemp, Warning, TEXT("The length of the array is: %d"), ages.Num());

	//for (int32 i = 0; i < ages.Num(); i++) {
	//	UE_LOG(LogTemp, Warning, TEXT("%d"), ages[i]);
	//}

	//sort of like foreach val??
	//for (int32 age: ages) {								//ages goes into age, maybe like foreach?
	//	UE_LOG(LogTemp, Warning, TEXT("%d"), age);
	//}

	//Maps

	//distances.Add(TEXT("Seoul"), 250.5f);						//can do without Text, it's just in case it's Korean
	//distances.Add("Seoul", 250.5f);
	//distances.Add("Incheon", 345.5f);
	//distances.Add("Suwon", 999.5f);

	//FString myKey = TEXT("Incheon");

	//UE_LOG(LogTemp, Warning, TEXT("%s : %f"), *myKey, distances[myKey]);				//for finding specific value with specific key

	//showing all values and keys
	//for (auto dist : distances) {				//auto helps us find the value type automatically
	//	UE_LOG(LogTemp, Warning, TEXT("%s - %f"), *dist.Key, dist.Value);
	//}

#pragma endregion

#pragma region Day 4.2 - Pointers: Implementation

//Call by value

	int32 num1 = 10;
	int32 copyNum1 = num1;
	int32 num = 30;

	UE_LOG(LogTemp, Warning, TEXT("num1: %d, copyNum1: %d"), num1, copyNum1);


	//Call by Reference
	//pointer
	int32 num2 = 10;
	int32* copyNum2;			//pointer
	copyNum2 = &num2;
	num1 = 30;

	//UE_LOG(LogTemp, Warning, TEXT("Address of num2: %p"), num2, copyNum2);
	UE_LOG(LogTemp, Warning, TEXT("num2: %p, copyNum2: %p"), &num2, *copyNum2);
	UE_LOG(LogTemp, Warning, TEXT("num2: %p, copyNum2: %p"), num2, copyNum2);

#pragma endregion

#pragma region Day 4.3 - Pointers Practice: Implementation
// 	pointerCode->pointerNumber = 15; 							//arrow means you want to access the variable inside the class
// 	//type period "." to automatically do arrow
// 
// 	for (APointerCode* pt : pointerArray) {
// 		pt->pointerNumber = 15;
// 	}
// 
// 	*(pointerCode->myAge) = 15;
// 	pointerCode->realAge = 15;

	//if (pointerCode != nullptr) {
	//	*(pointerCode->myAge) = 15
	//}

#pragma endregion 
}








// Called every frame
void ACodeTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Day 2.1 - Functions: Function Definition
//Day 2
int32 ACodeTest::Add(int32 parameter1, int32 parameter2) {

	return parameter1 + parameter2;
}


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


//FString ACodeTest::AppendString(FString firstName, FString lastName) {
//	
//	FString fullName;
//	fullName = firstName + " " + lastName;
//
//	return fullName;
//}
#pragma endregion

#pragma region Day 3 - Loops: Loop Definition
//void ACodeTest::Multiplication(int32 multiplier) {
//	for (int32 i = 2; i < 10; i++) {
//		for (int32 j = 1; j < 10; j++) {
//			UE_LOG(LogTemp, Warning, TEXT("%d x %d = %d"), i, j, i * j);
//		}
//		UE_LOG(LogTemp, Warning, TEXT("=========================="));
//	}
//}
#pragma endregion 

