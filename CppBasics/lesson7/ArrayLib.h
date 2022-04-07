/*****************************************************************//**
 * \file   ArrayLib.h
 * 
 * \brief  Requires some srand() in main
   for example: std::srand(std::time(nullptr));
 *
 * 
 * \author Filip
 * \date   April 2022
 *********************************************************************/
#pragma once
#ifndef ARRAYLIB_H
#define ARRAYLIB_H

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdarg>

#define SwapINT(a, b) \
b^=a;\
a^=b;\
b^=a;

namespace arrayLib {
	bool b_buildFloatArray(float*& ptrArr, int size);
	bool b_populateFloatArrayRand(float*& ptrArr, int size, int maxval);
	bool b_countNegPos(float*& ptrArr, int size);

	bool printArray(float* array, int size);
	bool printArray(int* array, int size);

	void sortIntArray(int* array, int size);

	bool freeArray(int*& Array);
}


#endif
