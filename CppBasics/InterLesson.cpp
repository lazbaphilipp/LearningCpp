#include "InterLesson.h"
#include <limits>
namespace IL { // InterLesson

	/**
	* @brief Enters "Press any key to continue" in console
	*/
	void wait(){
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
    #if defined(LINUX) || defined(__linux__)
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
}