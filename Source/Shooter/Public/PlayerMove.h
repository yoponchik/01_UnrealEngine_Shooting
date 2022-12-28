// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"				//has to be above generated.h
#include "PlayerMove.generated.h"


UCLASS()
class SHOOTER_API APlayerMove : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerMove();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Declare Variables for Component Classes

	//building a component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
		class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = PlayerSettings)
		class UStaticMeshComponent* meshComp;

#pragma endregion

	//PlayerMovement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	float moveSpeed = 500;

	//Player Fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerSettings)
	TSubclassOf<class ABullet> bulletFactory;

	//Input Actions :Enhanced Inputs
	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputAction* iAHorizontal;	

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputAction* iAVertical;	

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputAction* iAFire;

	UPROPERTY(EditDefaultsOnly, Category = PlayerSettings)
	class UInputMappingContext* iMCMyMapping;
	
	//Change EnemyColor
	void ChangeHitColor(float time);
	void ChangeToOriginalColor();


private:
	//PlayerMovement
	float hori;
	float verti;
	FVector direction;

#pragma region Old Input
	//Original Horizontal function
	//UFUNCTION(BlueprintCallable)
	//void Horizontal(float value);//comment to prevent overloading

	//Original Vertical function
	//UFUNCTION(BlueprintCallable)
	//void Vertical(float value);
#pragma endregion 

	//Enhanced Horizontal function
	UFUNCTION(BlueprintCallable)
	void Horizontal(const FInputActionValue& value);			
	UFUNCTION(BlueprintCallable)
	void Vertical(const FInputActionValue& value);

	//Player Fire
	UFUNCTION(BlueprintCallable)
	void FireBullet();

	//Change Enemy Color
	FLinearColor initColor;
	FTimerHandle colorTimer;
	UMaterialInstanceDynamic* dynamicMat;
};
