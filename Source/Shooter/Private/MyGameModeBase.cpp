// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MainWidget.h"

void AMyGameModeBase::BeginPlay()
{
	mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);

	if (mainUI != nullptr) {
		
		//draw generated widget on viewport
		mainUI->AddToViewport();

		//print current score on the widget's uICurrentScore textblock 
		mainUI->PrintCurrentScore();
	}
}

void AMyGameModeBase::AddScore(int32 count)
{
	currentScore += count;
	
	if (mainUI != nullptr) {
		//print current score on the widget's uICurrentScore textblock 
		mainUI->PrintCurrentScore();
	}
}

