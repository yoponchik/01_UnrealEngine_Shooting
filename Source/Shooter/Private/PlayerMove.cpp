// Fill out your copyright notice in the Description page of Project Settings.


#pragma region Include
#include "PlayerMove.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Bullet.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShieldActor.h"
#include "Enemy.h"
#include "EngineUtils.h"
#include "MyGameModeBase.h"
#pragma endregion

// Sets default values
APlayerMove::APlayerMove()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Initialize Colliders Meshes

	//Initialize Collision Component
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	//Set the collision component as the root
	SetRootComponent(boxComp);

	//Change the size of the box collision
	boxComp->SetBoxExtent(FVector(50.0f));

	//Initialize Static Mesh Component
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));

	//Set Mesh Component as an attachment
	//meshComp->SetupAttachment(boxComp);		//Can do this or
	meshComp->SetupAttachment(RootComponent);		//better when you change the root component
	meshComp->SetRelativeLocation(FVector(0,0, -50));
	//Find cube mesh from contents folder
	//This is only convenient for making default static meshes when making blueprint
	//otherwise, if you change the location of files, you have to change the script
	ConstructorHelpers::FObjectFinder<UStaticMesh> cubeMesh(TEXT(" /Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	//if found
	if (cubeMesh.Succeeded()) {
		meshComp->SetStaticMesh(cubeMesh.Object);
	}
#pragma endregion

#pragma region Collision
	boxComp->SetCollisionProfileName(TEXT("PlayerCollisionPreset"));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

#pragma endregion

}

// Called when the game starts or when spawned
void APlayerMove::BeginPlay()
{
	Super::BeginPlay();

#pragma region Enhanced Input
	//1st BP Graph
	//Cast(change the data type) the Player Controller.
	APlayerController* playerCon = Cast<APlayerController>(GetController());		//Controller == GetController() But why is function better than variable

	//2nd BP Graph
	//if assigned properly
	if (playerCon != nullptr) {
		UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerCon->GetLocalPlayer());

		//3rd BP Graph
		if (subsystem != nullptr) {
			subsystem->AddMappingContext(iMCMyMapping, 0);
		}
	}
#pragma endregion

#pragma region Change Enemy Material Color
	//save current material color vector
	UMaterialInterface* iMat = meshComp->GetMaterial(0);
	FHashedMaterialParameterInfo param = FHashedMaterialParameterInfo(TEXT("myColor"));

	//Assign vector parameter from the Material interface to initColor
	iMat->GetVectorParameterValue(param, initColor);

#pragma region Debug
	//UE_LOG(LogTemp, Warning, TEXT("R: %f, G: %f, B:%f"), initColor.R, initColor.G, initColor.B);
#pragma endregion

	//Create Material Instance Dynamic object from Material instance
	dynamicMat = UMaterialInstanceDynamic:: Create(iMat, this);

	//set dynamic Material in the mesh component
	if (dynamicMat != nullptr) {
		meshComp->SetMaterial(0, dynamicMat);
	}
#pragma endregion

}


// Called every frame
void APlayerMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	#pragma region PlayerMovement
	//P = P0 + vt
	direction.Normalize();
	FVector dir = GetActorLocation() + direction * moveSpeed * DeltaTime;
	SetActorLocation(dir,true);
	#pragma endregion
	
	#pragma region Spin
	//SpinPlayer();
	#pragma endregion

}


// Called to bind functionality to input
void APlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	#pragma region Old Input
	////Bind input functions to horizontal axis
	//PlayerInputComponent->BindAxis("Horizontal", this, &APlayerMove::Horizontal);

	////Bind input functions to vertical axis
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerMove::Vertical);

	////Bind input function to action input
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerMove::FireBullet);
	#pragma endregion

	#pragma region Enhanced Input: Movement & Fire
	//cast original UInputComponent* variable to UEnhancedInputComponent*
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//binding to function
	enhancedInputComponent->BindAction(iAHorizontal, ETriggerEvent::Triggered, this, &APlayerMove::Horizontal);
	enhancedInputComponent->BindAction(iAHorizontal, ETriggerEvent::Completed, this, &APlayerMove::Horizontal);
	
	enhancedInputComponent->BindAction(iAVertical, ETriggerEvent::Triggered, this, &APlayerMove::Vertical);
	enhancedInputComponent->BindAction(iAVertical, ETriggerEvent::Completed, this, &APlayerMove::Vertical);
	
	enhancedInputComponent->BindAction(iAFire, ETriggerEvent::Triggered, this, &APlayerMove::FireBullet);
	#pragma endregion

	#pragma region Enhanced Input: Boost
	enhancedInputComponent->BindAction(iABoost, ETriggerEvent::Triggered, this, &APlayerMove::Boost);
	enhancedInputComponent->BindAction(iABoost, ETriggerEvent::Completed, this, &APlayerMove::UnBoost);
	#pragma endregion

	enhancedInputComponent->BindAction(iAExplosionUltimate, ETriggerEvent::Triggered, this, &APlayerMove::ExplosionUltimate);

}

#pragma region Old Input Functions
//Axis

//Original Horizontal function
//void APlayerMove::Horizontal(float value) {
//	hori = value;
//	//UE_LOG(LogTemp, Warning, TEXT("h: %.4f"), hori);
//
//	direction.Y = hori;
//}

//Original Vertical function
//void APlayerMove::Vertical(float value) {
//	verti = value;
//	//UE_LOG(LogTemp, Warning, TEXT("h: %.4f"), verti);
//	direction.Z = verti;
//}
#pragma endregion

#pragma region Old Fire Bullet
//void APlayerMove::FireBullet()
//{
//	//set spawn position
//	FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 90.0f;	//GetActorUpVector is a unit vector so its one. Vector * scalar
//
//	
//	//set spawn rotation 
//	FRotator spawnRotator = FRotator(90, 0, 0);
//
//	//set spawn parameters
//	FActorSpawnParameters param;
//	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;										//When spawning, might spawn overlapping with other colliders. Gives option to override it
//
//	//spawn bullet at the position, orientation with the set parameters
//	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotator, param);
//
//	//SFX for the bullet
//	UGameplayStatics::PlaySound2D(this, bulletSound);
//}
#pragma endregion

#pragma region Enhanced Input Functions
//Enhanced Horizontal Function
void APlayerMove::Horizontal(const FInputActionValue& value)
{
	hori = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("h: %.4f"), hori);
	direction.Y = hori;
}


void APlayerMove::Vertical(const FInputActionValue& value)
{
	verti = value.Get<float>();
	//UE_LOG(LogTemp, Warning, TEXT("h: %.4f"), hori);
	direction.Z = verti;

}

	#pragma region Fire Bullet
void APlayerMove::FireBullet()
{
	if(!canFire){return;}

	for (int32 i = 0; i < bulletCount; i++) {
		
		//total distance between the bullets
		float totalSize = (bulletCount - 1) * bulletSpacing;

		float baseY = totalSize * -0.5f;

		FVector offset = FVector(0, baseY + 150 * i, 0);

		//set spawn position
		FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 90.0f;	//GetActorUpVector is a unit vector so its one. Vector * scalar

		spawnPosition += offset;

		FRotator spawnRotator = FRotator(90, 0, 0);

		//set spawn parameters
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;										//When spawning, might spawn overlapping with other colliders. Gives option to override it

		//spawn bullet at the position, orientation with the set parameters
		ABullet* bullet = GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotator, param);
		


		float midAngle = (bulletCount - 1) * bulletAngle * -0.5f;

		FRotator rotMidAngle = FRotator(0, midAngle + bulletAngle * i, 0);
		if(bullet != nullptr)
		{
			bullet-> AddActorLocalRotation(rotMidAngle);
		}


	}
	//SFX for the bullet
	UGameplayStatics::PlaySound2D(this, bulletSound);
}
#pragma endregion

	#pragma region Boost
void APlayerMove::Boost()
{
	//UE_LOG(LogTemp, Warning, TEXT("BOOST"));
	moveSpeed = boostSpeed;
}

void APlayerMove::UnBoost()
{
	//UE_LOG(LogTemp, Warning, TEXT("UNBOOST"));
	moveSpeed = regularSpeed;
}
	#pragma endregion

	#pragma region Explosion Ultimate

		#pragma region Explosion Ultimate: Method 1 - Array
//void APlayerMove::ExplosionUltimate()
//{
//	TArray<AActor*> AllEnemyActors;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), AllEnemyActors);
//	
//	for (int32 i = 0; i < AllEnemyActors.Num(); i++)
//	{
//		if(AllEnemyActors[i] != nullptr){
//			AllEnemyActors[i]->Destroy();
//		}
//	}
//}

		#pragma endregion

		#pragma region Explosion Ultimate: Method 2	- Actor Iterator
//void APlayerMove::ExplosionUltimate()
//{
//	
//	for (TActorIterator<AEnemy> enemy(GetWorld()); enemy; ++enemy) {
//		enemy->DestroyMyself();
//	}
//
//}
		#pragma endregion

		#pragma region Explosion Ultimate: Method 3 - Adding Enemy to GM array
	//uses TArray from MyGameModeBase; Enemy adds itself to that array when it's beginplay and removes itself when its endplay
//void APlayerMove::ExplosionUltimate()
//{
//	AMyGameModeBase* gm = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
//
//	if(gm != nullptr){
//		TArray<AEnemy*> enemyArrayCopy = gm->enemyArray;
//		//for(int32 i = 0; i < gm->enemyArray.Num(); i++){
//		for(int32 i = 0; i < enemyArrayCopy.Num(); i++){
//		//check if in pending kill state
//			//if(IsValid(gm->enemyArray[i])){
//			if(IsValid(enemyArrayCopy[i])){
//				enemyArrayCopy[i]->DestroyMyself();
//			}
//		}
//
//		//Reset array
//		gm->enemyArray.Empty();
//	}
//}
		#pragma endregion

		#pragma region Explosion Ultimate: Method 4 - Delegation
//void APlayerMove::ExplosionUltimate() {
//	playerUltimateActivate.Broadcast();
//}

void APlayerMove::ExplosionUltimate() {
	OnPlayerRedirectEnemy.Broadcast(this->GetActorRightVector());

}
		#pragma endregion


	#pragma endregion 
#pragma endregion

#pragma region Change  Material Color

void APlayerMove::ChangeToOriginalColor() {
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), (FVector4)initColor);
}

void APlayerMove::ChangeHitColor(float time) {
	dynamicMat->SetVectorParameterValue(TEXT("myColor"), (FVector4)FLinearColor::Red);

	GetWorld()->GetTimerManager().SetTimer(colorTimer, this, &APlayerMove::ChangeToOriginalColor, time, false);
}
#pragma endregion

#pragma region Spin
//void APlayerMove::SpinPlayer(){
//	if(shieldActor == nullptr){return;}
//	if (!(shieldActor->isAttached)) { return; }
//
//	FRotator rotAngle = FRotator(0, 0, -10);
//	AddActorLocalRotation(rotAngle);
//}
#pragma endregion