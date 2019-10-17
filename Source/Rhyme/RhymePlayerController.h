// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Notes.h"
#include "InputNoteBlock.h"
#include "RhymeGameMode.h"
#include "RhymePlayerController.generated.h"

UCLASS()
class ARhymePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	uint8 notesCurrentlyPressed;

	// Begin PlayerController interface
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// End PlayerController interface

	void OneNotePlayed();
	void TwoNotePlayed();
	void ThreeNotePlayed();
	void FourNotePlayed();

	void OneNoteReleased();
	void TwoNoteReleased();
	void ThreeNoteReleased();
	void FourNoteReleased();

	void OnNotePlayed(ENotes note);
	void OnNoteReleased(ENotes note);

public:
	ARhymePlayerController();

	UFUNCTION(BlueprintCallable)
	uint8 GetNotesCurrentlyPressed();

	UFUNCTION(BlueprintCallable)
	void PlayNotesPressed();

	UFUNCTION()
	void PlayNoteSound(ENotes note);

	UFUNCTION()
	void PlayWrongNoteSound();

	UPROPERTY()
	class ARhymeGameMode* GameMode;
};


