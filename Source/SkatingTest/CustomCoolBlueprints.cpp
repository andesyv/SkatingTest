// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCoolBlueprints.h"

FQuat UCustomCoolBlueprints::toQuat(const FRotator &rot)
{
    return rot.Quaternion();
}
