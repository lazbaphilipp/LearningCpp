// lesson2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;



int main()
{
  cout << "Hello World!\n" << endl;
  /**
    * Task 1 
    * create and initialize variables with following data types: short int, int, long long, char, bool, float, double
    */
   
  short int  a = 1;
  int b = 3;
  long long lng = 1123333036854775507;
  char ch = 'g';
  bool d = true;
  float fl = 5242.2523532;
  double dd = 32089442380945.234257342093483498093428092;

  /**
    * Task 2
    * Create an enum with symbols for the game of tic-tac-toe.
    */
   enum class TicTacToeCEll{
     EMPTY,
     ZERO,
     CROSS
   };

  /**
    * Task 3
    * Create and initialize an array of such an enum.
    */
  TicTacToeCEll TTTfield[3][3]={};
  // for(int8_t i=0;i<3;i++) for(int8_t j=0;j<3;j++) TTTfield[i][j] = (TicTacToeCEll)0; //TicTacToeCEll::EMPTY;

  /**
    * Task 4
    * Create struct "Tic-Tac-Toe battlefield" and provide it with all necessary properties
    */
   struct TicTacToeGame{
     TicTacToeCEll TTTfield[3][3];
     char Player1[32];
     char Player2[32];
     bool Player1Sym;
     // bool Player2Sym;
     bool turn;

   }defaultTTT = {{},"Donkey Kong","Mario",true,false};

  // tests for players sym
  defaultTTT.TTTfield[1][1] = (TicTacToeCEll)(defaultTTT.Player1Sym+1);
  defaultTTT.TTTfield[0][0] = (TicTacToeCEll)(!defaultTTT.Player1Sym+1);

  /**
    * Task 5
    * Create struct containing union of int,float and char and 3 bit-flags saying which type of it is currently being used. 
    */
  struct QUV{ // quite unuversal variable
    union QUVmain{
      char ch;
      int in;
      float fl;
    }QUVMain;
    int8_t isInt:1, isFloat:1, isChar:1;
    int8_t universalFlag : 2;
  }QUVexample{'a',0,0,1,0};

  QUVexample.QUVMain.in = 5;
  QUVexample.isInt = 1;
  QUVexample.isFloat = 0;
  QUVexample.isChar = 0;
  QUVexample.universalFlag = 1;

  return 0;
}

