// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Note.generated.h"

UENUM(BlueprintType, Meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ENotes : uint8 
{
	ONE = 1 UMETA(DisplayName = "One"),
	TWO = 2 UMETA(DisplayName = "Two"),
	THREE = 4 UMETA(DisplayName = "Three"),
	FOUR = 8 UMETA(DisplayName = "Four")
};
ENUM_CLASS_FLAGS(ENotes)

static FString ENotesToString(const ENotes note) {
	switch (note) {
	case ENotes::ONE:
		return "One";
	case ENotes::TWO:
		return "Two";
	case ENotes::THREE:
		return "Three";
	case ENotes::FOUR:
		return "Four";
	default:
		return "";
	}
}

template<typename T>
static FString EnumToString(const FString& enumName, const T value)
{
	UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName);
	return *(pEnum ? pEnum->GetNameStringByIndex(static_cast<uint8>(value)) : "null");
}