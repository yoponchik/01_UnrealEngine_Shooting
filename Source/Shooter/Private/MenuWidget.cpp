// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UMenuWidget::NativeConstruct()
{
	btnResume->OnClicked.AddDynamic(this, &UMenuWidget::ResumeGame);
	btnRestart->OnClicked.AddDynamic(this, &UMenuWidget::RestartGame);
	btnQuit->OnClicked.AddDynamic(this, &UMenuWidget::QuitGame);
}

void UMenuWidget::ResumeGame()
{
	//Set normal time dilation
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);				// Method 1 - Make time dilation 0
	//UGameplayStatics::SetGamePaused(GetWorld(), true);

	//hide mouse cursor
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	//delete viewport to lighten the memory
	this->RemoveFromParent();
}

void UMenuWidget::RestartGame()
{
	//Load the level
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("ShootingLevel"));

	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);

	//delete viewport to lighten the memory
	this->RemoveFromParent();
}

void UMenuWidget::QuitGame()
{
	APlayerController* playerCon = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerCon, EQuitPreference::Quit, true);
}
