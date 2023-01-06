// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBullet.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameModeBase.h"
#include "PlayerMove.h"


AEnemyBullet::AEnemyBullet(){
	boxComp->SetCollisionProfileName(TEXT("EnemyPreset"));
}

void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnOverlap);
}

void AEnemyBullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	APlayerMove* player = Cast<APlayerMove>(OtherActor);

	if (player != nullptr) {
		//delete player
		player->Destroy();

		//Call function that brings up the menu widget
		AMyGameModeBase* gm = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());			//second method of getting the gamemode

		if (gm != nullptr) {
			gm->ShowMenu();

		}
	}
}
