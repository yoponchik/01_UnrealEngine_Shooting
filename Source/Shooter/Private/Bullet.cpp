// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Initialize Colliders Meshes
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));			//Create box collider component
	SetRootComponent(boxComp);														//Set as root		
	boxComp->SetBoxExtent(FVector(50));												//change box size
	boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.00f));


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));	//crate SN component
	meshComp->SetupAttachment(RootComponent);										//Child the mesh comp
	meshComp->SetRelativeLocation(FVector(0,0,-50));			//move box collider to match position with mesh


#pragma endregion

#pragma region Collision
	boxComp->SetCollisionProfileName(TEXT("BulletCollisionPreset"));
#pragma endregion
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	myDirection = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + myDirection * moveSpeed * DeltaTime);
}


