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
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btnResume;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btnRestart;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UButton* btnQuit;

};
