// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50, 300, 150));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(1,6,3));
	meshComp->SetRelativeLocation(FVector(0,0,-150));

	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("BossPreset"));

}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

	originalLocation = GetActorLocation();

}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveBoss(DeltaTime);
}

void ABoss::MoveBoss(float tick)
{
	FVector currentLocation = GetActorLocation();
	FVector targetLocation = originalLocation + moveOffset;

	float speed = FVector::Distance(originalLocation, targetLocation) / moveTime;

	FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, tick, speed);

	SetActorLocation(newLocation);
}