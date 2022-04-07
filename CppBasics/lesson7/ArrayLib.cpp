#include "ArrayLib.h"

namespace arrayLib {
	/**
	 * @brief builds Array of Floats
	 * 
	 * \param ptrArr pointer that will show position of created array
	 * \param size
	 * \return true if array was succesfully allocated
	 */
	bool b_buildFloatArray(float*& ptrArr, int size) {
		if (size > 0) {
			ptrArr = new (std::nothrow) float[size];
			if (ptrArr != nullptr) return true;
		}
		std::cout << "Unsuccesfull array allocation" << std::endl;
		return false;
	}
	
	/**
	 * @brief Fills float array with random floats from 0 to some integer max
	 * 
	 * \param ptrArr
	 * \param size
	 * \param maxval
	 * \return 
	 */
	bool b_populateFloatArrayRand(float*& ptrArr, int size,int maxval) {
		if (size > 0) {
			if (ptrArr != nullptr) {
				for (int i = 0; i < size; i++) {
					ptrArr[i] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / maxval));
					ptrArr[i] *= (rand() % 2) ? (-1) : 1;
				}
				return true;
			}
			std::cout << "Array is Imaginary!!!" << std::endl;
			return false;
		}
		std::cout << "I see, size is negative, I say, that I will not do anything." << std::endl;
		return false;
	}


	bool b_countNegPos(float*& ptrArr, int size) {
		int pos = 0, neg = 0;
		if (size > 0) {
			if (ptrArr != nullptr) {
				for (int i = 0; i < size; i++) {
					(ptrArr[i] > 0) ? pos++ : neg++;
				}
				std::cout << "pos count = " << pos << "\nneg count = " << neg << std::endl;
				return true;
			}
			std::cout << "Array is Imaginary!!!" << std::endl;
			return false;
		}
		std::cout << "I see, size is negative, I say, that I will not do anything." << std::endl;
		return false;
	}


	bool printArray(float* array, int size) {
		if (size > 0) {
			if (array != nullptr) {
				for (int i = 0; i < size - 1; i++) {
					std::cout << array[i] << ", ";
				}
				std::cout << array[size - 1] << std::endl;
				return true;
			}
			std::cout << "Array is Imaginary!!!" << std::endl;
			return false;
		}
		std::cout << "I see, size is negative, I say, that I will not do anything." << std::endl;
		return false;


	}

	bool printArray(int* array, int size) {
		if (size > 0) {
			if (array != nullptr) {
				for (int i = 0; i < size - 1; i++) {
					std::cout << array[i] << ", ";
				}
				std::cout << array[size - 1] << std::endl;
				return true;
			}
			std::cout << "Array is Imaginary!!!" << std::endl;
			return false;
		}
		std::cout << "I see, size is negative, I say, that I will not do anything." << std::endl;
		return false;


	}

	void sortIntArray(int* array, int size) {
		bool swapped=1;
		while (swapped) {
			swapped = 0;
			for (int i = 1; i < size; i++) {
				if (array[i] < array[i - 1]) {
					SwapINT(array[i], array[i - 1]);
					swapped = 1;
				}
			}
		}
	}

	bool freeArray(int*& Array) {
		if (Array != nullptr) {
			delete[] Array;
			Array = nullptr;
			return true;
		}
		std::cout << "The array is already free or not initialized yet." << std::endl;
		return false;
	}


}

