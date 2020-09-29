#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <experimental/filesystem>




using namespace std;
namespace fs = std::experimental::filesystem;


double* times = new double[4];

double e;
int N;
double** A = nullptr;
double* B = nullptr;
double* X = nullptr;

double timing = 0;
int iterationsCount = 0;


fs::path DIR = fs::current_path();



void writeTime(double time, int i) {
	times[(int)log2(i)] = time;
}

void ReadFromFile(string file_name) {
	ifstream file_in(file_name);
	string line;

	if (file_in.is_open()) {
		getline(file_in, line);
		stringstream text(line);
		text >> N >> e;

		A = new double* [N];
		B = new double[N];

		getline(file_in, line);
		text.clear();
		text.str(line);
		int i = 0;
		while (!text.eof()) {
			text >> B[i++];
		}

		for (int i = 0; i < N; i++) {
			A[i] = new double[N];

			getline(file_in, line);
			text.clear();
			text.str(line);
			int j = 0;
			while (!text.eof()) {
				text >> A[i][j++];
			}
		}


	}

	for (int i = 0; i < N; i++)
		printf("%f ", B[i]);
	

}

void writeInfo(double* X, int N, int countIterations, double* times, string OUTPUTFILE) {
	ofstream out;
	out.open(DIR.u8string() + OUTPUTFILE);
	if (out.is_open()) {
		out << countIterations << endl;
		for (int i = 0; i < N; i++) {
			out << fixed << setprecision(5) << X[i] << " ";
		}
		out << endl;
		for (int i = 0; i < 4; ++i) {
			out << setprecision(10) << times[i] << " ";
		}
	}
}

