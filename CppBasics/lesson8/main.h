#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <ctime>
#include <string>

#include <fstream>

#include "../InterLesson.h"


#define V1

enum class TTT_Cell {
	CROSS = 'X',
	ZERO = '0',
	EMPTY = '_'
};


enum class TTT_Progress {
	IN_PROGRESS,
	PLAYER1_WON,
	PLAYER2_WON,
	DRAW
};


#pragma pack(push, 1)
struct TTT_Game {
	TTT_Cell** TTT_Field{ nullptr };
	int field_size{ 3U };
	int win_len{ 3U };
	bool GType{ 0U }; // 0 for AI 1 for 2 Players

	std::string P1_Name;
	std::string P2_Name;

	TTT_Cell P1{ TTT_Cell::EMPTY }, P2{ TTT_Cell::EMPTY }; // Player Symbol;

	bool P1_turn{ 0U };
	bool turn{ 0U };

	TTT_Progress Progress{ TTT_Progress::IN_PROGRESS };

	int P1_WINS{ 0 }, P2_WINS{ 0 }, DRAWS{ 0 };
	bool restarted{ 0 };
};
#pragma pack(pop)

struct TTT_Coord {
	int x{ 0U };
	int y{ 0U };
};


bool createField(TTT_Cell**& field, int size_x, int size_y);
bool deleteField(TTT_Cell** field, int size_x, int size_y);
bool initField(TTT_Cell** field, int size_x, int size_y);
bool printField(TTT_Cell** field, int size_x, int size_y);

void initGame(TTT_Game& game);
bool selectTurn();
void printGame(TTT_Game& game);

TTT_Coord getHumanCoord(TTT_Game& game);
bool getAICoord(TTT_Game& game);
TTT_Progress checkField(TTT_Game& game);
void nameWinner(TTT_Game& game);

bool restartGame();

void saveGameResults(TTT_Game& game);
bool printGame2File(TTT_Game& game);

#if defined(V2)
bool getAICoord_V2(TTT_Game& game);
#elif defined(V3)
bool getAICoord_V3(TTT_Game& game);
#else // V1 
bool getAICoord_V1(TTT_Game& game);
#endif

#endif
