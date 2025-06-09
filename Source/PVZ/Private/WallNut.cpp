// Fill out your copyright notice in the Description page of Project Settings.


#include "WallNut.h"

AWallNut::AWallNut()
{
	PlantID = 2;
	Init();
}

void AWallNut::Dead()
{
	Destroy();
}