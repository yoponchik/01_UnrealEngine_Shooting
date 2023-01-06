// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSpawner.generated.h"


UCLASS()
class SHOOTER_API ABossSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Components
	UPROPERTY(EditInstanceOnly, Category = "BossSettings")
	class USceneComponent* sceneComp;

	UPROPERTY(EditInstanceOnly, Category = "BossSettings")
	class UArrowComponent* arrowComp;
#pragma endregion

	class AMyGameModeBase* gm;

	UPROPERTY(EditAnywhere, Category = "BossSpawnSettings")
	TSubclassOf<class ABoss> bossFactory;

	void CheckSpawnTime();

	void SpawnBoss();

	bool isSpawn;
	bool isDoneSpawn;

	int32 bossLevelScore = 2;
};
