// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class SHOOTER_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemySettings | Components")
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemySettings | Components")
	class UStaticMeshComponent* meshComp;
#pragma endregion

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemySettings | Movement")
	float moveSpeed = 800;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemySettings | Movement")
	float followProb = 0.3f;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemySettings | VFX")
	class UParticleSystem* explosionFX;

#pragma region Functions for Player Ultimate
	UFUNCTION()
	void DestroyMyself();																		

	UFUNCTION()
	void RedirectEnemy(FVector newDir);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;						//For removing the delegate when the actor dies 
#pragma endregion

private:
	FVector direction;
	class APlayerMove* target;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
};
