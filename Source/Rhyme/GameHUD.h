// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD.generated.h"



UCLASS(Blueprintable)
class RHYME_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateScore(int score);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayCorrectNoteAnimation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayWrongNoteAnimation();
};
