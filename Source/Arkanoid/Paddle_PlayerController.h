// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Paddle_PlayerController.generated.h"
class ABall;
class ATwoBall;
class AThreeBall;
class APaddle;

/**
 * 
 */

UCLASS()
class ARKANOID_API APaddle_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APaddle_PlayerController();

	UFUNCTION()
		virtual void SetupInputComponent() override; //Funcion virtual al componente de entrada de configuraci�n

protected:

	virtual void BeginPlay() override; //Funcion al iniciar el juego

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<ABall> BallObj; //Plantilla de la clase Ball

	UPROPERTY(EditAnywhere)
		TSubclassOf<AThreeBall> ThreeObj; //Plantilla de la clase ThreeBall

	UPROPERTY(EditAnywhere)
		TSubclassOf<ATwoBall> TwoObj; //Plantilla de la clase TwoBall


	ABall* MyBall; //Puntero a Ball
	TArray<AThreeBall*> AllThreeBalls; // Contenedor para todas las instancias de TwoBall
	AThreeBall* ThreeBall = nullptr; //Puntero a TheeBall
	TArray<ATwoBall*> AllTwoBalls; // Contenedor para todas las instancias de TwoBall
	ATwoBall* TwoBall = nullptr; //Puntero a TwoBall
	APaddle* PaddleLocation; //Puntero a Paddle 
	FActorSpawnParameters SpawnInfo0; //Parametros de spawn

	void MoveHorizontal(float _AxisValue); //Funcion de movilidad del paddle

public:

	virtual void Tick(float DeltaTime) override; //Tiempo de ejecucion 

	 void SpawnNewBall(); //Funcion de creacion de ball

	 void Launch(); //Funcion de lanzamiento de ball

	 void SpawnTwoBall(); //Funcion de creacion de twoball

	 void SpawnThreeBall(); //Funcion de creacion de threeball

	 void DestroyBall(); //Funcion de destuccion de balls
};

