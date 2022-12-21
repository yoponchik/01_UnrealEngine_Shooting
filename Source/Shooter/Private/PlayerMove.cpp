// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerMove::APlayerMove()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

}

// Called when the game starts or when spawned
void APlayerMove::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerMove::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind input functions to horizontal axis
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerMove::Horizontal);

	//Bind input functions to vertical axis
	PlayerInputComponent->BindAxis("Vertical", this, &APlayerMove::Vertical);
}

#pragma region Input Functions

void APlayerMove::Horizontal(float value) {
	hori = value;
	UE_LOG(LogTemp, Warning, TEXT("h: %.4f"), hori);

}

void APlayerMove::Vertical(float value) {
	verti = value;
	UE_LOG(LogTemp, Warning, TEXT("h: %.4f"), verti);
}
#pragma endregion