// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskBdAttack2.h"
#include "../Bouldelith.h"
#include "../BdAIController.h"
#include "../../../PlayerSource/IreneCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTaskBdAttack2::UBTTaskBdAttack2()
{
	NodeName = TEXT("Attack2");
}