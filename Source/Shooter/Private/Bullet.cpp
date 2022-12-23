// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy.h"

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
	
#pragma region Collision


	boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);

	//Enable Overlap event
	boxComp->SetGenerateOverlapEvents(true);
#pragma endregion
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	myDirection = GetActorForwardVector();

	SetActorLocation(GetActorLocation() + myDirection * moveSpeed * DeltaTime);
}

#pragma region Collision
void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	if (enemy != nullptr) {
		//delete enemy
		enemy->Destroy();

		//delete this.bullet
		Destroy();
	}
}
#pragma endregion


