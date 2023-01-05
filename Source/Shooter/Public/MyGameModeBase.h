// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"


UCLASS()
class SHOOTER_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	
#pragma region Score UI
	UPROPERTY(EditAnywhere, Category=DefaultSettings)
	TSubclassOf<class UMainWidget> mainWidget;
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetCurrentScore() {return currentScore;}
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE int32 GetHighScore() {return highScore;}

	void AddScore(int32 count);
#pragma endregion

#pragma region Menu UI
	void ShowMenu();
	
	UPROPERTY(EditAnywhere, Category=DefaultSettings)
	TSubclassOf<class UMenuWidget> menuWidget;
#pragma endregion

//Explosion Ultimate
TArray<class AEnemy*> enemyArray;

int32 currentScore = 0;

bool canSpawnEnemy;

private:
#pragma region Score UI
	int32 highScore = 0;

	class UMainWidget* mainUI;
#pragma endregion

#pragma region Menu UI
	class UMenuWidget* menuUI;
#pragma endregion

#pragma region Load High Score
	//absolute path; not recommended because creates a new folder in other ppls folder
	//FString filePath = FString("D:/01_UnrealEngine_Shooting/Content/SaveScores/HighScore.txt");
	//relative path
	FString filePath2 = FString("../../../Content/SaveScores/HighScore.txt");
#pragma endregion


};
