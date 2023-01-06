// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBullet.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"

APlayerBullet::APlayerBullet(){

#pragma region Collision
	boxComp->SetCollisionProfileName(TEXT("BulletCollisionPreset"));
#pragma endregion
}

void APlayerBullet::BeginPlay()
{
	Super::BeginPlay();

#pragma region Collision
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerBullet::OnOverlap);

	//Enable Overlap event
	boxComp->SetGenerateOverlapEvents(true);
#pragma endregion
	
	//boss enemy bullet
	SetBulletDirection(GetActorForwardVector());

}


#pragma region Collision & Scores
void APlayerBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);

	if (enemy != nullptr) {

		//get enemy location
		FVector enemyPos = enemy->GetActorLocation();
		FRotator enemyRot = enemy->GetActorRotation();

		//explosion VFX at the enemy position

		//delete enemy
		enemy->Destroy();

#pragma region AddScore (AMyGameModeBase)
		//Add Game mode's score by 1
		AGameModeBase* gm = UGameplayStatics::GetGameMode(this);		//Game mode can be accessed from my any script. dont need to cast,etc
		//AGameModeBase* gm = GetWorld()->GetAuthGameMode();			//Same thing > useful when you didn't include UGameplayStatics
		AMyGameModeBase* myGM = Cast<AMyGameModeBase>(gm);

		myGM->AddScore(1);
#pragma region Debug
		//UE_LOG(LogTemp, Warning, TEXT("Point: %d"), myGM->GetCurrentScore());
#pragma endregion
#pragma endregion

		//delete this.bullet
		Destroy();
	}
}
#pragma endregion