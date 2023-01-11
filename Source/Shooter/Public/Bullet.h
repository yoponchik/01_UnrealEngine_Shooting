// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet Settings | Components");
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet Settings | Components");
	class UStaticMeshComponent* meshComp;
#pragma endregion

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet Settings | Movement");
	float moveSpeed = 900;

	//boss enemybullet
	void SetBulletDirection(FVector angleInput);

private:
	FVector myDirection;

	FTimerHandle lifeTimer;

	void DestroyMyself();

};
