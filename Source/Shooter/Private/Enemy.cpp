// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerMove.h"
#include "EngineUtils.h"
#include "MyGameModeBase.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Initialize Components
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	SetRootComponent(boxComp);
	boxComp->SetBoxExtent(FVector(50)); 

#pragma region Collision
	//enable collision with query and physics mode
	boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//set object type's reply channel to 
	boxComp->SetCollisionObjectType(ECC_GameTraceChannel2);		//ECC = ECollision Channel
	
	//Set all to ignore
	boxComp->SetCollisionResponseToAllChannels(ECR_Ignore);			//ECR = ECollision Response

	//Set player and bullet to overlap
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);	//Player
	boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECR_Overlap);	//Bullet
#pragma endregion

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	meshComp->SetupAttachment(RootComponent);
#pragma endregion 
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
#pragma region Find Target
//Moved here for the Player Abilities
	for (TActorIterator<APlayerMove> it(GetWorld()); it; ++it) {
		target = *it;
	}
#pragma endregion
	
#pragma region Enemy Direction
	float randomNum = FMath::RandRange(0.1f, 1.0f);       //get random number

	if (randomNum <= followProb) {

		#pragma region Find Target: Deprecated
		//method 1 of finding player
		//AActor* target = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerMove::StaticClass());

		//method 2 of finding player
		//APlayerMove* target;
		//for (TActorIterator<APlayerMove> it(GetWorld()); it; ++it) {
		//	target = *it;
		//}
		#pragma endregion
		
		if (target != nullptr) {
			FVector targetDir = target->GetActorLocation() - GetActorLocation();
			targetDir.Normalize();					//need to normalize or else it will shoot out very far far
		
			direction = targetDir;

			//target->OnPlayerUltimateActivate.AddDynamic(this, &AEnemy::DestroyMyself);

		}
	}
	else {
		direction = GetActorForwardVector();
	}

	if(target != nullptr){
		target->OnPlayerRedirectEnemy.AddDynamic(this, &AEnemy::RedirectEnemy);
	}


#pragma endregion

#pragma region Setup Collision
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);

	//Enable Overlap event
	boxComp->SetGenerateOverlapEvents(true);
#pragma endregion

#pragma region Player Abilities: Deprecated
	//add self to array; for destroy myself
	//AMyGameModeBase* gm = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	//if(gm!=nullptr){
	//	gm->enemyArray.Add(this);
	//}
#pragma endregion
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#pragma region Enemy Move
	SetActorLocation(GetActorLocation() + direction * moveSpeed * DeltaTime);
#pragma endregion 
}

void AEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
#pragma region Destroy Myself - Game Mode Array Method
	//AMyGameModeBase* gm = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	//if (gm != nullptr) {
	//	gm->enemyArray.Remove(this);
	//}
#pragma endregion

#pragma region Destroy Myself - Game Mode Array Method
	if (target != nullptr) {
		target->OnPlayerUltimateActivate.RemoveDynamic(this, &AEnemy::DestroyMyself);
		target->OnPlayerRedirectEnemy.RemoveDynamic(this, &AEnemy::RedirectEnemy);
	}
#pragma endregion
}

#pragma region Collision
//When the enemy hits the player
void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerMove* player = Cast<APlayerMove>(OtherActor);

	if (player != nullptr) {
		//delete player
		player->Destroy();

		//Call function that brings up the menu widget
		AMyGameModeBase* gm = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());			//second method of getting the gamemode

		//Game Over
		if(gm != nullptr){
			gm->ShowMenu();
		}

		//PlayerMove ~> Enemy Change Color
		//player->ChangeHitColor(0.1f);

		//delete this.enemy
		Destroy();
	}
}
#pragma endregion

#pragma region Player Abilities

void AEnemy::RedirectEnemy(FVector newDir)
{
	direction = newDir;
}

void AEnemy::DestroyMyself()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation(), true);

	Destroy();
}
#pragma endregion

