// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MainWidget.h"
#include "MenuWidget.h"


void AMyGameModeBase::BeginPlay()
{
	mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (mainUI != nullptr) {
		
		//draw generated widget on viewport
		mainUI->AddToViewport();

		//read the file to bring the high score
		FString scoreText;
		bool isLoadSuccess = FFileHelper::LoadFileToString(scoreText, *filePath);

#pragma region Debug
		//if(isLoadSuccess){
		//	UE_LOG(LogTemp, Warning, TEXT("Loading Succeeded"));
		//}
		//else{
		//	UE_LOG(LogTemp, Warning, TEXT("Loading failed"));
		//}
		////Same
		//UE_LOG(LogTemp, Warning, TEXT("%s"), isLoadSuccess ? TEXT("Success" : TEXT("Failed")));
#pragma endregion
	
	//Convert alphabet to integer and assign it to highScore
		highScore = FCString::Atoi(*scoreText);

	//print current score on the widget's uICurrentScore textblock 
		mainUI->PrintCurrentScore();
	}
}

void AMyGameModeBase::AddScore(int32 count)
{
	//Update Current Score
	currentScore += count;

	//HighScore
	if (currentScore > highScore) {
		
		//Update High Score
		highScore = currentScore;

		//Save high score in text file, and also return true if saved
		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(highScore), *filePath);
#pragma region Debug
		//UE_LOG(LogTemp, Warning, TEXT("%s"), isSaved ? TEXT("True") : TEXT("False"));
#pragma endregion

	}
	
	if (mainUI != nullptr) {
		//print current score on the widget's uICurrentScore textblock 
		mainUI->PrintCurrentScore();
	}
}

void AMyGameModeBase::ShowMenu()
{
	//create instance
	menuUI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

	if(menuUI != nullptr){
		menuUI->AddToViewport();
	}
}

