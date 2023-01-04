// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerMove.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Components
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(200);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0,0,-200));
	meshComp->SetRelativeScale3D(FVector(4.0f));
#pragma endregion

	//Collision
	sphereComp->SetCollisionProfileName(TEXT("TrapPreset"));
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();

#pragma region Collision
	//connect collision overlap delegate to in trap function
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATrap::InTrap);
	sphereComp->OnComponentEndOverlap.AddDynamic(this, &ATrap::OutTrap);
#pragma endregion

}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TeleportTrap(DeltaTime);
}


#pragma region Collision
void ATrap::InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("In Trap"));

	APlayerMove* player = Cast<APlayerMove>(OtherActor);
	
	//if player
	if(player){
		player->canFire = false;
	}
	//canFire variables
}


void ATrap::OutTrap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	APlayerMove* player = Cast<APlayerMove>(OtherActor);

	if (player) {
		player->canFire = true;
	}
}
#pragma endregion

#pragma region TeleportTrap
void ATrap::TeleportTrap(float deltaTime)
{
	if (currentTime > teleportTime) {

#pragma region Method 1
		////random float
		//float randomNumY = FMath::RandRange(-500, 500);
		//float randomNumZ = FMath::RandRange(-800, 800);

		////convert to vector
		//FVector randomVectorPosition;
		//randomVectorPosition.Y = randomNumY;
		//randomVectorPosition.Z = randomNumZ;
		////FVector randomVectorPosition = FVector(0, randomNumY, randomNumZ);
#pragma endregion

#pragma region Method 2
	FVector randomVectorPosition = FMath::VRand() * 500.0f;
	randomVectorPosition.X = 0;
#pragma endregion

		//move there
		SetActorLocation(randomVectorPosition);

		//reset currentTIme
		currentTime = 0;
	}
	else {
		currentTime += deltaTime;
	}

}
#pragma endregion

