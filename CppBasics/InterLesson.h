#ifndef INTERLESSON_H
#define INTERLESSON_H

// В Википедии
// 
// приводятся аргументы на счёт того или иного 
// способа эксклюзивного включения файлов

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <string>


namespace IL { // InterLesson
	void wait();
	void cls();

	int getIntNumber(int& num);
}

#endif


