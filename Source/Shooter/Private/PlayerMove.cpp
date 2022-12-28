// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Bullet.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


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
	myMat = Cast<UMaterialInstanceDynamic>(meshComp->GetMaterial(0));
	FHashedMaterialParameterInfo param;
	myMat->GetVectorParameterValue(param, (FLinearColor)initColor);
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
}

// Called to bind functionality to input
void APlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

#pragma region Enhanced Input
	//cast original UInputComponent* variable to UEnhancedInputComponent*
	UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	//binding to function
	enhancedInputComponent->BindAction(iAHorizontal, ETriggerEvent::Triggered, this, &APlayerMove::Horizontal);
	enhancedInputComponent->BindAction(iAHorizontal, ETriggerEvent::Completed, this, &APlayerMove::Horizontal);
	
	enhancedInputComponent->BindAction(iAVertical, ETriggerEvent::Triggered, this, &APlayerMove::Vertical);
	enhancedInputComponent->BindAction(iAVertical, ETriggerEvent::Completed, this, &APlayerMove::Vertical);
	
	enhancedInputComponent->BindAction(iAFire, ETriggerEvent::Triggered, this, &APlayerMove::FireBullet);
#pragma endregion

#pragma region Old Input
	////Bind input functions to horizontal axis
	//PlayerInputComponent->BindAxis("Horizontal", this, &APlayerMove::Horizontal);

	////Bind input functions to vertical axis
	//PlayerInputComponent->BindAxis("Vertical", this, &APlayerMove::Vertical);

	////Bind input function to action input
	//PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerMove::FireBullet);
#pragma endregion
}

#pragma region Input Functions
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

//Action
void APlayerMove::FireBullet()
{
	//set spawn position
	FVector spawnPosition = GetActorLocation() + GetActorUpVector() * 90.0f;	//GetActorUpVector is a unit vector so its one. Vector * scalar
	
	//set spawn rotation 
	FRotator spawnRotator = FRotator(90, 0, 0);

	//set spawn parameters
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;										//When spawning, might spawn overlapping with other colliders. Gives option to override it

	//spawn bullet at the position, orientation with the set parameters
	GetWorld()->SpawnActor<ABullet>(bulletFactory, spawnPosition, spawnRotator, param);
}
#pragma endregion

#pragma region Change Enemy Material Color
void APlayerMove::ReserveHitColor(float time) {
	ChangeHitColor();
	GetWorld()->GetTimerManager().SetTimer(colorTimer, this, &APlayerMove::ChangeHitColor, time, false);
}

void APlayerMove::ChangeHitColor() {
	myMat->SetVectorParameterValue(TEXT("myColor"), FLinearColor::Red);
	//myMat->SetVectorParameterValue(TEXT("myColor"), FLinearColor(255,0,0,255));
}

void APlayerMove::ChangeOriginalColor() {

	myMat->SetVectorParameterValue(TEXT("myColor"), initColor);
}
#pragma endregion