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
	StartTrigger->OnTickControl.AddUObject(this, &AMagicStairManager::TickStart);
	EndTrigger->OnTickControl.AddUObject(this, &AMagicStairManager::TickEnd);

}


// Called every frame
void AMagicStairManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	min = 1000.0f;
	for (int i = 0; i < StairArray.Num(); i++)
	{
		float distance = StairArray[i]->GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (min > distance)min = distance;

	}
	if (min < 300.0f) {
		for (int i = 0; i < StairArray.Num(); i++)
		{
			float distance = StairArray[i]->GetDistanceTo(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			distance -= 90.0f;
			float Opacity;
			//float cos;
			float Calc = distance / min;
			
		
			if (Calc > 3.0f)
			{
				Opacity = 0.0f;
			}
			else {
							Opacity = FMath::Cos(Calc);
			Opacity = (Opacity + 0.5) * 0.65;
			}

			STARRYLOG(Warning, TEXT("stair : %d ,Distance %f , Cos %f "), i, Calc, Opacity);


			/*	if (distance / min <= 1.0f) Opacity = 0.6f;
				else if (distance / min >= 1.7f) Opacity = 0.0f;*/
				//FMath::Cos()
			NewMaterial[i]->SetScalarParameterValue(TEXT("Transparency_Amount"), Opacity);

		}
	}

	

}

void AMagicStairManager::OnStair()
{

		NewMaterial[0]->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.6f);
		NewMaterial[1]->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.4f);
		NewMaterial[2]->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.2f);
		NewMaterial[3]->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.1f);
}

void AMagicStairManager::TickStart()
{
	if (IsActorTickEnabled() == false) {
		STARRYLOG(Error, TEXT("Tick Start"));
		SetActorTickEnabled(true);
	}
}

void AMagicStairManager::TickEnd()
{
	if(IsActorTickEnabled()==true)
	{
		STARRYLOG(Error, TEXT("Tick Pause"));
		SetActorTickEnabled(false);
		for (int i = 0; i < StairArray.Num(); i++)
		{
			NewMaterial[i]->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.0f);

		}
	}

	

	StartTrigger->OnTickControl.Clear();
	EndTrigger->OnTickControl.Clear();
	Swap(StartTrigger, EndTrigger);
	StartTrigger->OnTickControl.AddUObject(this, &AMagicStairManager::TickStart);
	EndTrigger->OnTickControl.AddUObject(this, &AMagicStairManager::TickEnd);
}



