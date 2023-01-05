// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSpawner.h"

#include "MyGameModeBase.h"
#include "Components/ArrowComponent.h"
#include "Boss.h"


// Sets default values
ABossSpawner::ABossSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	sceneComp = CreateDefaultSubobject<USceneComponent>("Scene Component");
	SetRootComponent(sceneComp);

	arrowComp = CreateDefaultSubobject<UArrowComponent>("Arrow Component");
	arrowComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABossSpawner::BeginPlay()
{
	Super::BeginPlay();


	gm = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());

	isSpawn = false;
	isDoneSpawn = false;

}

// Called every frame
void ABossSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckSpawnTime();

	if(isSpawn){
		SpawnBoss();
	}

}


//spawn has to be in the gameMode
void ABossSpawner::SpawnBoss()
{
//if done spawning, don't run function
	if(isDoneSpawn){return;}

	(gm->canSpawnEnemy) = false;

	GetWorld()->SpawnActor<ABoss>(bossFactory, arrowComp->GetComponentLocation(), arrowComp->GetComponentRotation());
	UE_LOG(LogTemp, Warning, TEXT("Spawning Boss"));
	isDoneSpawn = true;
}

void ABossSpawner::CheckSpawnTime()
{
//if done spawning, don't run function
	if (isSpawn) { return; }

	if (gm != nullptr) {
		if ((gm->currentScore) > 2) {
			isSpawn = true;
			UE_LOG(LogTemp, Warning, TEXT("Spawn Boss"));
		}
	}
}



