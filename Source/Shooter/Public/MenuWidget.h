// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	
	//buttons
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btnResume;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btnRestart;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btnQuit;

	virtual void NativeConstruct() override;

private:

	//Dynamic Functions
	UFUNCTION()
	void ResumeGame();
	
	UFUNCTION()
	void RestartGame();
	
	UFUNCTION()
	void QuitGame();
};
