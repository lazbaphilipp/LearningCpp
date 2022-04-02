#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <string>


using namespace std;

namespace IL { // InterLesson
	int getIntNumber(int& num);
}

namespace l6{
	bool buildIntArray(int*& ptrArr, int size);
	bool buildIntMatrix(int**& ptrArr, size_t m, size_t n);

	bool populateIntArrayPowOf2(int* Arr, int size);
	bool populateIntArrayRand(int* Arr, int size);
	// я определённо не жалею, что пошел на этот курс, хихик. Возможно никогда бы и не узнал, что так можно где-то кроме матлаба.
	typedef bool(*populateArrayFun)(int*, int);

	bool populateIntMatrixByFunc(int**& Matrix, int m, int n, populateArrayFun fillArr);

	bool freeIntArray(int*& Array);
	bool freeIntMatrix(int**& Matrix, int m);

	bool printArray(int* array, int size);
	bool printMatrix(int** Matrix, int m, int n);
}


int main() {
	std::srand(std::time(nullptr));
	int tNum;
	Lesson6Start:		
	// по ряду соображений я решил использовать такой метод, однако 
	// позже понял, что мог бы без проблем использовать рекурсивную функцию или вызов функции в цикле
		system("cls");
		cout << "Enter Task Number (1-5) or 0 to exit" << endl;
		while ( (IL::getIntNumber(tNum) > 5) || (tNum) < 0) {
			system("cls");
			cout << "Error. Please enter Task Number (1-5) or 0 to exit!" << endl;
		}

		switch (tNum) {
			case 0: {
				exit(0);
			}
			// Выделить в памяти динамический одномерный массив типа int. Размер массива запросить у пользователя.
			// Инициализировать его числами степенями двойки: 1, 2, 4, 8, 16, 32, 64, 128 ...
			// Вывести массив на экран. Не забыть освободить память. =) Разбить программу на функции.
			case 1: {
				int* t1;
				int size;
				cout << "Enter array size: ";
				IL::getIntNumber(size);
				if ( !(l6::buildIntArray(t1,size) && l6::populateIntArrayPowOf2(t1, size) && l6::printArray(t1,size)) && l6::freeIntArray(t1) ) {
					cout << endl << "Something went wrong, try again" << endl;
				}
			}
			system("pause");
			goto Lesson6Start;

			// Динамически выделить матрицу 4х4 типа int. Инициализировать ее псевдослучайными числами через функцию rand.
			// Вывести на экран. Разбейте вашу программу на функции которые вызываются из main.
			case 2: {
				int** t2;
				int m, n;
				cout << "Enter matrix sizes. Rows first, columns second." << endl;
				IL::getIntNumber(m);
				IL::getIntNumber(n);
				cout << endl;
				if( !(l6::buildIntMatrix(t2,m,n) &&
					l6::populateIntMatrixByFunc(t2,m,n,l6::populateIntArrayRand) &&
					l6::printMatrix(t2,m,n) &&
					l6::freeIntMatrix(t2,m)) ) 
				{
					cout << endl << "Something went wrong, try again" << endl;
				}
			}
			system("pause");
			goto Lesson6Start;

			// Написать программу, которая создаст два текстовых файла (*.txt), примерно по 50-100 символов в каждом
			// (особого значения не имеет с каким именно содержимым). Имена файлов запросить у польлзователя.
			case 3: {
				string t31, t32;
				cout << "Enter file1 and file2 names:" << endl;
				cin >> t31;
				cin >> t32;

				ofstream fout1(t31 + ".txt");
				ofstream fout2(t32 + ".txt");
				for (int i = 0; i < 50; i++) {
					fout1 << std::rand() % 100 << " ";
					fout2 << std::rand() % 100 << " ";
				}
				fout1.close();
				fout2.close();
			}
			system("pause");
			goto Lesson6Start;

			//* Написать функцию, «склеивающую» эти файлы в третий текстовый файл (имя файлов спросить у пользователя).
			case 4: {
				string t31, t32;
				cout << "Enter file1 and file2 names:" << endl;
				cin >> t31;
				cin >> t32;
				int t33;
				ofstream fout(t31 + ".txt", ios_base::app);
				ifstream fin(t32 + ".txt");
				if (fin.is_open()) {
					for (int i = 0; i < 50; i++) {
						fin >> t33;
						fout << t33 << " ";
					}
				}
				fout.close();
				fin.close();
			}
			system("pause");
			goto Lesson6Start;

			// * Написать программу, которая проверяет присутствует ли указанное пользователем при запуске программы слово в
			// указанном пользователем файле (для простоты работаем только с латиницей).
			// Используем функцию find которая есть в строках std::string.
			case 5: {
				string t51,t52;
				cout << "Enter file name: ";
				cin >> t51;
				cout << "Enter string to find: ";
				cin >> t52;
				ifstream fin(t51 + ".txt");
				if (fin.is_open()) // Если файл был успешно открыт
				{
					string buf;
					while (!fin.eof()) // Пока не конец файла
					{
						getline(fin, buf); // Читаем из файла строку
						if (buf.find(t52) != string::npos) // строка была найдена?
						{
							cout << "Yes we found " << t52 << endl;
						}
						else
						{
							cout << "We can not find " << t52 << endl;
						}
					}
					fin.close(); // Закрываем файл
				}
			}
			system("pause");
			goto Lesson6Start;

			// На всякий случай
			default: {
				cout << "Lol How?" << endl;
				system("pause");
				goto Lesson6Start;
			}
		}

	return 0;
}


namespace IL { // InterLesson
	/**
	 * \brief Предлагает пользователю ввести число до тех пор, пока он его не введёт.
	 *
	 * \return
	 */
	int getIntNumber(int& num)
	{
		while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
		{
			cin >> num;
			if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
			{
				system("cls");
				cout << "Error. Please enter an integer number!" << endl;
				cin.clear(); // то возвращаем cin в 'обычный' режим работы
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
			}
			else // если всё хорошо, то возвращаем num
			{
				return num;
			}
		}
	}
}

namespace l6 {
	/**
	 * @brief builds 1-dim array
	 *
	 * @param ptrArr - pointer, that will take a newmade array
	 * \param size - size of new array
	 * \return true if OK and false if not. Pointer will be null if not ok.
	 */
	bool buildIntArray(int*& ptrArr, int size) {
		if (size > 0) {
			ptrArr = new (std::nothrow) int[size];
			if (ptrArr != nullptr) return true;
		}
		std::cout << "Unsuccesfull array allocation" << std::endl;
		return false;
	}

	/**
	 * @brief builds m*n matrix of integers
	 *
	 * @param ptrArr - pointer to get matrix
	 * @param n - number of columns
	 * @param m - number of rows
	 * @return true if OK and false if not. Pointer will be null if not ok.
	 */
	bool buildIntMatrix(int**& ptrArr, size_t m, size_t n) {
		if (n > 0 && m > 0) {
			ptrArr = new (std::nothrow) int* [m];
			if (ptrArr != nullptr) {
				for (int i = 0; i < m; i++) {
					if (!buildIntArray(ptrArr[i], n)) {
						return false;
					}
				}
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief fills array with numbers of power
	 * of 2 like 1, 2, 4, 8, etc
	 * \param Arr
	 * \param size
	 * \return true if ok, false if there is some problem (it will say you what)
	 */
	bool populateIntArrayPowOf2(int* Arr, int size) {
		if (Arr != nullptr) {
			Arr[0] = 1;
			for (int i = 1; i < size; i++) {
				Arr[i] = Arr[i - 1] * 2;
			}
			return true;
		}
		cout << "Array is Imaginary!!!" << endl;
		return false;
	}

	/**
	 * @brief fills array with pseudorandom integer numbers from 0 to 100 by the seed of time.
	 *
	 * \param Arr
	 * \param size
	 * \return true if ok, false if there is some problem (it will say you what)
	 */
	bool populateIntArrayRand(int* Arr, int size) {
		if (size > 0) {
			if (Arr != nullptr) {
				for (int i = 0; i < size; i++) {
					Arr[i] = std::rand() % 100;
				}
				return true;
			}
			cout << "Array is Imaginary!!!" << endl;
			return false;
		}
		cout << "I see, size is negative, I say, that I will not do anything." << endl;
		return false;
	}


	/**
	 * @brief fills matrix with numbers using function sent.
	 *
	 * \param Matrix
	 * @param n - number of columns
	 * @param m - number of rows
	 * \param fillFun - function, that will fill each row by it's special cool inner algorith.
	 * \return true if ok, false if there is some problem (it will say you what)
	 */
	bool populateIntMatrixByFunc(int**& Matrix, int m, int n, populateArrayFun fillFun) {
		if (m > 0 && n > 0) {
			if (Matrix != nullptr) {
				for (int i = 0; i < m; i++) {
					if (!fillFun(Matrix[i], n)) {
						return false;
					}
				}
				return true;
			}
			cout << "Matrix is not initialized, try again later." << endl;
			return false;
		}
		cout << "m or n is negative. Bad joke, xd." << endl;
		return false;
	}
	
	/**
	 * @brief clears 1-dim dynamic array.
	 *
	 * \param Array - pointer to an array
	 * @param size
	 * \return true if OK and false if not (it will sat you what).
	 */
	bool freeIntArray(int*& Array) {
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
			return true;
		}
		cout << "The array is already free or not initialized yet." << endl;
		return false;
	}

	/**
	 * @brief clears matrix of m rows
	 * 
	 * \param Matrix - pointer to the the matrix
	 * \param m - number of rows
	 * \return true if OK and false if not (it will sat you what).
	 */
	bool freeIntMatrix(int**& Matrix, int m) {
		if (m > 0) {
			if (Matrix != nullptr) {
				for (size_t i = 0; i < m; i++) {
					if (!freeIntArray(Matrix[i]) ) {
						return false;
					}
				}
				delete[] Matrix;
				Matrix = nullptr;
				return true;
			}
			cout << "The matrix is already free or not initialized yet." << endl;
			return false;
		}
		cout << "m is negative. Try something more original." << endl;
		return false;
	}

	bool printArray(int* array, int size) {
		if (size > 0) {
			if (array != nullptr) {
				for (int i = 0; i < size - 1; i++) {
					cout << array[i] << ", ";
				}
				cout << array[size - 1] << endl;
				return true;
			}
			cout << "Array is Imaginary!!!" << endl;
			return false;
		}
		cout << "I see, size is negative, I say, that I will not do anything." << endl;
		return false;

		
	}

	bool printMatrix(int** Matrix, int m, int n) {
		if (m > 0 && n > 0) {
			if (Matrix != nullptr) {
				for (size_t i = 0; i < m; i++) {
					if (!printArray(Matrix[i], n)) {
						return false;
					}
				}
				cout << endl;
				return true;
			}
			cout << "Matrix is not initialized, try again later." << endl;
			return false;
		}
		cout << "m or n is negative. Bad joke, xd." << endl;
		return false;
	}

}
