// BML.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <cstdlib>
using namespace std;
int MatrixSize = 30;
int s = 2000; //Sleep time

double Outflow[50];
double Outdensity[50];
int LiczbaPomiarow = 50;
double avgcarcount = 0;
double avgroadcount = 0;
double ResultFlow[50];
double ResultDensity[50];


int main()
{
	double FinalFlow = 0;
	double probability = 15;   //w procentach
	for (int pomiary = 0; pomiary < 50; pomiary++)
	{
		
		for (int i = 0; i < LiczbaPomiarow; i++)
		{
			double flow;
			double carcount = 0;
			double roadcount = 0;
			double percentage;
			bool flaga = 0;
			double cars_movable = 0;
			double car_size = 3;
			bool finishflag = 0;
			int iterations = 50; //Liczba iteracji symulacji
			bool checkedE = false;
			bool checkedN = false;
			bool tick = false;
			//generujemy tablice
			int **Matrix = new int *[MatrixSize];
			for (int i = 0; i < MatrixSize; i++)
			{
				Matrix[i] = new int[MatrixSize];
			}
			//generujemy tablice pomocnicza
			int **Matrix2 = new int *[MatrixSize];
			for (int i = 0; i < MatrixSize; i++)
			{
				Matrix2[i] = new int[MatrixSize];
			}

			//Wypelniamy glowna tablice zerami
			for (int i = 0; i < MatrixSize; i++) {
				for (int j = 0; j < MatrixSize; j++) {
					Matrix[i][j] = 0;
				}
			}
			//Wypelniamy macierz pomocnicza zerami
			for (int i = 0; i < MatrixSize; i++) {
				for (int j = 0; j < MatrixSize; j++) {
					Matrix2[i][j] = 0;
				}
			}

			srand(time(NULL));

			//Generowanie pojazdow

			for (int i = 0; i < MatrixSize; i++) {
				for (int j = 0; j < MatrixSize; j++) {
					int y = rand() % 100 + 1; //losujemy czy dane pole bedzie puste czy nie
					if (y < probability) //Jesli w polu ma byc wygenerowany samochod
					{
						int x = rand() % 2 + 1;   //losowanie jaki pojazd zostanie przypisany
						if (x == 1) //Jesli 1 to samochod przesuwa sie w gore, jesli 2 to w prawo
						{
							if (Matrix[i][j] == 0)
							{
								Matrix[i][j] = 11;
							}
						}
						if (x == 2)  //Jesli x=2 to samochod przesuwa sie w prawo
						{
							if (Matrix[i][j] == 0)
							{
								Matrix[i][j] = 22;
							}
						}
					}
					
				}
				
			}
			for (int iterationcount = 0; iterationcount < iterations; iterationcount++)
			{
				//Wyswietlanie Samochodow
				system("cls");
				if (flaga == 0)
				{
					for (int i = 0; i < MatrixSize; i++) {
						for (int j = 0; j < MatrixSize; j++) {
							if (Matrix[i][j] == 0) roadcount++;
							//{
							//	//cout << ". "; //Puste pole
							//	if (flaga == 0) roadcount++;
							//}
							else if (Matrix[i][j] == 11) carcount++;
							//{
							//	//cout << "N "; //Samochod poruszajacy sie w gore
							//	if (flaga == 0) carcount++;
							//}
							else if (Matrix[i][j] == 22) carcount++;
							//{
							//	//cout << "E "; //Samochod poruszajacy sie w prawo
							//	if (flaga == 0) carcount++;
							//}
						}
						//cout << endl;
					}
				}
				if (flaga == 0) percentage = (carcount / (roadcount + carcount)) * 100;
				cout << "carcount: " << carcount << endl;
				cout << "roudcount: " << roadcount << endl;
				cout << "Percentage: " << percentage << "%" << endl;
				cout << "Probability: " << probability << endl;
				flaga = 1;


				//Przesuwanie pojazdow
				if (tick == false) //W tym przypadku ruszaja sie samochody idace w prawo
				{
					for (int i = 0; i < MatrixSize; i++) {
						for (int j = 0; j < MatrixSize; j++) {
							int k = j + 1;
							if (k == MatrixSize)
								k = 0;

							if (Matrix[i][j] == 22) {
								if (Matrix[i][k] == 0)
								{
									Matrix2[i][k] = 22;
									if (iterationcount >= iterations - 2) cars_movable++;
								}
								else
									Matrix2[i][j] = 22;
							}
							if (Matrix[i][j] == 11)
								Matrix2[i][j] = 11;
						}
					}
				}


				if (tick == true)  //Tutaj przesuwaja sie samochodu poruszajace sie w gore
				{
					for (int i = 0; i < MatrixSize; i++) {
						int k = i - 1;
						for (int j = 0; j < MatrixSize; j++) {

							if (k == -1)
								k = MatrixSize - 1;

							if (Matrix[i][j] == 11)
							{
								if (Matrix[k][j] == 0)
								{
									Matrix2[k][j] = 11;
									if (iterationcount >= iterations - 2) cars_movable++;
								}
								else
									Matrix2[i][j] = 11;
							}
							if (Matrix[i][j] == 22)
								Matrix2[i][j] = 22;
						}
					}
				}
				tick = !tick; //Zmieniamy rodzaj samochodow, ktore beda przesuwane w nastepnej iteracji


			//Przepisujemy macierz pomocnicza do macierzy glownej	
				for (int i = 0; i < MatrixSize; i++) {
					for (int j = 0; j < MatrixSize; j++) {
						Matrix[i][j] = Matrix2[i][j];
					}
				}


				//Zerujemy macierz pomocnicza
				for (int i = 0; i < MatrixSize; i++) {
					for (int j = 0; j < MatrixSize; j++) {
						Matrix2[i][j] = 0;
					}
				}



				//Sleep(s);
				if (iterationcount == iterations - 1)
					finishflag = 1;

				if (finishflag == 1)
				{
					double cars_size = carcount;
					double average_v = cars_movable / cars_size;
					flow = average_v * probability;
					cout << "flow: " << flow << "%" << endl;
					cout << "d: " << probability / 100 << "%" << endl;
					cout << "cars_movable: " << cars_movable << endl;
					cout << "average_v: " << average_v << endl;
					cars_movable = 0;
					finishflag = 0;
					

				}
			}
			avgcarcount += carcount;
			avgroadcount += roadcount;
			Outdensity[i] = probability;
			Outflow[i] = flow;
			FinalFlow += flow;
			//cout << endl;
			//cout << "OUTFLOW[i] =" << Outflow[i];
			//Sleep(200000);
		}


		//cout << "d: " << probability / 100 << "%" << endl;
		//for (int i = 0; i < LiczbaPomiarow; i++)
		//{
		//	cout << "flow[" << i << "] wynosi: " << Outflow[i] << endl;
		//	//FinalFlow += Outflow[i];
		//}
		FinalFlow = FinalFlow / LiczbaPomiarow;
		cout << "srednie flow dla gestosci: " << probability << " wynosi: " << FinalFlow << endl;

		avgcarcount = avgcarcount / LiczbaPomiarow;
		avgroadcount = avgroadcount / LiczbaPomiarow;
		cout << "Srednia liczba pojazdow wyniosla: " << avgcarcount << endl;
		cout << "Srednia liczba pustych drog wyniosla: " << avgroadcount << endl;
		ResultFlow[pomiary] = FinalFlow/3;
		ResultDensity[pomiary] = avgcarcount / 900;
		probability++;
		FinalFlow = 0;
		avgcarcount = 0;
		avgroadcount = 0;
	}
	for (int i = 0; i < 50; i++) {
		cout << "Gestosc[" << i+1 << "]: " << ResultDensity[i] << "    Flow: " << ResultFlow[i] << "%" << endl;
		}


		system("PAUSE");
		return 0;
	
}

