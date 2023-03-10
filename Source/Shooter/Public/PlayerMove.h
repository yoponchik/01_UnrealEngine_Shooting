// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"				//has to be above generated.h
#include "PlayerMove.generated.h"

//Delegate to destroy all enemies
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUltimateExplosion);

//delegate that takes in argument
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRedirect, FVector, newDir);


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

#pragma region Components
	//building a component
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerSettings | Components")
	class UBoxComponent* boxComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "PlayerSettings | Components")
	class UStaticMeshComponent* meshComp;
#pragma endregion

#pragma region PlayerMovement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings | Movement")
	float regularSpeed = 500;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings | Movement")
	float boostSpeed = 800;
#pragma endregion

#pragma region PlayerFire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings | Gun")
	TSubclassOf<class ABullet> bulletFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings | Gun")
	int32 bulletCount = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings | Gun")
	float bulletSpacing = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerSettings | Gun")
	float bulletAngle = 30;
#pragma endregion

#pragma region Input Actions : Enhanced Inputs
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings | Inputs")
	class UInputMappingContext* iMCMyMapping;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings | Inputs")
	class UInputAction* iAHorizontal;	

	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings | Inputs")
	class UInputAction* iAVertical;	

	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings | Inputs")
	class UInputAction* iAFire;
	
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings | Inputs")
	class UInputAction* iABoost;

	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings | Inputs")
	class UInputAction* iAExplosionUltimate;	

	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings | Inputs")
	class UInputAction* iARedirectUltimate;
#pragma endregion

#pragma region Change Color
	void ChangeHitColor(float time);
	void ChangeToOriginalColor();
#pragma endregion

	//SFX
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSettings | SFX")
	class USoundBase* bulletSound;

#pragma region Spin
	class AShieldActor* shieldActor;
	void SpinPlayer();
#pragma endregion

	//Trap
	bool canFire = true;

#pragma region Ultimate
	FUltimateExplosion OnPlayerUltimateActivate;

	FRedirect OnPlayerRedirectEnemy;
#pragma endregion

private:

#pragma region Old Input
	//Original Horizontal function
	//UFUNCTION(BlueprintCallable)
	//void Horizontal(float value);//comment to prevent overloading

	//Original Vertical function
	//UFUNCTION(BlueprintCallable)
	//void Vertical(float value);
#pragma endregion 

#pragma region Player Movement
	float moveSpeed = 500;

	float hori;
	float verti;
	FVector direction;
#pragma endregion

#pragma region Input Actions : Enhanced Inputs
	//Enhanced Horizontal function
	UFUNCTION(BlueprintCallable)
	void Horizontal(const FInputActionValue& value);			
	UFUNCTION(BlueprintCallable)
	void Vertical(const FInputActionValue& value);

	//Player Fire
	UFUNCTION(BlueprintCallable)
	void FireBullet();
	
	//Player Boost
	void Boost();
	void UnBoost();

	//Ultimate
	UFUNCTION(BlueprintCallable)
	void ExplosionUltimate();	
		
	UFUNCTION(BlueprintCallable)
	void RedirectUltimate();
#pragma endregion

#pragma region Change Color
	//Change Enemy Color
	FLinearColor initColor;
	FTimerHandle colorTimer;
	UMaterialInstanceDynamic* dynamicMat;
#pragma endregion

};
