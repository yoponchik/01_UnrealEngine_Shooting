// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawn.h"
#include "Enemy.h"
#include "Components/ArrowComponent.h"

// Sets default values
AEnemySpawn::AEnemySpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Components
	rootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	SetRootComponent(rootScene);

	spawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn Arrow"));
	spawnArrow->SetupAttachment(RootComponent);
#pragma endregion

}

// Called when the game starts or when spawned
void AEnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EnemySpawner(DeltaTime);

}

#pragma region Enemy Spawner
void AEnemySpawn::EnemySpawner(float deltaTime)
{
	//get time expired
	currentTime += deltaTime;

	//if time expired is > than spawn time, instantiate
	if (currentTime >= spawnTime) {
		//instantiate BP enemy
		//GetWorld()->SpawnActor<AEnemy>(enemyFactory, GetActorLocation(), GetActorRotation());
		GetWorld()->SpawnActor<AEnemy>(enemyFactory, spawnArrow->GetComponentLocation(), spawnArrow->GetComponentRotation());

		//reset currentTime
		currentTime = 0;
	}
}
#pragma endregion


