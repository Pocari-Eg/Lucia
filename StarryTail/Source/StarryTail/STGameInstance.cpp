// Fill out your copyright notice in the Description page of Project Settings.


#include "STGameInstance.h"

AIreneCharacter* USTGameInstance::GetPlayer()
{
	return Player;
}
void USTGameInstance::SetPlayer(AIreneCharacter* IreneCharacter)
{
	Player = IreneCharacter;
	if (Player == nullptr)
		STARRYLOG(Log, TEXT("Failed SetPlayer"));
	STARRYLOG(Log, TEXT("SetPlayer Complete : %s"), *Player->GetName());
}
AMonster* USTGameInstance::GetAttributeEffectMonster()
{
	return AttributeEffectMonster;
}
void USTGameInstance::SetAttributeEffectMonster(AMonster* Monster)
{
	AttributeEffectMonster = Monster;
	if (AttributeEffectMonster == nullptr)
		STARRYLOG(Log, TEXT("Failed SetAttributeEffectMonster"));
	STARRYLOG(Log, TEXT("Set AttributeEffect Monster Complete : %s"), *AttributeEffectMonster->GetName());
}
void USTGameInstance::ResetAttributeEffectMonster()
{
	AttributeEffectMonster = nullptr;
}