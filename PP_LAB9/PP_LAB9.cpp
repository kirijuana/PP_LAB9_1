#include "pch.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <ctime>

	using namespace std;
	int mas[16] = {};

	int main()
	{
		setlocale(LC_ALL, "Russian");
		setlocale(LC_ALL, "rus");

		MPI_Init(0, 0); //инициализация MPI
		int rank, size; //узнаем ранг каждого процесса и их общее число
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &size);

		srand(time(NULL) * rank);
		int q = 2, w = 3;
			int i, proizv = 1;
			
			if (rank != 0)
			{
				int p = (rank - 1) * 8;
				for (int i = (rank - 1) * 8; i  < p + 8; i++)
				{
					mas[i] = 1 + rand() % 16; // 0 ... 15
					
				}
				for (int i = (rank - 1) * 8; i < p + 8; i++)
				{
					fprintf(stdout, "%d ", mas[i]);
				}
			}

			if (rank != 0)
			{
				int i, p = (rank - 1) * 8;
		       
				cout << "Chisla kratnie " << q << " i " << w << ":\n";
				for (i = p; i < p + 8; i++)
				{
					if ((mas[i] % q) == 0 && (mas[i] % w) == 0)
					{
						cout << mas[i] << "\n";
						proizv = proizv * mas[i];
					}
				}
			}
			if (rank != 0) MPI_Send(&proizv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			//нулевой процесс принимает все сообщения и выводит общую сумму
			if (rank == 0)
			{
				int buf; //для приема
				MPI_Status status;
				printf("\nProizvedenit nulevogo processa = %d", proizv);
				for (i = 0; i < size - 1; i++)
				{
					MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE,
						MPI_ANY_TAG, MPI_COMM_WORLD, &status);
					proizv = proizv * buf;
					printf("\nPolucheno proizvedenie = %d, obshee proizvedenie = %d", buf,
						proizv);
				}
				printf("\nResult = %d", proizv);
			}
			
			MPI_Finalize(); 
			return 1;
		}

