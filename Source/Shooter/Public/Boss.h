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

	UPROPERTY(EditAnywhere, Category = BossSettings)
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, Category = BossSettings)
	class UStaticMeshComponent* meshComp;

	UPROPERTY(EditAnywhere, Category = "BossSettings")
	float moveTime = 10;

	UPROPERTY(EditAnywhere, Category = "BossSettings")
	FVector moveOffset =FVector(0,0,-200);
	
	void MoveBoss(float tick);

private:
	FVector direction;
	FVector originalLocation;
};
