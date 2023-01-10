// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MainWidget.h"
#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Boss.h"


void AMyGameModeBase::BeginPlay()
{
	mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (mainUI == nullptr) { return;}									//nullptr checker for main UI

	mainUI->AddToViewport();											//draw score ui in viewport
		
#pragma region Load High Score
	//read the file to bring the high score
	FString scoreText;

	//bool isLoadSuccess = FFileHelper::LoadFileToString(scoreText, *filePath);
	bool isLoadSuccess = FFileHelper::LoadFileToString(scoreText, *filePath2);							//Changing to a relative path

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
#pragma endregion

	mainUI->PrintCurrentScore();										//print current score on the widget's uICurrentScore textblock 


	FString testPath = FPaths::ProjectContentDir() + TEXT("SaveScore/SaveScore.txt");

	//boss
	canSpawnEnemy = true;
}


#pragma region Score UI
void AMyGameModeBase::AddScore(int32 count)
{
	//Update Current Score
	currentScore += count;

	//HighScore
	if (currentScore > highScore) {
		
		//Update High Score
		highScore = currentScore;

		//Save high score in text file, and also return true if saved
		//bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(highScore), *filePath);					//filepath2
		bool isSaved = FFileHelper::SaveStringToFile(FString::FromInt(highScore), *filePath2);
#pragma region Debug
		//UE_LOG(LogTemp, Warning, TEXT("%s"), isSaved ? TEXT("True") : TEXT("False"));
#pragma endregion

	}


	
	if (mainUI != nullptr) {
		//print current score on the widget's uICurrentScore textblock 
		mainUI->PrintCurrentScore();
	}
}
#pragma endregion 

#pragma region Menu
void AMyGameModeBase::ShowMenu()
{
	//create instance
	menuUI = CreateWidget<UMenuWidget>(GetWorld(), menuWidget);

	if(menuUI == nullptr){return;}										//nullptr checker for menu UI
	
	menuUI->AddToViewport();											//draw menu UI in viewport

	//Pause the game
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0);				// Method 1 - Make time dilation 0
	//UGameplayStatics::SetGamePaused(GetWorld(), true);				//Method 2 - call Pause Game function

	//Show Mouse Cursor
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}
#pragma endregion

