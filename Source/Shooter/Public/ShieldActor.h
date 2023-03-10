// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShieldActor.generated.h"

UCLASS()
class SHOOTER_API AShieldActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShieldActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Shield Settings | Components")
	class UBoxComponent* boxComp;
	
	UPROPERTY(EditAnywhere, Category = "Shield Settings | Components")
	class UStaticMeshComponent* meshComp;

	UFUNCTION()
	void ShieldOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

#pragma region Spin
	UFUNCTION()
	void SpinShield();

	bool isAttached;														//used in PlayerMove

	UFUNCTION()
	void ResetAttach();
#pragma endregion
};
