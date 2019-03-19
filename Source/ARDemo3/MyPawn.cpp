#include "MyPawn.h"
#include "Projectile.h"


// Sets default values
AMyPawn::AMyPawn()
{
    //Create our components
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
    OurCamera->SetupAttachment(RootComponent);
    
    // Load  Session config to start  session
    MyARSessionConfig = Cast<UARSessionConfig>(StaticLoadObject(UARSessionConfig::StaticClass(), nullptr, TEXT("SessionConfig'/Game/Resources/D_SessionConfig.D_SessionConfig'")));
    
    // Load background tracks
    BackgroundTrack = Cast<USoundBase>(StaticLoadObject(USoundBase::StaticClass(), nullptr, TEXT("SoundCue'/Game/Resources/ville_seppanen-1_g_Cue.ville_seppanen-1_g_Cue'")));
    
    //Take control of the default Player
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}


// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
    Super::BeginPlay();
    
    // Stt  Session
    UARBlueprintLibrary::StartARSession(MyARSessionConfig);
    
    // Play background track
    if(BackgroundTrack != nullptr){
        UGameplayStatics::PlaySound2D(GetWorld(), BackgroundTrack);
    }
}


// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    InputComponent->BindAxis("LookUp", this, &AMyPawn::LookUp);
    InputComponent->BindAxis("RollRight", this, &AMyPawn::RollRight);
    InputComponent->BindAxis("LookRight", this, &AMyPawn::LookRight);
    InputComponent->BindAction("Fire", IE_Pressed, this, &AMyPawn::FireProjectile);
}


// Pans the camera up
void AMyPawn::LookUp(float value)
{
    FRotator currentRotation = GetActorRotation();
    FQuat QuatRotation = FQuat(FRotator(value, 0.f, 0.f));
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}


// Rotates the camera ound the forwd axis
void AMyPawn::RollRight(float value)
{
    FRotator currentRotation = GetActorRotation();
    FQuat QuatRotation = FQuat(FRotator(0.f, 0.f, value));
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}


// Pans the camera to the side
void AMyPawn::LookRight(float value)
{
    FRotator currentRotation = GetActorRotation();
    FQuat QuatRotation = FQuat(FRotator(0.f, value, 0.f));
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}


// Spawns a projectile along forward vetor
void AMyPawn::FireProjectile()
{
    FVector spawnLocation = OurCamera->GetComponentLocation();
    spawnLocation.X += 20.f;    // Hopefully mitigate camera clipping
    FRotator spawnRotation = OurCamera->GetComponentRotation();
    FActorSpawnParameters spawnInfo;
    GetWorld()->SpawnActor<AProjectile>(spawnLocation, spawnRotation, spawnInfo);
}
