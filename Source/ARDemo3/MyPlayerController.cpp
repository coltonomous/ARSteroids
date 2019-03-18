#include "MyPlayerController.h"


// Called when the game starts
void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
}
