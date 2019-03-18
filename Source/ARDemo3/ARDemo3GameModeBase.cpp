#include "ARDemo3GameModeBase.h"


AARDemo3GameModeBase::AARDemo3GameModeBase()
{
    DefaultPawnClass = AMyPawn::StaticClass();
}


// Called when the game starts
void AARDemo3GameModeBase::BeginPlay()
{
    Super::BeginPlay();
    ChangeMenuWidget(StartingWidgetClass);
}


// Replaces existing menu widget with new one
void AARDemo3GameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
    if(CurrentWidget != nullptr){
        CurrentWidget->RemoveFromViewport();
        CurrentWidget = nullptr;
    }
    
    if(NewWidgetClass != nullptr){
        CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
        
        if(CurrentWidget != nullptr){
            CurrentWidget->AddToViewport();
        }
    }
}
