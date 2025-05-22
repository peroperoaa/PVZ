// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterNode.h"

AEncounterNode::AEncounterNode()
	: Super()
{
	NodeType = ERoguelikeNodeTypes::Encounter;

}

void AEncounterNode::EnterNode_Implementation(APlayerController* PlayerController)
{
	Super::EnterNode_Implementation(PlayerController);
	
}
