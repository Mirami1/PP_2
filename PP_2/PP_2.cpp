// PP_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "omp.h"
#include <Windows.h>
#include "Utils.h"



double* ZiedelMethodParal(double** A, double* B, double e, int N, int countThreads) {
	double norm = 0.0;
	iterationsCount = 0;
	double* X = new double[N];

	for (int i = 0; i < N; i++)
		X[i] = 1;

	timing = omp_get_wtime();

	do {
		iterationsCount++;
		norm = 0.0;
		for (int i = 0; i < N; i++) {
			double diff = -X[i];
			double sum = 0;
#pragma omp parallel for shared(X,A,N,i) reduction(+:sum) num_threads(countThreads)
			for (int j = 0; j < N; j++)
				if (j != i)
					sum += A[i][j] * X[j];
			X[i] = (B[i] - sum) / A[i][i];
			diff += X[i];
			norm += diff * diff;
		}
	} while (sqrt(norm) >= e);

	timing = omp_get_wtime() - timing;
	writeTime(timing, countThreads);
	return X;
}



void workForResult(int numFile) {
	stringstream strNumberFile;
	strNumberFile << numFile;
	ReadFromFile(DIR.string() +"\\input2_0"+ strNumberFile.str() + ".txt");

	cout << "N = " << N << endl;
	cout << "Epsilon =  " << e << endl;

	for (int i = 0; i < 4; i++) {
		X = ZiedelMethodParal(A, B, e, N, (int)pow(2, i));
		if (i == 0)
			cout << "Time(" << pow(2, i) << "): " << 100 << "% " << endl;
		else
			cout << "Time(" << pow(2, i) << "): " <<(times[i] / times[0]) * 100 << "% " << endl;
		
		Sleep(1000);
	}
	writeInfo(X, N, iterationsCount, times, "output2__0" + to_string(numFile) + ".txt");
	delete B;
	delete X;
	for (int i = 0; i < N; i++)
		delete A[i];
	delete A;
	printf("\n");
}

int main()
{
	setlocale(0, "");
	for(int i=0;i<9;i++)
	workForResult(i);
	delete times;
}


