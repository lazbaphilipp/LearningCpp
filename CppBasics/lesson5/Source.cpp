#include <cstdlib>
#include <iostream>
#include <ctime>
///////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
using namespace std;

/**
 * @brief Написать функцию которая выводит массив double чисел на экран. А У МЕНЯ БУДЕТ ИНТ. ЯСКОЗАЛ.
 * Параметры функции это сам массив и его размер. Вызвать эту функцию из main.
 * @param array
 * @param size
 */
void printArray(int* array, int size) {
	for (int i = 0; i < size-1;i++) {
		cout << array[i]<<", ";
	}
	cout << array[size-1] << endl;
}

/**
 * @brief Задать целочисленный массив, состоящий из элементов 0 и 1. Например: [ 1, 1, 0, 0, 1, 0, 1, 1, 0, 0 ]. 
 * Написать функцию, заменяющую в принятом массиве 0 на 1, 1 на 0. Выводить на экран массив до изменений и после.
 * 
 * @param array
 * @param size
 */
void invertArray(int* array, int size) {
	cout << "How it was: ";
	printArray(array, size);

	cout << "What it is now: ";
	for (int i = 0; i < size-1; i++) {
		array[i] = !array[i]; // as ! is logical
		cout << array[i] << ", "; // this is faster, believe me, this is truly the reason
	}
	cout << array[size - 1];

	cout << endl << "You become responsible, forever, for what you have tamed." << endl;
}

// supportive
void populateArray01(int* array, int size) {
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	for (int i = 0; i < size; i++) {
		array[i] = std::rand() % 2;
	}
}

/**
 * @brief Задать пустой целочисленный массив размером 8. 
 * Написать функцию, которая с помощью цикла заполнит его значениями 1 4 7 10 13 16 19 22. 
 * Вывести массив на экран.
 * 
 * \param array
 * \param size
 */
void populateArray1p3pEtc(int* array, int size) {
	for (int i = 0; i < size;i++) {
		array[i] = 1 + 3 * i;
	}
	printArray(array, size);
}


//Task 4
#define TASK4_ARR_MAX_SIZE 16
int Task4Buf[TASK4_ARR_MAX_SIZE] = {};

void populateArrayMod10(int* array, int size = TASK4_ARR_MAX_SIZE) {
	std::srand(std::time(nullptr)); // use current time as seed for random generator
	for (int i = 0; i < size; i++) {
		array[i] = std::rand() % 10;
	}
}

/**
 * @brief Написать функцию, которой на вход подаётся одномерный массив и число n 
 * (может быть положительным, или отрицательным), при этом метод должен циклически 
 * сместить все элементы массива на n позиций.
 * 
 * \param array
 * \param shift
 * \param size
 */
void shiftArray(int* array, int shift, int size = TASK4_ARR_MAX_SIZE){
	int realshift = shift%size;
	int poshift = abs(realshift);
	int k = sizeof(int);
	if (realshift) {
		if (realshift > 0) {
			memcpy(Task4Buf, &array[size - poshift], k*poshift);
			memcpy(&Task4Buf[shift], array, k*(size-poshift));
			memcpy(array, Task4Buf, k*size);
		}
		else {
			memcpy(Task4Buf, &array[poshift], k*(size-poshift));
			memcpy(&Task4Buf[size- poshift],array, k*poshift);
			memcpy(array, Task4Buf, k*size);			
		}
	}
}
// сложность метода - 2N
// Вот умел бы я писать динамическую память я бы просто переносил "хвост" в нужное место, выделяя там память, а потом очищая старое место.
// Тогда сложность была бы N (наверно)


// Task 5
bool checkBalance(int* array, int size) {
	int counter1 = array[0], counter2=0;
	for (int i = 1; i < size; i++) {
		counter2 += array[i];
	}
	for (int i = 1; i < size; i++) {
		if (counter1 == counter2) {
			return true;
		}
		counter1 += array[i];
		counter2 -= array[i];
	}
	return false;
}
// сложность метода = N + 2*(N-1), где под сложностью я имею в виду только количество операций сложения/вычитания, не учитывая затраты на сравнение



int main() {
	// Task 1
	cout << "Task 1" << endl;
	int task1[10] = {};
	printArray(task1, sizeof(task1) / sizeof(int));
	
	// Task 2
	cout << endl << "Task 2" << endl;
	int task2[10] = {};
	populateArray01(task2, sizeof(task2) / sizeof(int));
	invertArray(task2, sizeof(task2) / sizeof(int));

	// Task 3
	cout << endl << "Task 3" << endl;
	int task3[8] = {};
	populateArray1p3pEtc(task3, sizeof(task3) / sizeof(int));

	// Task 4
	cout << endl << "Task 4" << endl;
	int task4[TASK4_ARR_MAX_SIZE] = {};
	populateArrayMod10(task4);
	int shift;
	for (int i = 0; i < 2; i++) {
		cout << endl;
		cout << "Array: ";
		printArray(task4, sizeof(task4) / sizeof(int));
		cout << "Enter shift: ";
		cin >> shift;
		shiftArray(task4, shift);
		cout << "After  shift: ";
		printArray(task4, sizeof(task4) / sizeof(int));
	}
	// Task 5
	cout << endl << "Task 5" << endl;

	int task5[8] = { 1,2,2,3,3,2,2,1 };
	printArray(task5, sizeof(task5) / sizeof(int));
	checkBalance(task5, sizeof(task5) / sizeof(int)) ? (cout << "true"<<endl) : (cout << "false" << endl);
	populateArrayMod10(task5, sizeof(task5) / sizeof(int));
	printArray(task5, sizeof(task5) / sizeof(int));
	checkBalance(task5, sizeof(task5) / sizeof(int)) ? (cout << "true" << endl) : (cout << "false" << endl);



	return 0;
}
