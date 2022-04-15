#include "main.h"

#if defined(V1) && !defined(V2) && !defined(V3)
	bool getAICoord_V1(TTT_Game& game) {
		int x, y;

		// check if wins
		for (y = 0; y < 3; y++) {
			for (x = 0; x < 3; x++) {
				if (game.TTT_Field[y][x] == TTT_Cell::EMPTY) {
					game.TTT_Field[y][x] = game.P2;
					if (checkField(game) == TTT_Progress::PLAYER2_WON) {
						return true;
					}
					else {
						game.TTT_Field[y][x] = TTT_Cell::EMPTY;
					}
				}
				
			}
		}

		// check if opponent can (he-he-he) win
		for (y = 0; y < 3; y++) {
			for (x = 0; x < 3; x++) {
				if (game.TTT_Field[y][x] == TTT_Cell::EMPTY) {
					game.TTT_Field[y][x] = game.P1;
					if (checkField(game) == TTT_Progress::PLAYER1_WON) {
						game.TTT_Field[y][x] = game.P2;
						return true;
					}
					else {
						game.TTT_Field[y][x] = TTT_Cell::EMPTY;
					}
				}

			}
		}

		// ==========================================================
		// ========================= CROSSO =========================
		// ==========================================================
		if (game.P2 == TTT_Cell::CROSS) {
			
			// ========================= first step =========================
			if (game.TTT_Field[0][0] == TTT_Cell::EMPTY && game.TTT_Field[2][0] == TTT_Cell::EMPTY && 
			game.TTT_Field[0][2] == TTT_Cell::EMPTY && game.TTT_Field[2][2] == TTT_Cell::EMPTY) {
				game.TTT_Field[0+2*IL::getRandomNum(0,1)][0 + 2 * IL::getRandomNum(0, 1)] = game.P2;
				return true;
			}
			// ========================= second or third step =========================
			int count_corner_crosses = 0;
			int x[9]{}, y[9]{};
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					if (game.TTT_Field[i*2][j*2] == TTT_Cell::CROSS) {
						x[count_corner_crosses] = j * 2;
						y[count_corner_crosses] = i * 2;
						count_corner_crosses++;
					}
				}
			}
			
			// ========================= second step =========================
			if (count_corner_crosses == 1) {
				if (x[0] ) { // x = 2
					if (game.TTT_Field[y[0]][1] == TTT_Cell::EMPTY && game.TTT_Field[y[0]][0] == TTT_Cell::EMPTY) {
						game.TTT_Field[y[0]][0] = game.P2;
						return true;
					}
					else {
						if (y[0] && game.TTT_Field[0][2] == TTT_Cell::EMPTY ) { // x=2, y=2
							game.TTT_Field[0][2] = game.P2;
							return true;
						}
						if (game.TTT_Field[2][2] == TTT_Cell::EMPTY) { // x=2,y=0
							game.TTT_Field[2][2] = game.P2;
							return true;
						}
					}

				}
				else { // x = 0
					if (game.TTT_Field[y[0]][1] == TTT_Cell::EMPTY && game.TTT_Field[y[0]][2] == TTT_Cell::EMPTY) {
						game.TTT_Field[y[0]][2] = game.P2;
						return true;
					}
					else { 
						if (y[0] && game.TTT_Field[0][0] == TTT_Cell::EMPTY) { // x=0,y=2
							game.TTT_Field[0][0] = game.P2;
							return true;
						}
						if (game.TTT_Field[2][0] == TTT_Cell::EMPTY) { // x=0, y=0;  "else" here is not really needed
							game.TTT_Field[2][0] = game.P2;
							return true;							
						}
					}
				}
			}

			// ========================= third step =========================
			if (count_corner_crosses == 2) {
				for (int st2 = 0; st2 < 2; st2++) {
					// checking X-ed corner
					if (x[st2]) { // x=2
						if (game.TTT_Field[y[st2]][1] == TTT_Cell::EMPTY && game.TTT_Field[y[st2]][0] == TTT_Cell::EMPTY) {
							game.TTT_Field[y[st2]][0] = game.P2; // x=2, y=0 or y=2
							return true;
						}
						if (y[st2] && game.TTT_Field[1][2] == TTT_Cell::EMPTY && game.TTT_Field[0][2] == TTT_Cell::EMPTY) { // x=2, y=2
							game.TTT_Field[0][2] = game.P2;
							return true;
						}
						if (!y[st2] && game.TTT_Field[1][2] == TTT_Cell::EMPTY && game.TTT_Field[2][2] == TTT_Cell::EMPTY) { // x=2,y=0; 
							game.TTT_Field[2][2] = game.P2;
							return true;
						}
					}
					else { // x=0
						if (game.TTT_Field[y[st2]][1] == TTT_Cell::EMPTY && game.TTT_Field[y[st2]][2] == TTT_Cell::EMPTY) {
							game.TTT_Field[y[st2]][2] = game.P2; // x=0, y=0 or y=2
							return true;
						}
						if (y[st2] && game.TTT_Field[1][0] == TTT_Cell::EMPTY && game.TTT_Field[0][0] == TTT_Cell::EMPTY) { // x=0, y=2
							game.TTT_Field[0][0] = game.P2;
							return true;
						}
						if (!y[st2] && game.TTT_Field[1][0] == TTT_Cell::EMPTY && game.TTT_Field[2][0] == TTT_Cell::EMPTY) { // x=0,y=0; 
							game.TTT_Field[2][0] = game.P2;
							return true;
						}
					}
				}
			}

			// ========================= try any empty line with one own symbol=========================
			int empty_cells = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (game.TTT_Field[i][j] == TTT_Cell::EMPTY) {
						x[empty_cells] = j;
						y[empty_cells] = i;
						empty_cells++;
					}
				}
			}

			for (int i = 0; i < empty_cells; i++) {
				// check horizontal
				if (x[i] == 0 && (game.TTT_Field[y[i]][1] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][1] == game.P2) && 
				(game.TTT_Field[y[i]][2] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][2] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				if (x[i] == 1 && (game.TTT_Field[y[i]][0] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][0] == game.P2) &&
					(game.TTT_Field[y[i]][2] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][2] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				if (x[i] == 2 && (game.TTT_Field[y[i]][1] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][1] == game.P2) &&
					(game.TTT_Field[y[i]][0] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][0] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}
				// check vertical
				if (y[i] == 0 && (game.TTT_Field[1][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[1][x[i]] == game.P2) &&
					(game.TTT_Field[2][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[2][x[i]] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				if (y[i] == 1 && (game.TTT_Field[0][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[0][x[i]] == game.P2) &&
					(game.TTT_Field[2][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[2][x[i]] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				if (y[i] == 2 && (game.TTT_Field[0][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[0][x[i]] == game.P2) &&
					(game.TTT_Field[1][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[1][x[i]] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				// no diagonal checks
			}

			int randcell = IL::getRandomNum(0, empty_cells - 1);
			game.TTT_Field[y[randcell]][x[randcell]] = game.P2;
			return true;


		}

		// ========================================================
		// ========================= ZERO =========================
		// ========================================================
		if (game.P2 == TTT_Cell::ZERO) {
			int x[9]{}, y[9]{};

			if (game.TTT_Field[1][1] == TTT_Cell::EMPTY) {
				game.TTT_Field[1][1] = game.P2;
				return true;
			}
			else if (game.TTT_Field[1][1] == TTT_Cell::CROSS) {
				int empty_diags = 0;
				// try any empty diagonal;
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++) {
						if ((i == j) || (i == (2 - j))) {
							if (game.TTT_Field[i][j] == TTT_Cell::EMPTY) {
								x[empty_diags] = j;
								y[empty_diags] = i;
								empty_diags++;
							}
						}
					}
				}
				if (empty_diags > 0) {
					int chosen_one = IL::getRandomNum(0, empty_diags);
					game.TTT_Field[y[chosen_one]][x[chosen_one]] = game.P2;
					return true;
				}
			}

			
			// ========================= try any empty line with one own symbol =========================
			int empty_cells = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (game.TTT_Field[i][j] == TTT_Cell::EMPTY) {
						x[empty_cells] = j;
						y[empty_cells] = i;
						empty_cells++;
					}
				}
			}

			for (int i = 0; i < empty_cells; i++) {
				// check horizontal
				if (x[i] == 0 && (game.TTT_Field[y[i]][1] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][1] == game.P2) &&
					(game.TTT_Field[y[i]][2] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][2] == game.P2)) { // pos=(0, any) and (1,any) and (2,any) are empty or handled by AI
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				if (x[i] == 1 && (game.TTT_Field[y[i]][0] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][0] == game.P2) &&
					(game.TTT_Field[y[i]][2] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][2] == game.P2)) { // pos=(1, any) and (0,any) and (2,any) are empty or handled by AI
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				if (x[i] == 2 && (game.TTT_Field[y[i]][1] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][1] == game.P2) &&
					(game.TTT_Field[y[i]][0] == TTT_Cell::EMPTY || game.TTT_Field[y[i]][0] == game.P2)) { // pos=(2, any) and (1,any) and (0,any) are empty or handled by AI
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}
				// check vertical
				if (y[i] == 0 && (game.TTT_Field[1][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[1][x[i]] == game.P2) &&
					(game.TTT_Field[2][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[2][x[i]] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				if (y[i] == 1 && (game.TTT_Field[0][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[0][x[i]] == game.P2) &&
					(game.TTT_Field[2][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[2][x[i]] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				if (y[i] == 2 && (game.TTT_Field[0][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[0][x[i]] == game.P2) &&
					(game.TTT_Field[1][x[i]] == TTT_Cell::EMPTY || game.TTT_Field[1][x[i]] == game.P2)) {
					game.TTT_Field[y[i]][x[i]] = game.P2;
					return true;
				}

				// no diagonal checks
			}




			int empty_nondiags=0;
			// try any empty nondiagonal;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if ( (i != j) && (i != (2-j)) ) {
						if (game.TTT_Field[i][j] == TTT_Cell::EMPTY) {
							x[empty_nondiags] = j;
							y[empty_nondiags] = i;
							empty_nondiags++;
						}
					}
				}
			}

			if (empty_nondiags > 0) {
				int chosen_one = IL::getRandomNum(0, empty_nondiags);
				game.TTT_Field[y[chosen_one]][x[chosen_one]] = game.P2;
				return true;
			}
			

			// try any empty
			empty_cells = 0;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (game.TTT_Field[i][j] == TTT_Cell::EMPTY) {
						x[empty_cells] = j;
						y[empty_cells] = i;
						empty_cells++;
					}
				}
			}

			int randcell = IL::getRandomNum(0, empty_cells - 1);
			game.TTT_Field[y[randcell]][x[randcell]] = game.P2;
			return true;
		}

		if (game.P2 != TTT_Cell::ZERO && game.P2 != TTT_Cell::CROSS) {
			std::cout << "Something is REALLY wrong" << std::endl;
			IL::wait();
			exit(0);
		}



		return false;
	}
#endif
