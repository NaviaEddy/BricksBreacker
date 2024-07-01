// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_PlayerController.h"
#include "Kismet/GamePlayStatics.h" 
#include "Camera/CameraActor.h"
#include "Paddle.h"
#include "Ball.h"
#include "TwoBall.h"
#include "ThreeBall.h"

APaddle_PlayerController::APaddle_PlayerController()
{
}

void APaddle_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	PaddleLocation = Cast<APaddle>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	FViewTargetTransitionParams Params;
	SetViewTarget(CameraActors[0], Params);
	SpawnNewBall();
}

void APaddle_PlayerController::Launch()
{
	MyBall->Launch();
}

void APaddle_PlayerController::DestroyBall()
{
	MyBall->Destroy();

	if (AllTwoBalls.Num()>0) {
		for (ATwoBall* BallTwo : AllTwoBalls)
		{
			if (BallTwo)
			{
				BallTwo->Destroy();
			}
		}
		AllTwoBalls.Empty();  // Limpiar la lista de instancias de TwoBall
	}
	
	if (AllThreeBalls.Num() > 0) {
		// Eliminar todas las instancias de ThreeBall
		for (AThreeBall* BallThree : AllThreeBalls)
		{
			if (BallThree)
			{
				BallThree->Destroy();
			}
		}
		AllThreeBalls.Empty();  // Limpiar la lista de instancias de TwoBall
	}
	

}

void APaddle_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);
	InputComponent->BindAxis("MoveHorizontal", this, &APaddle_PlayerController::MoveHorizontal);
	InputComponent->BindAction("Launch", IE_Pressed, this, &APaddle_PlayerController::Launch);
}


void APaddle_PlayerController::MoveHorizontal(float _AxisValue)
{
	auto MyPaddle = Cast<APaddle>(GetPawn());

	if (MyPaddle) 
	{
		MyPaddle->MoveHorizontal(_AxisValue);
	}
}

void APaddle_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APaddle_PlayerController::SpawnNewBall()
{
	if (!MyBall) {
		MyBall = nullptr;
	}

	FVector PLocation = PaddleLocation->GetActorLocation() + FVector(0.0f, 0.0f, 15.0f);

	if (BallObj) {
		MyBall = GetWorld()->SpawnActor<ABall>(BallObj, PLocation, FRotator::ZeroRotator, SpawnInfo0);
	}
}

void APaddle_PlayerController::SpawnTwoBall()
{
	
	FVector Location = MyBall->GetActorLocation();

	for (int i = 0; i < 2; i++)
	{
		TwoBall = GetWorld()->SpawnActor<ATwoBall>(TwoObj, Location, FRotator::ZeroRotator);
		if (TwoBall)
		{
			TwoBall->LaunchTwoBall();
			AllTwoBalls.Add(TwoBall); // Agregar la nueva instancia al contenedor
		}
	}


}

void APaddle_PlayerController::SpawnThreeBall()
{

	FVector Location = MyBall->GetActorLocation();

	for (int i = 0; i < 2; i++)
	{
		ThreeBall = GetWorld()->SpawnActor<AThreeBall>(ThreeObj, Location, FRotator::ZeroRotator);
		if (ThreeBall)
		{
			ThreeBall->LaunchThreeBall();
			AllThreeBalls.Add(ThreeBall); // Agregar la nueva instancia al contenedor
		}
	}

}




