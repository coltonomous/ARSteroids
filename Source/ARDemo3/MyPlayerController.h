#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

// This class defines the behavior of the player controller which is
// used for switching input between gameplay and menu navigation controls.
UCLASS()
class ARDEMO3_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
    
public:
    // Master function for setting initial state; 
    virtual void BeginPlay() override;
};
