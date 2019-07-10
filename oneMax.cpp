#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include<string>
using namespace std;

int* dataplus(int N, int *data);
int* datarand(int from, int to, int *data);

int ExhaustiveSearch(int iteration);
int HillClimbing(int iteration);

int *data;
int *_data;

string algo, filename;
int runs, N;

int main()
{
	int iteration;
	cout << "./Search [algorithm] [#runs] [#iterations] [#bits] [filename]" << endl;
	cout << "./Search ";
	cin >> algo;
	cin >> runs;
	cin >> iteration;
	cin >> N; //bits
	cin >> filename;

	ofstream MyExcelFile;
	MyExcelFile.open("/Users/asus/Documents/CodeBlock/" + filename + ".csv");

	data = new int[N];
	_data = new int[N];

	srand(time(NULL));

	if (algo == "ES"){
		while (runs--){
			for (int i = 0; i < iteration; i++){
				MyExcelFile << runs << "," << i << "," << ExhaustiveSearch(i) << endl;
			}
		}
	}
	else{
		while (runs--){
			for (int i = 0; i <= iteration; i++){
				MyExcelFile << runs << "," << i << "," << HillClimbing(i) << endl;
			}
		}
	}

	MyExcelFile.close();

	delete[] data;
	delete[] _data;

	return 0;
}

int ExhaustiveSearch(int iteration){
	for (int i = 0; i < N; i++){
		data[i] = 0;
	}
	int MAX = 0;
	for (int i = 0; i < N; i++){
		cout << data[i];
	}
	cout << endl;

	//int count = pow(2, N) - 1;
	while (iteration--){

		dataplus(N, data);

		int oneMax = 0;
		for (int i = 0; i < N; i++){
			cout << data[i];
			oneMax += data[i];
		}

		if (MAX < oneMax)
			MAX = oneMax;
		cout << " " << oneMax;
		cout << endl;
	}

	cout << "One-Max Problem for " << N << " bits : " << MAX << endl;

	return MAX;
}

int HillClimbing(int iteration){
	for (int i = 0; i < N; i++){
		data[i] = rand() % 2;
		_data[i] = data[i];
	}


	//int MAX = 0;
	int oneMax = 0;
	for (int i = 0; i < N; i++){
		cout << data[i];
		oneMax += data[i];
	}
	cout << endl;

	int Half, _Half;

	int count = pow(2, N) - 1;
	while (iteration--){

		Half = 0;
		_Half = 0;
		oneMax = 0;
		for (int i = 0; i < N / 2; i++){
			Half += data[i];
			_Half += _data[i];
		}
		if (Half > _Half)
			datarand(0, N / 2, _data);
		else if (Half == _Half){
			for (int i = N / 2; i < N; i++){
				Half += data[i];
				_Half += _data[i];
			}

			if (Half >= _Half){

				for (int i = 0; i < N; i++){
					_data[i] = data[i];
				}
				datarand(0, N, _data);
			}
			else
			{
				for (int i = 0; i < N; i++){
					data[i] = _data[i];
				}
			}
		}
		else{
			for (int i = 0; i < N; i++){
				data[i] = _data[i];
			}
		}

		oneMax = 0;
		for (int i = 0; i < N; i++){
			cout << data[i];
			oneMax += data[i];
		}

		cout << " " << oneMax << " ";

		/*oneMax = 0;
		for (int i = 0; i < N; i++){
		cout << _data[i];
		oneMax += _data[i];
		}

		cout << " " << oneMax;*/
		cout << endl;
	}

	cout << "One-Max Problem for " << N << " bits : " << oneMax << endl;
	return oneMax;
}

int* dataplus(int N, int *data){

	for (int i = N - 1; i >= 0; i--){
		if (data[i] == 1)
			data[i] = 0;
		else{
			data[i] = 1;
			return data;
		}
	}
}

int* datarand(int from, int to, int *data){


	int pos1 = from + (rand() % (to - from));
	int pos2 = from + (rand() % (to - pos1));

	data[pos1] = rand() % 2;
	data[pos2] = rand() % 2;

	return data;
}
