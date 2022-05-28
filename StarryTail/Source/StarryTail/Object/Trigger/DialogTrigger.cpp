// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogTrigger.h"

#include "../../PlayerSource/IreneUIManager.h"
#include "../../PlayerSource/IreneCharacter.h"
#include"../../PlayerSource/IreneInputInstance.h"

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
	if (DalogIndex != "") {
		if (GetScriptData()->Condition == 1)
		{
			STARRYLOG_S(Error);
			auto Irene = Cast<AIreneCharacter>(OtherActor);
			if (Irene != nullptr)
			{
				Irene->IreneInput->bActionKeyActive = true;
				Irene->IreneUIManager->PlayerHud->SetDialog(GetScriptData());
				Irene->IreneUIManager->PlayerHud->ActionWidgetOn();
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
	Irene->IreneInput->bActionKeyActive = false;
	Irene->IreneUIManager->PlayerHud->ActionWidgetOff();
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

FScriptData* ADialogTrigger::GetScriptData()
{
	return ScriptData->FindRow<FScriptData>(FName(*DalogIndex), FString(""));
}


