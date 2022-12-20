// Fill out your copyright notice in the Description page of Project Settings.


#include "PointerCode.h"

// Sets default values
APointerCode::APointerCode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region 	Day 4.3 - Pointers Practice : Implementation
	myAge = &realAge;
#pragma endregion


}

// Called when the game starts or when spawned
void APointerCode::BeginPlay()
{
	Super::BeginPlay();
	
	//myAge = &realAge;			move to initializer to make sure the pointer is not null point before BeginPlay

}

// Called every frame
void APointerCode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

