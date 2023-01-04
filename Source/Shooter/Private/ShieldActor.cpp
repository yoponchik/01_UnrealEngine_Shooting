// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"
#include "PlayerMove.h"

// Sets default values
AShieldActor::AShieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Components
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50, 150, 50));
	
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(1.0f, 3.0f, 1.0f));
	meshComp->SetRelativeLocation(FVector(0, 0, -50));
#pragma endregion

#pragma region Collision
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);

	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AShieldActor::ShieldOverlap);
#pragma endregion

}

// Called when the game starts or when spawned
void AShieldActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if(isAttached){
		SpinShield();
	}
	else{
		ResetAttach();
	}

}

void AShieldActor::ShieldOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	APlayerMove* player = Cast<APlayerMove>(OtherActor);

	//if collision with enemy
	if (enemy != nullptr) {
		//destroy
		enemy->Destroy();
	}

	//if collision with player
	else if(player != nullptr){
		//joint with player
		//this->AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);					//Keep -> The moment the two actors collide
		this->AttachToActor(OtherActor, FAttachmentTransformRules::SnapToTargetIncludingScale);				//Snaps to each other's pivot
		
		isAttached = true;
		(player->shieldActor) = this;

	}
}

void AShieldActor::SpinShield()
{
	FRotator rotAngle = FRotator(0,0,20);
	AddActorLocalRotation(rotAngle);					//
	//SetActorRotation()								//only sets it, so have to change the parameter

}

void AShieldActor::ResetAttach()
{
	FTimerHandle snapTimer;
	GetWorld()->GetTimerManager().SetTimer(snapTimer, this, &AShieldActor::ResetAttach, 3, false);
	isAttached = false;

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

