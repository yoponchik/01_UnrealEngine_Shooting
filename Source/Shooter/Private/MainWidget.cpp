// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"


void UMainWidget::PrintCurrentScore()
{
	AMyGameModeBase* myGM = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));

	if (myGM != nullptr) {
		//change current score (int) type to SetText 
		FText scoreText = FText::AsNumber(myGM->GetCurrentScore());

		//change uIcurrrentScore's text
		uICurrentScore->SetText(scoreText);
		
		//change high score (int) type to SetText 
		FText highScoreText = FText::AsNumber(myGM->GetHighScore());

		//change uIHighScore's text
		uIHighScore->SetText(highScoreText);
	}
}
