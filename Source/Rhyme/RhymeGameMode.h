// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameHUD.h"
#include "InputNoteBlock.h"
#include "RhymeGameMode.generated.h"

UCLASS(minimalapi)
class ARhymeGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	float tempo = 50;

	UPROPERTY(EditAnywhere)
	TArray<TWeakObjectPtr<AInputNoteBlock>> noteBlocks;

protected:
	virtual void Tick(float DeltaTime) override;

	void UpdateCurrentInputNoteBlocks(float DeltaTime);

	void AddNewNoteBlock();

public:
	ARhymeGameMode();

	UPROPERTY(BlueprintReadOnly)
	int score;

	UPROPERTY(BlueprintReadWrite, meta = (BlueprintProtected))
	UGameHUD* gameHUD;

	UFUNCTION(BlueprintCallable)
	float GetTempo();

	bool CheckInputForValidNotes(uint8 notesCurrentlyPressed);
};



