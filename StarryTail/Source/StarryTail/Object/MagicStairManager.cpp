// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicStairManager.h"
#include "Materials/MaterialInterface.h"
// Sets default values
AMagicStairManager::AMagicStairManager()
{
	//초기 설정
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AMagicStairManager::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
	NewMaterial.SetNum(StairArray.Num());


	for (int i = 0; i < StairArray.Num(); i++)
	{
		auto StairMesh = Cast<UStaticMeshComponent>(StairArray[i]->GetRootComponent());
		if (StairMesh != nullptr) {

			NewMaterial[i]=UMaterialInstanceDynamic::Create(StairMesh->GetMaterial(0), NULL);
			StairMesh->SetMaterial(0, NewMaterial[i]);
		}
		NewMaterial[i]->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.0f);
	}
	FirstTrigger->OnTickControl.AddUObject(this, &AMagicStairManager::MagicStairControl);
	SecondTrigger->OnTickControl.AddUObject(this, &AMagicStairManager::MagicStairControl);
}


// Called every frame
void AMagicStairManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (int i = 0; i < StairArray.Num(); i++)
	{
		float distance = StairArray[i]->GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		float Opacity;
		if (distance <= 280.0f)Opacity = 0.6f;
		else if (distance <= 320.0f)Opacity = 0.5f;
		else if (distance <= 370.0f)Opacity = 0.4f;
		else if (distance <= 420.0f)Opacity = 0.3f;
		else if (distance <= 450.0f)Opacity = 0.2f;
		else if (distance <= 480.0f)Opacity = 0.1f;
		else Opacity = 0.0f;

		NewMaterial[i]->SetScalarParameterValue(TEXT("Transparency_Amount"), Opacity);	
		
	}
}

void AMagicStairManager::MagicStairControl()
{
	if (IsActorTickEnabled() == false) {
		STARRYLOG(Error, TEXT("Tick Start"));
		SetActorTickEnabled(true);
	}
	else {
		STARRYLOG(Error, TEXT("Tick Pause"));
		SetActorTickEnabled(false);
		for (int i = 0; i < StairArray.Num(); i++)
		{
			NewMaterial[i]->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.0f);

		}
	}
}

