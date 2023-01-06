// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

//enemybullet
#include "Kismet/KismetMathLibrary.h"
#include "EnemyBullet.h"



// Sets default values
ABoss::ABoss()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Components
	boxComp = CreateDefaultSubobject<UBoxComponent>("Box Comp");
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50, 300, 150));

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	meshComp->SetupAttachment(RootComponent);
	meshComp->SetRelativeScale3D(FVector(1,6,3));
	meshComp->SetRelativeLocation(FVector(0,0,-150));
#pragma endregion

#pragma region Collision
	boxComp->SetGenerateOverlapEvents(true);
	boxComp->SetCollisionProfileName(TEXT("BossPreset"));
#pragma endregion

}

// Called when the game starts or when spawned
void ABoss::BeginPlay()
{
	Super::BeginPlay();

	originalLocation = GetActorLocation();
}

// Called every frame
void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveBoss(DeltaTime);

	BossPatternUpdate(DeltaTime);
}

#pragma region Move Boss
void ABoss::MoveBoss(float tick)
{
	FVector currentLocation = GetActorLocation();
	FVector targetLocation = originalLocation + moveOffset;

	float speed = FVector::Distance(originalLocation, targetLocation) / moveTime;

	FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, tick, speed);

	SetActorLocation(newLocation);
}
#pragma endregion

#pragma region Boss Pattern
void ABoss::BossPatternUpdate(float tick)
{
	//enemybullet
	if (currentTime > patternDelayTime) {
		BossAttack1(15, 6);

		//My try; buggy
		//MyBossAttack1(bossBulletNumber, bossBulletNumber, isBossFullAttack);
		currentTime = 0;
	}
	else {
		currentTime += tick;
	}
}
#pragma endregion


#pragma region Boss Attack - Method 1
//void ABoss::BossAttack1(float angle, int32 bulletNumber)
//{
//	UE_LOG(LogTemp, Warning, TEXT("BossAttack1"));
//	
//	//start angle = 270 - (angle * count-1) * 0.5
//	float startAngle = 270 - (angle*(bulletNumber -1)*0.5f);
//
//	for(int32 i = 0; i < bulletNumber; i++){
//		FVector bulletPivotAngle = FVector(0, 1000 * FMath::Cos(FMath::DegreesToRadians(startAngle + angle * i)), 1000 * FMath::Sin(FMath::DegreesToRadians(startAngle + angle * i)));
//
//		//Method 1
//		//must test - changing the moving direction
//		AEnemyBullet* enemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(enemyBulletFactory, GetActorLocation() + bulletPivotAngle, FRotator::ZeroRotator);
//		enemyBullet->SetBulletDirection(bulletPivotAngle.GetSafeNormal());
//
//	}
//}
#pragma endregion

#pragma region Boss Attack - Method 2
void ABoss::BossAttack1(float angle, int32 bulletNumber)
{
	UE_LOG(LogTemp, Warning, TEXT("BossAttack1"));
	
	//start angle = 270 - (angle * count-1) * 0.5
	float startAngle = 270 - (angle*(bulletNumber -1)*0.5f);

	for(int32 i = 0; i < bulletNumber; i++){
		FVector bulletPivotAngle = FVector(0, 1000 * FMath::Cos(FMath::DegreesToRadians(startAngle + angle * i)), 1000 * FMath::Sin(FMath::DegreesToRadians(startAngle + angle * i)));

		//Method 1
		//must test - changing the moving direction
		//enemyBullet->SetBulletDirection(bulletPivotAngle.GetSafeNormal());
		//AEnemyBullet* enemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(enemyBulletFactory, GetActorLocation() + bulletPivotAngle, FRotator::ZeroRotator);

		//method 2 - changing the ?
		AEnemyBullet* enemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(enemyBulletFactory, GetActorLocation() + bulletPivotAngle, FRotator(-90,0,0));
		//calculate rotation
		FRotator rot = UKismetMathLibrary::MakeRotFromZX(enemyBullet->GetActorUpVector(), bulletPivotAngle.GetSafeNormal());
		//input calculated rotation angle when the up vector axis is rotated towards the bulletPivot angle
		enemyBullet->SetActorRotation(rot);
	}
}
#pragma endregion

#pragma region My Boss Attack - Buggy
void ABoss::MyBossAttack1(int32 bulletNumber, int32 bulletDistance, bool isFullAttack){
	
	float theta = 0;

	if(isBossFullAttack){			//round attack
		theta = 2 * PI; 
	}
	else{							//front attack
		theta = PI;
	}

	theta /= bossBulletNumber;

	for(int32 i = 0; i < bulletNumber; i++){

		FVector bulletPosition;

		bulletPosition.Y = bulletDistance * FMath::Sin(theta);  
		bulletPosition.Z = bulletDistance * FMath::Cos(theta);  
		 
		FRotator bulletRotation = FRotator(0, theta + (theta * i),0);

		//AEnemyBullet* enemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(enemyBulletFactory, bulletPosition, bulletRotation);
		AEnemyBullet* enemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(enemyBulletFactory, bulletPosition, FRotator::ZeroRotator);

		if (enemyBullet != nullptr)
		{
			enemyBullet->AddActorLocalRotation(bulletRotation);
		}

	}
	
}
#pragma endregion
