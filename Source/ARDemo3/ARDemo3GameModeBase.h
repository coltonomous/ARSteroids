#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "MyPawn.h"
#include "ARDemo3GameModeBase.generated.h"


// This class acts as a game mode manager and defines global behaviors for the game.
UCLASS()
class ARDEMO3_API AARDemo3GameModeBase : public AGameModeBase
{
    // Required UE4 macro for unreal header code
    GENERATED_BODY()
    
public:
    AARDemo3GameModeBase();
    
    // Replaces menu widget
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
    
protected:
    
    // Master function for setting initial state; 
    virtual void BeginPlay() override;
    
    // Starting widget
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> StartingWidgetClass;
    
    UPROPERTY()
    UUserWidget* CurrentWidget;
};
