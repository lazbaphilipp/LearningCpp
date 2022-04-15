#include "InterLesson.h"
#include <limits>
namespace IL { // InterLesson

	/**
	* @brief Enters "Press any key to continue" in console
	*/
	void wait(){
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
    #if defined(LINUX) || defined(__linux__)
        system("read");
    #else 
        #if defined(_WIN64) || defined(_WIN32)
        system("pause");
        #endif
    #endif
	
	}
	
	/**
	* @brief clears console screen
	* 
	*/
	void cls(){
    #if defined(LINUX) || defined(__linux__) || defined(VSCode)
        printf("\033c");
    #else 
        #if defined(_WIN64) || defined(_WIN32)
        system("cls");
        #endif
    #endif
	}
	

	/**
	 * \brief Предлагает пользователю ввести число до тех пор, пока он его не введёт.
	 *
	 * \return
	 */
	int getIntNumber(int& num)
	{
		while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
		{
			std::cin >> num;
			if (std::cin.fail()) // если предыдущее извлечение оказалось неудачным,
			{
				std::cout << "Error. Please enter an integer number!" << std::endl;
				std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
			}
			else // если всё хорошо, то возвращаем num
			{
				return num;
			}
		}
	}


	int getRandomNum(int min, int max) {
		const static auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		static std::mt19937_64 generator(seed);
		std::uniform_int_distribution<int> dis(min,max);
		return dis(generator);
	}


}