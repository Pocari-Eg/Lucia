// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogTrigger.h"

#include "../../PlayerSource/PlayerInstance/IreneUIManager.h"
#include "../../PlayerSource/IreneCharacter.h"
#include"../../PlayerSource/PlayerInstance/IreneInputInstance.h"

#include "../../UI/TutorialWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

ADialogTrigger::ADialogTrigger()
{

	//초기 설정
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;

	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));


	static ConstructorHelpers::FObjectFinder<UStaticMesh>ST_MESH(TEXT("/Engine/VREditor/BasicMeshes/SM_Cube_01.SM_Cube_01"));
	if (ST_MESH.Succeeded())
	{
		Mesh->SetStaticMesh(ST_MESH.Object);
	}


	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);


	FString ScriptDataPath = TEXT("/Game/UI/Data/DataTable/STARRY_TAIL_Table_-_Script_Master.STARRY_TAIL_Table_-_Script_Master");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Script(*ScriptDataPath);
	if (DT_Script.Succeeded())
	{
		ScriptData = DT_Script.Object;
	}
}

void ADialogTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	STARRYLOG_S(Error);
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr) {
		if (DalogIndex.Num() != 0) {


			if (GetScriptData(DalogIndex.Num())[0]->Condition == 0) {
				Irene->IreneUIManager->PlayerHud->ExitPopUp();
				if (GetScriptData(DalogIndex.Num())[0]->Type == 0)
				{
					if (Irene != nullptr)
					{
						if (Irene->IreneUIManager->PlayerHud->GetDialogState() == EDialogState::e_Disable) {
							for (int i = 0; i < DalogIndex.Num(); i++)
								Irene->IreneUIManager->PlayerHud->SetDialog(GetScriptData(DalogIndex.Num()));
						}
					}
					//Irene->IreneUIManager->PlayerHud->ActionWidgetOn();
					Irene->IreneUIManager->PlayerHud->PlayDialog();
					Irene->SetIreneDialog();
					TriggerOff();
				}
				else {
					if (Irene != nullptr)
					{
						if (Irene->IreneUIManager->PlayerHud->GetDialogState() == EDialogState::e_Disable) {
							for (int i = 0; i < DalogIndex.Num(); i++)
								Irene->IreneUIManager->PlayerHud->SetPopUp(GetScriptData(DalogIndex.Num()));
							TriggerOff();
						}
					}
				}

			}
			else if (GetScriptData(DalogIndex.Num())[0]->Condition == 1)
			{
				if (GetScriptData(DalogIndex.Num())[0]->Type == 0)
				{

					if (Irene != nullptr)
					{
					

						if (Irene->IreneUIManager->PlayerHud->GetDialogState() == EDialogState::e_Disable) {
							for (int i = 0; i < DalogIndex.Num(); i++)
								Irene->IreneUIManager->PlayerHud->SetDialog(GetScriptData(DalogIndex.Num()));
						}
					}
				}
				else {

					if (Irene != nullptr)
					{
						if (Irene->IreneUIManager->PlayerHud->GetDialogState() == EDialogState::e_Disable) {
							for (int i = 0; i < DalogIndex.Num(); i++)
								Irene->IreneUIManager->PlayerHud->SetPopUp(GetScriptData(DalogIndex.Num()));
						}
					}
				}

				Irene->IreneUIManager->PlayerHud->ActionWidgetOn();

				TArray<UUserWidget*> outWidget;
				UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), outWidget, UTutorialWidget::StaticClass());
				for (auto FOR : outWidget)
				{
					auto castWidget = Cast<UTutorialWidget>(FOR);
					if (castWidget == nullptr) continue;

					castWidget->trystopPlay(EPlayTutorial::Action);
					castWidget->tryPlay(EPlayTutorial::Action);
				}
			}




		}

	}
}

void ADialogTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	STARRYLOG_S(Error);
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene != nullptr)
	{
		if (Irene->IreneUIManager->PlayerHud->GetDialogState() == EDialogState::e_Set) {
			Irene->IreneUIManager->PlayerHud->SetDialogState(EDialogState::e_Disable);
		}
		Irene->IreneUIManager->PlayerHud->ActionWidgetOff();

		TArray<UUserWidget*> outWidget;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), outWidget, UTutorialWidget::StaticClass());
		for (auto FOR : outWidget)
		{
			auto castWidget = Cast<UTutorialWidget>(FOR);
			if (castWidget == nullptr) continue;

			castWidget->trystopPlay(EPlayTutorial::Action);
		}
	}

}

void ADialogTrigger::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADialogTrigger::OnBeginOverlap);

	Trigger->OnComponentEndOverlap.AddDynamic(this, &ADialogTrigger::OnEndOverlap);
}

void ADialogTrigger::TriggerOff()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(false);
}

void ADialogTrigger::TriggerOn()
{
	//트리거 충돌을 켜기
	Trigger->SetGenerateOverlapEvents(true);
}

TArray<FScriptData*> ADialogTrigger::GetScriptData(int32 num)
{
	
	TArray<FScriptData*> NewData;
	for (int i = 0; i < num; i++)
	{
		NewData.Add(ScriptData->FindRow<FScriptData>(FName(DalogIndex[i]), FString("")));
	}
	return NewData;
}


