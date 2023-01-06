// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bullet.h"
#include "PlayerBullet.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API APlayerBullet : public ABullet
{
	GENERATED_BODY()
	
public:
	//Constructor
	APlayerBullet();

	virtual void BeginPlay() override;


#pragma region Collision
//need to delete from bullet.h because they have an inheritance relationship
	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

#pragma endregion
};
