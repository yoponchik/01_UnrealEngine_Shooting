// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "EnemyBullet.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AEnemyBullet : public ABullet
{
	GENERATED_BODY()
	
public:
	AEnemyBullet();

	virtual void BeginPlay() override;

#pragma region Collision
	//can have same name as playerbullet because not inherited each other
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
#pragma endregion


};
