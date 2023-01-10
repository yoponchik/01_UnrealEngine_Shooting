// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"



// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Initialize Components
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));			//Create box collider component
	SetRootComponent(boxComp);														//Set as root		
	boxComp->SetBoxExtent(FVector(50));												//change box size
	boxComp->SetWorldScale3D(FVector( 0.25f, .1f, .1f));


	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));	//crate SN component
	meshComp->SetupAttachment(RootComponent);										//Child the mesh comp
	meshComp->SetRelativeLocation(FVector(0,0,-50));			//move box collider to match position with mesh
#pragma endregion
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

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

//boss enemy bullet
void ABullet::SetBulletDirection(FVector angleInput)
{
	myDirection = angleInput;
}

void ABullet::DestroyMyself() {
	Destroy();
}
