// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category=DefaultSettings)
	TSubclassOf<class UMainWidget> mainWidget;

	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentScore() {return currentScore;}

	virtual void BeginPlay() override;

	void AddScore(int32 count);


private:
	int32 currentScore = 0;

	class UMainWidget* mainUI;
};
