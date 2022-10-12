#include <stdio.h>
#include <stdlib.h>

// function that prints out the current state of the board
void printBoard (char board[3][3]) {                                                        
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column< 3; column++) {
			if (column == 0 || column == 1)
				printf(" %c |", board[row][column]);
			else if (column == 2) {
				printf(" %c", board[row][column]);
			}
		}
	printf("\n");
	if (row != 2)
		printf("---+---+---\n");
	}
}

// function that returns an integer depending on the state of the board (X win, O win, draw or no win)
int findWinner (char board[3][3]) {																
	for (int row = 0; row < 3; row++) {																			// case of horizontal win
		if ((board[row][0] == board[row][1]) && (board[row][1] == board[row][2])) {
			if (board[row][0] == 'O') {
				return 10;	
			}
			else if (board[row][0] == 'X') {
				return -10;			
			}
		}
	}
	
	for (int column = 0; column < 3; column++) {																// case of vertical win
		if ((board[0][column] == board[1][column]) && (board[1][column] == board[2][column])) {
			if (board[0][column] == 'O') {
				return 10;	
			}
			else if (board[0][column] == 'X') {
				return -10;			
			}
		}
	}

	if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) {											// case of diagonal win
		if (board[0][0] == 'O') {
			return 10;	
		}
		else if (board[0][0] == 'X') {
			return -10;			
		}
	} else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0])) {
		if (board[0][2] == 'O') {
			return 10;	
		}
		else if (board[0][2] == 'X') {
			return -10;			
		}
	}
	
	for (int row = 0; row < 3; row++) {																			// case of no winner (still unmarked spaces)
		for (int column = 0; column < 3; column++) {
			if (board[row][column] == '_'){
				return -1;
			}

		}	
	}
	return 0;																									// case of draw
}

// function that returns the score for a move
int minimax (char board [3][3], char player, int depth) {
	int score;
	int bestScore;
		
	int isWinner = findWinner(board);
	if (isWinner == 10)
		return isWinner - depth;
	else if (isWinner == -10)
		return isWinner + depth;
	else if (isWinner == 0)
		return isWinner;

	if (player == 'O') {
		bestScore = -100;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == '_') {
					board[i][j] = 'O';
					score = minimax(board, 'X', depth + 1);
					if (score > bestScore)
						bestScore = score;
					board[i][j] = '_';	
				}
			}
		}
	} else if (player == 'X') {
		bestScore = 100;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == '_') {
					board[i][j] = 'X';
					score = minimax(board, 'O', depth + 1);
					if (score < bestScore)
						bestScore = score;
					board[i][j] = '_';	
				}
			}
		}
	}
	return bestScore;
}

// function that assigns the row and column variables with the best possible move
void findBestMove (char board[3][3], char player, int *r, int *c ) {
	int currScore;
	int bestScore;

	if (player == 'X')
		bestScore = 100;
	else
		bestScore = -100;

	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			if (board[row][column] == '_') {
				board[row][column] = player;
				if (player == 'X') {
					currScore = minimax(board, 'O', 1);
					if (currScore < bestScore) {
						bestScore = currScore;
						*r = row;
						*c = column;
					}
					board[row][column] = '_';
				} else {
					currScore = minimax(board, 'X', 1);
					if (currScore > bestScore) {
						bestScore = currScore;
						*r = row;
						*c = column;
					}
					board[row][column] = '_';
				}
			}
		}	
	}
}

// function that prints out the result of a ttt match
void printResult (int result) {
	if (result == 10)
		printf("O wins\n");
	else if (result == -10)
		printf("X wins\n");
	else if (result == 0)
		printf("draw\n");
}

// function that initializes the ttt board
void initBoard(char board[3][3], int value, char *argv[]) {
	int k = 1;
	if (value > 1) {
		for (int row = 0; row < 3; row++) {
			for (int column = 0; column < 3; column++) {
				board[row][column] = *argv[k];
				k++;
			}
		}
	} else {
		for (int row = 0; row < 3; row++) {
			for (int column = 0; column < 3; column++) {
				board[row][column] = '_';
			}
		}
	}
}

int main (int argc, char *argv[]) {
	char board[3][3];
	initBoard(board, argc, argv);
	int r;
	int c;

	if (argc > 1) {																				// case if player wants to know the next best move
		printBoard(board);
		findBestMove(board,'O', &r, &c);
		printf("O: %d %d\n", r, c);
	} else {																					// case if player wants to play against computer
		int gameDone = -1;
		printBoard(board);
		while (gameDone == -1) {
			printf("X: ");
			fscanf(stdin, "%d %d", &r, &c);
			if ((board[r][c] == '_') && (r >= 0) && (r < 3) && (c >= 0) && (c < 3)) {			// check if player move is valid
				board[r][c] = 'X';
				if (findWinner(board) == -10 || findWinner(board) == 0) {						// check if player move ends the game
					gameDone = findWinner(board);
					break;
				}
				findBestMove(board, 'O', &r, &c);
				board[r][c] = 'O';
				printf("O moves to %d %d\n", r, c);
				if (findWinner(board) == 10 || findWinner(board) == 0) {						// check if computer move ends the game
					gameDone = findWinner(board);
					break;
				}
				printBoard(board);	
			} else {								
				printf("invalid move\n");
				break;
			}
		}		

		if (gameDone != -1){
			printBoard(board);
			printResult(gameDone);
		}
	}
	
	return 0;
}
