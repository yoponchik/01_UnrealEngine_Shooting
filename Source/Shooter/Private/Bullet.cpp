// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"


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
	
#pragma region Components
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);

	//Enable Overlap event
	boxComp->SetGenerateOverlapEvents(true);
#pragma endregion

	//Method 1
	//SetLifeSpan(2.0f);		//Destroyed after 2 seconds
	
	//Method 2
	GetWorld()->GetTimerManager().SetTimer(lifeTimer, this, &ABullet::DestroyMyself, 2.0f, false);			//true makes it repeat
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	myDirection = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + myDirection * moveSpeed * DeltaTime);
}

#pragma region Collision & Scores
void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	if (enemy != nullptr) {
		
		//get enemy location
		FVector enemyPos = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionEffect, enemyPos, enemyRot, true);

		//explosion VFX at the enemy position

		//delete enemy
		enemy->Destroy();

#pragma region AddScore (AMyGameModeBase)
		//Add Game mode's score by 1
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);		//Game mode can be accessed from my any script. dont need to cast,etc
		//AGameModeBase* gm = GetWorld()->GetAuthGameMode();			//Same thing > useful when you didn't include UGameplayStatics
		AMyGameModeBase* myGM = Cast<AMyGameModeBase>(gm);

		myGM->AddScore(1);
#pragma region Debug
		//UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());
#pragma endregion
#pragma endregion

		//delete this.bullet
		Destroy();
	}
}
#pragma endregion

void ABullet::DestroyMyself() {
	Destroy();
}
