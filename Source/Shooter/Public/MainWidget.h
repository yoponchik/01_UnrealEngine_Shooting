// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Settings|Score", meta = (BindWidget));
	class UTextBlock* uICurrentScore;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Settings|Score", meta = (BindWidget));
	class UTextBlock* uIHighScore;
	    
	void PrintCurrentScore();

};
