#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <string>

#include <cstdarg>

#include <fstream>

#include "../InterLesson.h"
#include "ArrayLib.h"



#define IN_RANGE(a, b) ((a>0 && a<b)?true:false)  



#define ARRAYSIZE 12

#pragma pack(push, 1)
struct Employee {
	std::string Name;
	int id;
	double salaryBtc;
	float workExperienceYdMdD;
	int cabNum;
};
#pragma pack(pop)



int main() {
	setlocale(LC_ALL, "Russian");
	std::srand(std::time(nullptr));

	std::cout << "Создайте проект из 2х cpp файлов и заголовочного (main.cpp, mylib.cpp, mylib.h) во втором модуле \n";
	std::cout << "/mylib объявить 3 функции: для инициализации массива(типа float), печати его на экран и подсчета количества \n";
	std::cout << "отрицательных и положительных элементов.Вызывайте эти 3 - и функции из main для работы с массивом.\n" << std::endl;
	float* newfloat;
	int num;
	std::cout << "Enter Array Size: ";
	IL::getIntNumber(num);
	arrayLib::b_buildFloatArray(newfloat, num);
	arrayLib::b_populateFloatArrayRand(newfloat, num, 256);
	arrayLib::printArray(newfloat, num);
	arrayLib::b_countNegPos(newfloat, num);
	arrayLib::freeArray((int*&)newfloat);

	IL::wait();
	IL::cls();

	std::cout << "Описать макрокоманду(через директиву define), проверяющую, входит ли переданное ей число \n";
	std::cout << "(введенное с клавиатуры) в диапазон от нуля(включительно) до переданного ей второго аргумента(исключительно) \n";
	std::cout << " и возвращает true или false, вывести на экран «true» или «false».\n" << std::endl;

	int num1, num2;
	std::cout << "Введите 2 целых числа\n";
	IL::getIntNumber(num1);
	IL::getIntNumber(num2);

	std::string output = IN_RANGE(num1, num2) ? "true" : "false";
	std::cout << output<<std::endl;
	
	IL::wait();
	IL::cls();
	
	std::cout << "Задайте массив типа int.Пусть его размер задается через директиву препроцессора #define. \n";
	std::cout << "Инициализируйте его через ввод с клавиатуры.Напишите для него свою функцию сортировки(например Пузырьком). \n";
	std::cout << "Реализуйте перестановку элементов как макрокоманду SwapINT(a, b).Вызывайте ее из цикла сортировки. \n" << std::endl;

	int arr[ARRAYSIZE];
	std::cout << "Введите значения элементов массива[" << ARRAYSIZE << ']' << std::endl;
	for (int i = 0; i < ARRAYSIZE; i++) {
		std::cout << i << ": ";
		IL::getIntNumber(arr[i]);
	}

	arrayLib::sortIntArray(arr, ARRAYSIZE);

	arrayLib::printArray(arr, ARRAYSIZE);


	IL::wait();
	IL::cls();

	Employee *empa = new Employee;
	
	empa->Name = "Fil";
	empa->id = 1;
	empa->salaryBtc = 1.00500;
	empa->cabNum = 1337;
	empa->workExperienceYdMdD = 0.53421;

	std::cout << "Employee params: " << std::endl;
	std::cout << empa->Name << std::endl;
	std::cout << empa->id << std::endl;
	std::cout << empa->salaryBtc << std::endl;
	std::cout << empa->cabNum << std::endl;
	std::cout << empa->workExperienceYdMdD << std::endl;
	
	std::cout << "Instance size (bytes)" << std::endl;
	std::cout << sizeof(empa) << std::endl;

	std::ofstream fout("data.txt"); // 1. Создаем файл для записи данных
	// 2. Записываем данные
	fout << "Employee params: " << std::endl;
	fout << empa->Name << std::endl;
	fout << empa->id << std::endl;
	fout << empa->salaryBtc << std::endl;
	fout << empa->cabNum << std::endl;
	fout << empa->workExperienceYdMdD << std::endl;
	fout << "Instance size (bytes)" << std::endl;
	fout << sizeof(empa) << std::endl;
	fout.close(); // Закрываем файл


	return 0;
}

