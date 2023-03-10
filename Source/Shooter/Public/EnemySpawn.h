// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawn.generated.h"

UCLASS()
class SHOOTER_API AEnemySpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
#pragma region Components
	UPROPERTY(EditInstanceOnly, Category = "Enemy Spawn Settings | Components")
	class UArrowComponent* spawnArrow;
	
	UPROPERTY(EditInstanceOnly, Category = "Enemy Spawn Settings | Components")
	class USceneComponent* rootScene;
#pragma endregion

	UPROPERTY(EditInstanceOnly, Category = "Enemy Spawn Settings | Sapwn Settings")
	float spawnTime = 2;
	
	UPROPERTY(EditInstanceOnly, Category = "Enemy Spawn Settings | Sapwn Settings")
	TSubclassOf<class AEnemy> enemyFactory;


private:
	void EnemySpawner(float deltaTime);

	float currentTime;

	//boss
	class AMyGameModeBase* gm;
};
