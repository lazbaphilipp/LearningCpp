#include "main.h"

int main() {


	TTT_Game TGame; 
	TTT_Coord сoords;

GameStart:
	initGame(TGame);
	do {
		if (TGame.turn == TGame.P1_turn) {
			сoords = getHumanCoord(TGame);
			TGame.TTT_Field[сoords.y][сoords.x] = TGame.P1;
		}
		else {
			if (TGame.GType) {
				сoords = getHumanCoord(TGame);
				TGame.TTT_Field[сoords.y][сoords.x] = TGame.P2;
			}
			else {
				if (!getAICoord(TGame)) {
					std::cout << "Something went wrong" << std::endl;
					IL::wait();
					exit(0);
				}
				
			}

		}
		IL::cls();
		TGame.Progress = checkField(TGame);
		TGame.turn = !TGame.turn;
		printGame(TGame);
	} while (TGame.Progress == TTT_Progress::IN_PROGRESS);
	
	nameWinner(TGame);

	saveGameResults(TGame);

	deleteField(TGame.TTT_Field, TGame.field_size, TGame.field_size);

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	
	
	if (restartGame()) {
		TGame.restarted = true;
		goto GameStart;
	}


	return 0;
}






bool createField(TTT_Cell**& field, int size_x, int size_y) {
	if (size_x > 0 && size_y > 0) {
		field = new (std::nothrow) TTT_Cell * [size_y];
		if (field != nullptr) {
			for (int i = 0; i < size_x; i++) {
				field[i] = new (std::nothrow) TTT_Cell[size_x];
				if (field[i] == nullptr) {
					std::cout << "Unable to init field" << std::endl;
					return false;
				}
			}
			return true;
		}
		std::cout << "Unable to init field" << std::endl;
		return false;
	}
	std::cout << "wrong size(s)" << std::endl;
	return false;
}

bool deleteField(TTT_Cell** field, int size_x, int size_y) {
	if (size_x > 0 && size_y > 0) {
		if (field != nullptr) {
			for (int i = 0; i < size_x; i++) {
				if (field[i] == nullptr) {
					std::cout << "strange field, row is empty or not initialized. Try manual delete." << std::endl;
					return false;
				}
				delete[] field[i];
				field[i] = nullptr;
			}
			delete[] field;
			field = nullptr;
			return true;
		}
		std::cout << "Field deleted aready or not initialized yet" << std::endl;
		return false;
	}
	std::cout << "wrong size(s)" << std::endl;
	return false;
}



bool initField(TTT_Cell** field, int size_x, int size_y) {
	if (size_x > 0 && size_y > 0) {
		if (field != nullptr) {
			for (int i = 0; i < size_y; i++) {
				if (field[i] == nullptr) {
					std::cout << "empty ot wrong cell pointer" << std::endl;
					return false;
				}
				for (int j = 0; j < size_x; j++) {
					field[i][j] = TTT_Cell::EMPTY;
				}
			}
			return true;
		}
		std::cout << "empty ot wrong field pointer" << std::endl;
		return false;
	}
	std::cout << "wrong size(s)" << std::endl;
	return false;
}

bool printField(TTT_Cell** field, int size_x, int size_y) {
	if (size_x > 0 && size_y > 0) {
		if (field != nullptr) {
			std::cout << "     ";
			for (int i = 0; i < size_x; i++) {
				std::cout << i + 1 << "   ";
			} std::cout << std::endl;

			for (int i = 0; i < size_y; i++) {
				if (field[i] == nullptr) {
					std::cout << "empty ot wrong cell pointer" << std::endl;
					return false;
				}
				// start: print separator
				std::cout << "   ";// ------------- " << std::endl;
				for (int j = 0; j < size_x; j++) {
					std::cout << "----";
				}
				std::cout << "- " << std::endl;
				// end: print separator

				// start: print line
				std::cout << i+1 << "  | ";
				for (int j = 0; j < size_x; j++) {
					std::cout << (char)field[i][j] << " | ";
				}
				std::cout << std::endl;
				// end: print line
			}

			// start: print last separator
			std::cout << "   ";// ------------- " << std::endl;
			for (int j = 0; j < size_x; j++) {
				std::cout << "----";
			}
			std::cout << "- " << std::endl;
			// end: print last separator

			return true;
		}
		std::cout << "empty ot wrong field pointer" << std::endl;
		return false;
	}
	std::cout << "wrong size(s)" << std::endl;
	return false;
}


bool selectTurn() {
	std::cout << "Enter 'r' for random turn or 'm' for manual: ";
	std::string trn;
	std::cin >> trn;
	while (true) {
		if (trn == "r" || trn == "m") break;
		std::cout << "Error! Enter Valid variant\n";
		std::cin >> trn;
	}
	if (trn == "r") {
		int turn = IL::getRandomNum(0, 1000) % 2;
		return turn;
	}
	else if (trn == "m") {
		std::cout << "Enter Player1 turn (1 or 2)\n";
		int turn;
		IL::getIntNumber(turn);
		while (turn < 1 && turn > 2) {
			std::cout << "Enter Player1 turn !!!(1 or 2)!!!\n";
			IL::getIntNumber(turn);
		}
		return turn % 2;
	}
	else {
		std::cout << "WTF?!\n";
		IL::wait();
		exit(0);
	}
}

void printGame(TTT_Game& game) {
	printField(game.TTT_Field, game.field_size, game.field_size);
	std::cout << game.P1_Name << " sign: " << (char)game.P1 << "\n" << game.P2_Name << " sign: " << (char)game.P2 << std::endl;

	if (game.restarted) {
		std::cout << std::endl;
		std::cout << game.P1_Name << " wins: " << game.P1_WINS << std::endl;
		std::cout << game.P2_Name << " wins: " << game.P2_WINS << std::endl;
		std::cout << "Draws: " << game.DRAWS << std::endl;
	}

	std::cout << "\nturn: ";
	if (game.turn == game.P1_turn) {
		std::cout << game.P1_Name << std::endl;
	}
	else {
		std::cout << game.P2_Name << std::endl;
	}
	



}

void initGame(TTT_Game& game) {
	if (!game.restarted) {
		std::cout << "Enter Game type. 0 for AI game, 1 for two-player mode\n";
		int gametype;
		IL::getIntNumber(gametype);
		while (gametype < 0 && gametype > 1) {
			std::cout << "Error! Enter valid game type\n";
			IL::getIntNumber(gametype);
		}
		IL::cls();
		if (!gametype) { // play with AI
			game.GType = gametype;
			game.P1_Name = "Player";
			game.P2_Name = "AI";
		}
		else { // play with your friend :) or with yourself :(
			game.GType = gametype;
			
			// start: КОСТЫЛЬ
			std::cin.clear(); // возвращаем cin в 'обычный' режим работы
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
			// end: КОСТЫЛЬ

			std::cout << "Enter Player1 Name: ";
			std::getline(std::cin, game.P1_Name);

			std::cout << "Enter Player2 Name: ";
			std::getline(std::cin, game.P2_Name);
		}

		game.P1_turn = selectTurn();
	}
	else {
		game.P1_turn = !game.P1_turn;
	}
	
	
	game.P1 = (game.P1_turn) ? TTT_Cell::CROSS : TTT_Cell::ZERO;
	game.P2 = (!game.P1_turn) ? TTT_Cell::CROSS : TTT_Cell::ZERO;
	game.turn = 1;
	IL::cls();


#if defined(V2) || defined (V3)
	std::cout << "Enter field size from 3 to ... let it be 9, don't go crazy, okay?" << std::endl;
	while (true) {
		IL::getIntNumber(game.field_size);
		if (game.field_size >= 3 && game.field_size <= 9) break;
		else {
			std::cout << "Enter field size from 3 to 9: ";
		}
	}
#else // V1
	game.field_size = 3; 
#endif

#if defined(V2) || defined (V3)
	std::cout << "Enter win length from 3 to 9 but less or equal to field size" << std::endl;
	while (true) {
		IL::getIntNumber(game.win_len);
		if (game.win_len >= 3 && game.win_len <= 9) {
			if (game.win_len > game.field_size) {
				std::cout << "Enter win length from 3 to 9 but !less or equal! to field size: " << std::endl;
			}
			else {
				break;
			}
		}
		else {
			std::cout << "Enter win length from 3 to 9: ";
		}
	}
#else // V1
	game.win_len = 3;
#endif

	createField(game.TTT_Field, game.field_size, game.field_size);
	initField(game.TTT_Field, game.field_size, game.field_size);

	IL::cls();
	printGame(game);
}


TTT_Progress checkField(TTT_Game& game) {
	
	bool is_equal;

	// проход по строкам
	for (int i = 0; i < game.field_size;i++) {
		for (int j = 0; j < game.field_size - (game.win_len-1); j++) {
			is_equal = true;
			for (int k = 1; k < game.win_len; k++) {
				is_equal = is_equal && (game.TTT_Field[i][j] == game.TTT_Field[i][j + k]);
			}

			if (is_equal && (game.TTT_Field[i][j] == game.P1)) {
				return TTT_Progress::PLAYER1_WON;				
			}
			if (is_equal && (game.TTT_Field[i][j] == game.P2)) {
				return TTT_Progress::PLAYER2_WON;
			}
		}		
	}

	// проход по столбцам
	for (int j = 0; j < game.field_size; j++) {
		for (int i = 0; i < game.field_size - (game.win_len - 1); i++) {
			is_equal = true;
			for (int k = 1; k < game.win_len; k++) {
				is_equal = is_equal && (game.TTT_Field[i][j] == game.TTT_Field[i+k][j]);
			}

			if (is_equal && (game.TTT_Field[i][j] == game.P1)) {
				return TTT_Progress::PLAYER1_WON;
			}
			if (is_equal && (game.TTT_Field[i][j] == game.P2)) {
				return TTT_Progress::PLAYER2_WON;
			}
		}
	}

	// проход по диагоналям	y=kx+b
	for (int x = 0; x < game.field_size - (game.win_len - 1); x++) {
		for (int b = 0; b < game.field_size - (game.win_len - 1); b++) {
			// проход по диагоналям вниз
			is_equal = true;			
			for (int i = 1; i < game.win_len; i++) {
				is_equal = is_equal && (game.TTT_Field[b][x] == game.TTT_Field[b + i][x + i]);
			}

			if (is_equal && (game.TTT_Field[b][x] == game.P1)) {
				return TTT_Progress::PLAYER1_WON;
			}
			if (is_equal && (game.TTT_Field[b][x] == game.P2)) {
				return TTT_Progress::PLAYER2_WON;
			}

			// проход по диагоналям вниз
			is_equal = true;
			for (int i = 1; i < game.win_len; i++) {
				is_equal = is_equal && (game.TTT_Field[b][x + (game.win_len - 1)] == game.TTT_Field[b + i][x + (game.win_len - 1) - i]);
			}
			if (is_equal && (game.TTT_Field[b][x + (game.win_len - 1)] == game.P1)) {
				return TTT_Progress::PLAYER1_WON;
			}
			if (is_equal && (game.TTT_Field[b][x + (game.win_len - 1)] == game.P2)) {
				return TTT_Progress::PLAYER2_WON;
			}
		}
	}

	// Check if draw
	bool is_draw=true;
	for (int i = 0; i < game.field_size; i++) {
		for (int j = 0; j < game.field_size; j++) {
			if (game.TTT_Field[i][j] == TTT_Cell::EMPTY) is_draw = false;
		}
	}
	if (is_draw) return TTT_Progress::DRAW;

	// if no winners and it is not draw
	return TTT_Progress::IN_PROGRESS;
}


TTT_Coord getHumanCoord(TTT_Game& game) {
	TTT_Coord coord = { -1, -1 };
	while (true) {
		do {
			std::cout << "\nEnter x (1.." << game.field_size << "): ";
			IL::getIntNumber(coord.x);
			coord.x--;
		} while ((coord.x) < 0 || (coord.x > (game.field_size - 1)));


		do {
			std::cout << "\nEnter y (1.." << game.field_size << "): ";
			IL::getIntNumber(coord.y);
			coord.y--;
		} while ((coord.y) < 0 || (coord.y > (game.field_size - 1)));

		IL::cls();

		if (game.TTT_Field[coord.y][coord.x] != TTT_Cell::EMPTY) {
			std::cout << "Cell is not empty, try again" << std::endl;
			IL::wait();
			IL::cls();
			printGame(game);
		}
		else {
			break;
		}
	}

	return coord;
}

bool getAICoord(TTT_Game& game) {
#if defined(V2)
	return getAICoord_V2(game);
#elif defined(V3)
	return getAICoord_V3(game);
#else // V1 
	return getAICoord_V1(game);
#endif
}


void nameWinner(TTT_Game& game) {
	switch (game.Progress) {
	case TTT_Progress::PLAYER1_WON: {
		std::cout << game.P1_Name << " won! Congrats to the great " << game.P1_Name << "!" << std::endl;
		game.P1_WINS++;
		break;
	}
	case TTT_Progress::PLAYER2_WON: {
		std::cout << game.P2_Name << " won! Congrats to the great " << game.P2_Name << "!" << std::endl;
		game.P2_WINS++;
		break;
	}
	case TTT_Progress::DRAW: {
		std::cout << "Pobediela drushba!!!" << std::endl;
		game.DRAWS++;
		break;
	}
	}
}


bool restartGame() {
	std::cout << "Restart game? Y/N: ";
	std::string rstrt;
	std::cin >> rstrt;
	while (true) {
		if (rstrt == "Y" || rstrt == "y" || rstrt == "N" || rstrt == "n") break;
		std::cout << "Error! Enter Valid variant\n";
		std::cin >> rstrt;
	}
	if (rstrt == "Y" || rstrt == "y") {
		return true;
	}
	else if (rstrt == "N" || rstrt == "n") {
		return false;
	}
	else {
		std::cout << "WTF?!\n";
		IL::wait();
		exit(0);
	}
}

void saveGameResults(TTT_Game& game) {

	// start: КОСТЫЛЬ
	std::cin.clear(); // возвращаем cin в 'обычный' режим работы
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
	// end: КОСТЫЛЬ

	std::cout << "Save result of this game? Y/N: ";
	std::string do_save;
	std::cin >> do_save;
	while (true) {
		if (do_save == "Y" || do_save == "y" || do_save == "N" || do_save == "n") break;
		std::cout << "Error! Enter Valid variant\n";
		std::cin >> do_save;
	}
	if (do_save == "Y" || do_save == "y") {
		printGame2File(game);
	}
	else if (do_save == "N" || do_save == "n") {
		
	}
	else {
		std::cout << "WTF?!\n";
		IL::wait();
		exit(0);
	}
}

bool printGame2File(TTT_Game& game) {
	// start: КОСТЫЛЬ
	std::cin.clear(); // возвращаем cin в 'обычный' режим работы
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // и удаляем значения предыдущего ввода из входного буфера
	// end: КОСТЫЛЬ
	std::cout << "enter file name: ";
	std::string fname;
	std::cin >> fname;
	std::ofstream fout;
	std::ifstream fin(fname + ".txt");
	if (fin.is_open()) {
		fin.close();
		std::cout << "File exists already. Rewrite or append? [R/A]: ";
		std::string fileop;
		std::cin >> fileop;
		while (true) {
			if (fileop == "R" || fileop == "r" || fileop == "A" || fileop == "a") break;
			std::cout << "Error! Enter Valid variant\n";
			std::cin >> fileop;
		}
		if (fileop == "R" || fileop == "r") {
			fout.open(fname + ".txt");
		}
		else if (fileop == "A" || fileop == "a") {
			fout.open(fname + ".txt", std::ios_base::app);
		}
		else {
			std::cout << "WTF?!\n";
			IL::wait();
			exit(0);
		}
	}else {
		fin.close();
		fout.open(fname + ".txt");
	}

	fout << "     ";
	for (int i = 0; i < game.field_size; i++) {
		fout << i + 1 << "   ";
	} fout << std::endl;

	for (int i = 0; i < game.field_size; i++) {
		if (game.TTT_Field[i] == nullptr) {
			std::cout << "empty ot wrong cell pointer" << std::endl;
			return false;
		}
		// start: print separator
		fout << "   ";// ------------- " << std::endl;
		for (int j = 0; j < game.field_size; j++) {
			fout << "----";
		}
		fout << "- " << std::endl;
		// end: print separator

		// start: print line
		fout << i + 1 << "  | ";
		for (int j = 0; j < game.field_size; j++) {
			fout << (char)game.TTT_Field[i][j] << " | ";
		}
		fout << std::endl;
		// end: print line
	}

	// start: print last separator
	fout << "   ";// ------------- " << std::endl;
	for (int j = 0; j < game.field_size; j++) {
		fout << "----";
	}
	fout << "- " << std::endl;
	// end: print last separator

	fout << game.P1_Name << " sign: " << (char)game.P1 << "\n" << game.P2_Name << " sign: " << (char)game.P2 << std::endl;

	if (game.restarted) {
		fout << std::endl;
		fout << game.P1_Name << " wins: " << game.P1_WINS << std::endl;
		fout << game.P2_Name << " wins: " << game.P2_WINS << std::endl;
		fout << "Draws: " << game.DRAWS << std::endl;
	}

	switch (game.Progress) {
	case TTT_Progress::PLAYER1_WON: {
		fout << game.P1_Name << " won! Congrats to the great " << game.P1_Name << "!" << std::endl;
		break;
	}
	case TTT_Progress::PLAYER2_WON: {
		fout << game.P2_Name << " won! Congrats to the great " << game.P2_Name << "!" << std::endl;
		break;
	}
	case TTT_Progress::DRAW: {
		fout << "Pobediela drushba!!!" << std::endl;
		break;
	}
	}
	fout.close();

	return true;
}

