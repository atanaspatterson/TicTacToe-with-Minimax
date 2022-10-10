#include <stdio.h>

int minimax (char *board [3][3], int row, int column, int depth) {
	int isWinnwer = findWinner(char *board [3][3]);
	if(isWinner){
		
	}	
			/*	base cases:
					if maximizer wins
						score = max;
					if minimizer wins
						socre = min
					if draw (there are no more free spaces)
						scorew = 0
				recursive case
					for rows r:
						for columns c:
							is space is open
								recursive(r, c) decomposes the data by filling that space up

			the way scoring goes is like a tree, when we want to calculate the best move we consider all possible cases. for example, player chooses top corner. One of the cases is ai chooses
			middle, and x may go bottom right after that. we reach these cases with recursion. With every possible board, we go to a case where someone wins or draws.

			The program is: make a move, switch players, recurse, print computer move and so on until winner or a draw.

			Minimax is exhaustive; all moves are scored MINIMAX: recursively finds a score for all possible moves amoing thousands of choices

			example of maximizer (minimizer would be the opposite, less is better)
				1 iteration that leads to a win = + 2
				1 iteratio "" = +7 this becomes the new best move
			sooner wins are better, and to know this we find the depth of the recursion. A way to do this is to call minimax at first with depth 0 and when we recurse we call minimax*/ with depth +1.

	return ();
}

void printBoard (char board[3][3]) {
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column< 3; column++) {
			if (column == 0 || column == 1)
				printf(" %c |", board[row][column]);
			else if (column == 2){
				printf(" %c", board[row][column]);
			}
		}
	printf("\n");
	if (row != 2)
		printf("---+---+---\n");
	}
}

int findWinner (char board[3][3]) {
	for (int i = 0; i < 3; i++) {
		if ((board[i][0] == board[i][1]) && (board[i][1] == board[i][2])) {
			if (board[i][0] == 'X') {
				printf("X wins\n");
				return 1;	
			}
			else if (board[i][0] == 'O') {
				printf("O wins\n");
				return -1;			
			}
		}
	}

	for (int i = 0; i < 3; i++) {
		if ((board[0][i] == board[1][i]) && (board[1][i] == board[2][i])) {
			if (board[0][i] == 'X') {
				printf("X wins\n");
				return 1;	
			}
			else if (board[0][i] == 'O') {
				printf("O wins\n");
				return -1;			
			}
		}
	}

	if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) {
		if (board[0][0] == 'X') {
			printf("X wins\n");
			return 1;	
		}
		else if (board[0][0] == 'O') {
			printf("O wins\n");
			return -1;			
		}
	} else if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0])) {
		if (board[0][2] == 'X') {
			printf("X wins\n");
			return 1;	
		}
		else if (board[0][2] == 'O') {
			printf("O wins\n");
			return -1;			
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '_'){
				return -2;
			}

		}
	}

	printf("draw\n");
	return 0;
}

int * findBestMove (char *board[3][3]) {
	int bestScore = -100;
	int bestSquare[2];
	int currScore;
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			if(*board[row][column] == '_'){
				currScore = minimax(board, row, column, 0);
				if (currScore > bestScore){
					bestScore = currScore;
					bestSquare[0] = row;
					bestSquare[1] = column;
				}
			}
		}	
	}
	return bestSquare;
}





int main (int argc, char *argv[]) {


		/* how to do minimax

				base cases:
					if maximizer wins
						score = max;
					if minimizer wins
						socre = min
					if draw (there are no more free spaces)
						scorew = 0
				recursive case
					for rows r:
						for columns c:
							is space is open
								recursive(r, c) decomposes the data by filling that space up

			the way scoring goes is like a tree, when we want to calculate the best move we consider all possible cases. for example, player chooses top corner. One of the cases is ai chooses
			middle, and x may go bottom right after that. we reach these cases with recursion. With every possible board, we go to a case where someone wins or draws.

			The program is: make a move, switch players, recurse, print computer move and so on until winner or a draw.

			Minimax is exhaustive; all moves are scored MINIMAX: recursively finds a score for all possible moves amoing thousands of choices

			example of maximizer (minimizer would be the opposite, less is better)
				1 iteration that leads to a win = + 2
				1 iteratio "" = +7 this becomes the new best move
			sooner wins are better, and to know this we find the depth of the recursion. A way to do this is to call minimax at first with depth 0 and when we recurse we call minimax with depth +1.

			need a function that records scores and picks the best one:

				findbestmove(board)
					runningbestscore (if youre minimizer lowest score, if maximizer highest score)
					loop over board
						score = minimax(r, c)
						if score is better
							runningbestscore = score
							keep r and c that generated that score
						else
							undo that move
							try again
					move to best r, c
			


	
	*/return 0;
}
