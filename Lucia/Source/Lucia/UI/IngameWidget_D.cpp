// Fill out your copyright notice in the Description page of Project Settings.


#include "IngameWidget_D.h"
#include "UltimateGaugeWidget_D.h"
#include "NormalSkillWidget_D.h"
#include "StanceGaugeWidget_D.h"

void UIngameWidget_D::STANCEGAUGEeCtime(float _ctime)
{
	if (BP_StanceGauge == nullptr) return;

	BP_StanceGauge->eCtime(_ctime);
}

void UIngameWidget_D::NORMALAttackCountMinus()
{
	if (BP_NormalSkill == nullptr) return;

	BP_NormalSkill->SetAttackCountMinus();
}

void UIngameWidget_D::NORMALAttackCountPlus()
{
	if (BP_NormalSkill == nullptr) return;

	BP_NormalSkill->SetAttackCountPlus();
}

void UIngameWidget_D::NORMALAttackCooltime(float _ctime)
{
	if (BP_NormalSkill == nullptr) return;

	BP_NormalSkill->SetAttackCooltime(_ctime);
}

void UIngameWidget_D::ULTIMATEsetUltimate(float _pErcent)
{
	if (BP_UltimateGauge == nullptr) return;

	if (!CanULTIMATE) return;

	CanULTIMATE = false;
	BP_UltimateGauge->SetUltimate(_pErcent);
	GetWorld()->GetTimerManager().SetTimer(ULTIMATEhandle, this, &UIngameWidget_D::CANULTIMATE, 5.0f, false, 5.0f);
}
