// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class SHOOTER_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

#pragma region Components
	//USphereComponent -> root collision
	UPROPERTY(EditAnywhere, Category = "Trap Settings | Components")
	class USphereComponent* sphereComp;

	//StaticMesh as child component
	UPROPERTY(EditAnywhere, Category = "Trap Settings | Components")
	class UStaticMeshComponent* meshComp;
#pragma endregion

#pragma region Collision
	//in trap 
	UFUNCTION()
	void InTrap(UPrimitiveComponent* OverlappedComponent, 
			AActor* OtherActor, 
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, 
			bool bFromSweep, 
			const FHitResult& SweepResult);

	UFUNCTION()
	void OutTrap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex);
#pragma endregion

#pragma region TeleportTrap
	void TeleportTrap(float deltaTime);
	
	UPROPERTY(EditAnywhere, Category = "Trap Settings | Movement")
	float teleportTime = 2;
#pragma endregion

private:
	float currentTime;
};
