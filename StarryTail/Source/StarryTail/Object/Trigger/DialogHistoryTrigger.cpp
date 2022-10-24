// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogHistoryTrigger.h"
#include "../../PlayerSource/PlayerInstance/IreneUIManager.h"
#include "../../PlayerSource/IreneCharacter.h"
#include "../../PlayerSource/PlayerInstance/IreneInputInstance.h"
#include "../../UI/DialogHistoryWidget_D.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DataTable.h"

ADialogHistoryTrigger::ADialogHistoryTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	RootComponent = Trigger;

	Trigger->SetCollisionProfileName(TEXT("Trigger"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	FString ScriptDataPath = TEXT("/Game/UI/Data/DataTable/STARRY_TAIL_Table_-_Script_Master.STARRY_TAIL_Table_-_Script_Master");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_Script(*ScriptDataPath);
	if (DT_Script.Succeeded())
	{
		ScriptData = DT_Script.Object;
	}
}

void ADialogHistoryTrigger::SetDefaultObject(FString Start, FString End)
{
	Start_ = Start;
	End_ = End;
}

void ADialogHistoryTrigger::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADialogHistoryTrigger::OnBeginOverlap);

	Trigger->OnComponentEndOverlap.AddDynamic(this, &ADialogHistoryTrigger::OnEndOverlap);
}

void ADialogHistoryTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene == nullptr) return;

	Irene->IreneUIManager->PlayerHud->ActionWidgetOn();
	
	makeDialogue = CreateWidget<UDialogHistoryWidget_D>(GetWorld(), Dialogue_C);
	makeDialogue->DialogueStart(ScriptData, FName(Start_), FName(End_));
	makeDialogue->Owner = this;
	makeDialogue->AddToViewport();
}

void ADialogHistoryTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Irene = Cast<AIreneCharacter>(OtherActor);
	if (Irene == nullptr) return;

	Irene->IreneUIManager->PlayerHud->ActionWidgetOff();

	if (makeDialogue == nullptr) return;
	
	makeDialogue->RemoveFromParent();
	makeDialogue->RemoveFromViewport();
}

