// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boss.generated.h"

UCLASS()
class SHOOTER_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Components
	UPROPERTY(EditAnywhere, Category = BossSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = BossSettings)
	class UStaticMeshComponent* meshComp;
#pragma endregion

	UPROPERTY(EditAnywhere, Category = "Boss Settings | Move Settings")
	float moveTime = 10;

	UPROPERTY(EditAnywhere, Category = "Boss Settings | Move Settings")
	FVector moveOffset = FVector(0,0,-200);
	
	void MoveBoss(float tick);

#pragma region Boss Attack
	UFUNCTION()
	void BossAttack1(float angle, int32 bulletNumber);
	
	void BossPatternUpdate(float tick);

	//enemybullet
	UPROPERTY(EditAnywhere, Category = "Boss Settings | Attack Settings")
	TSubclassOf<class AEnemyBullet> enemyBulletFactory;

	UPROPERTY(EditAnywhere, Category = "Boss Settings | Attack Settings")
	float bossBulletDistance = 100.0f;											//where the bullet will spawn

	UPROPERTY(EditAnywhere, Category = "Boss Settings | Attack Settings")
	float patternDelayTime = 3;													//time it takes for the next attack

	#pragma region My Boss Attack
	//UFUNCTION()
	//void MyBossAttack1(int32 bulletNumber, int32 bulletDistance, bool isFullAttack);

	//UPROPERTY(EditAnywhere, Category = BossSetings)
	//int32 bossBulletNumber = 6;

	//UPROPERTY(EditAnywhere, Category = BossSetings)
	//int32 bossBulletDistance = 100;
	//
	//bool isBossFullAttack = true;
	#pragma endregion

#pragma endregion

private:
	FVector direction;
	FVector originalLocation;

	//Boss Attack
	float currentTime=0;
};
