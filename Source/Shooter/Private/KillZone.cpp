// Fill out your copyright notice in the Description page of Project Settings.


#include "KillZone.h"
#include "Components/BoxComponent.h"
#include "PlayerMove.h"

// Sets default values
AKillZone::AKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);

	boxComp->SetBoxExtent(FVector(50.0f, 2000.0f, 50.0f));

	boxComp->SetCollisionProfileName(TEXT("KilZonePreset"));
}

// Called when the game starts or when spawned
void AKillZone::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->SetGenerateOverlapEvents(true);
	
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AKillZone::OnOverlap);
}

// Called every frame
void AKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKillZone::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerMove* player = Cast<APlayerMove>(OtherActor);

	if (player != nullptr) {
		
	}
	else {
		OtherActor->Destroy();
	}
}

