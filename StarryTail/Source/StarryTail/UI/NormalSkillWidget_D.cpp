// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalSkillWidget_D.h"
#include "Components/Image.h"

void UNormalSkillWidget_D::SetAttackCountMinus()
{
	if (skill_count_right->Brush.GetDrawType() == ESlateBrushDrawType::Image)
	{
		skill_count_right->Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
		return;
	}

	skill_count_left->Brush.DrawAs = ESlateBrushDrawType::NoDrawType;
}

void UNormalSkillWidget_D::SetAttackCountPlus()
{
	if (skill_count_left->Brush.GetDrawType() == ESlateBrushDrawType::NoDrawType)
	{
		skill_count_left->Brush.DrawAs = ESlateBrushDrawType::Image;
		return;
	}

	skill_count_right->Brush.DrawAs = ESlateBrushDrawType::Image;
}

void UNormalSkillWidget_D::SetAttackCooltime(float Ctime)
{
	Ctime_n = Ctime;
	Ctime_f = Ctime;
	GetWorld()->GetTimerManager().ClearTimer(AttackCtimeHandle);

	mat_Progress = skill_cooltime->GetDynamicMaterial();
	mat_Progress->SetScalarParameterValue("Progress", 1.0f);

	if (Ctime == 5.0f)
	{
		skill_bg->SetColorAndOpacity(FLinearColor::Red);
		GetWorld()->GetTimerManager().SetTimer(BGRedHandle, this, &UNormalSkillWidget_D::BGWhite, 2.0f, false, 2.0f);
	}
	else if (Ctime == 2.0f)
	{
		skill_bg->SetColorAndOpacity(FLinearColor::White);
	}

	GetWorld()->GetTimerManager().SetTimer(AttackCtimeHandle, this, &UNormalSkillWidget_D::AttackCtime, 0.05f, true, 0.05f);
}

void UNormalSkillWidget_D::AttackCtime()
{
	if (Ctime_f <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackCtimeHandle);
		mat_Progress->SetScalarParameterValue("Progress", 0.0f);
		return;
	}

	Ctime_f -= 0.05f;
	mat_Progress->SetScalarParameterValue("Progress", Ctime_f / Ctime_n);
}

void UNormalSkillWidget_D::BGWhite()
{
	skill_bg->SetColorAndOpacity(FLinearColor::White);
}
