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

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(sphereComp);
	sphereComp->SetSphereRadius(200);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeLocation(FVector(0,0,-200));
	meshComp->SetRelativeScale3D(FVector(4.0f));

	//Collision
	sphereComp->SetCollisionProfileName(TEXT("TrapPreset"));
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();

	//connect collision overlap delegate to in trap function
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATrap::InTrap);

}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrap::InTrap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("In Trap"));

	//if player
	
	APlayerMove* player = Cast<APlayerMove>(OtherActor);
	
	if(player){
		player->canFire = false;
	}
	//canFire variables
}

