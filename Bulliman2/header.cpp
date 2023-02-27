// header.cpp

#include "header.h"

// Global variables definition

char MAZE[MAZE_SIZE][MAZE_SIZE];
char WRAPPED_MAZE[MAZE_SIZE + 2][MAZE_SIZE + 2];
int NUM_OF_FOODS = 0;
int BULLI_X;
int BULLI_Y;
int BEAR_X;
int BEAR_Y;
char cPrivousChar;

//---------------------------------------------------------------------
//                             Fill Mazes
//                            ------------ 
// 
// General		: The fuction fills the maze and wrapped maze 
//				  according to input.
//
// Parameters	: 
//		None.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void fill_mazes()
	{
	// Variable definition
	int nWallRow;
	int nWallColumn;
	int nBulliStartX;
	int nBulliStartY;
	int nBearStartX;
	int nBearStartY;
	int nRowsIndex;
	int nColumnsIndex;
	int nWrapperRowsIndex;
	int nWrapperColumnsIndex;

	// Code section

	// Filling the matrix with foods.
	for (nRowsIndex = 0; nRowsIndex < MAZE_SIZE; nRowsIndex++)
		{
		for (nColumnsIndex = 0; nColumnsIndex < MAZE_SIZE; nColumnsIndex++)
			{
			MAZE[nRowsIndex][nColumnsIndex] = '.';
			}
		}

	// Getting valid indexes of walls
	do
		{
		printf("Enter indexes of a wall:");
		scanf("%d %d", &nWallRow, &nWallColumn);
		nWallRow--;
		nWallColumn--;
		printf("\n");
		MAZE[nWallRow][nWallColumn] = '*';
		} while (nWallRow >= 0 && nWallColumn >= 0);

		// Getting valid indexes of bulli
		do
			{
			printf("Enter starting point of Bulli:");
			scanf("%d %d", &nBulliStartX, &nBulliStartY);
			nBulliStartX--;
			nBulliStartY--;
			printf("\n");
			} while (MAZE[nBulliStartX][nBulliStartY] == '*');

			// Getting valid indexes of bear
			do
				{
				printf("Enter starting point of Bear:");
				scanf("%d %d", &nBearStartX, &nBearStartY);
				nBearStartX--;
				nBearStartY--;
				printf("\n");
				} while (MAZE[nBearStartX][nBearStartY] == '*');

				// If bulli starts on a food, he eat it.
				if (MAZE[nBulliStartX][nBulliStartY] == '.')
					{
					NUM_OF_FOODS++;
					}

				// If bear starts on a food, delete it.
				if (MAZE[nBearStartX][nBearStartY] == '.')
					{
					NUM_OF_FOODS--;
					}

				// inserting bulli and bear in the maze.
				MAZE[nBulliStartX][nBulliStartY] = 'B';
				cPrivousChar = MAZE[nBearStartX][nBearStartY];
				MAZE[nBearStartX][nBearStartY] = 'D';

				// Filling the wrapper matrix with walls
				for (nWrapperRowsIndex = 0; nWrapperRowsIndex < MAZE_SIZE + 2; nWrapperRowsIndex++)
					{
					for (nWrapperColumnsIndex = 0;
						nWrapperColumnsIndex < MAZE_SIZE + 2;
						nWrapperColumnsIndex++)
						{
						WRAPPED_MAZE[nWrapperRowsIndex][nWrapperColumnsIndex] = '*';
						}
					}

				// Copying the normal matrix to the wrapper matrix
				for (nWrapperRowsIndex = 1, nRowsIndex = 0;
					nWrapperRowsIndex < MAZE_SIZE + 1;
					nWrapperRowsIndex++, nRowsIndex++)
					{
					for (nWrapperColumnsIndex = 1, nColumnsIndex = 0;
						nWrapperColumnsIndex < MAZE_SIZE + 1;
						nWrapperColumnsIndex++, nColumnsIndex++)
						{
						WRAPPED_MAZE[nWrapperRowsIndex][nWrapperColumnsIndex] = MAZE[nRowsIndex]
							[nColumnsIndex];

						// Eating food
						if (WRAPPED_MAZE[nWrapperRowsIndex][nWrapperColumnsIndex] == '.')
							{
							NUM_OF_FOODS++;
							}
						if (WRAPPED_MAZE[nWrapperRowsIndex][nWrapperColumnsIndex] == 'B')
							{
							BULLI_X = nWrapperRowsIndex;
							BULLI_Y = nWrapperColumnsIndex;
							}
						if (WRAPPED_MAZE[nWrapperRowsIndex][nWrapperColumnsIndex] == 'D')
							{
							BEAR_X = nWrapperRowsIndex;
							BEAR_Y = nWrapperColumnsIndex;
							}
						}
					}
				printf("\n");

				//	OPTIONAL- printing the maze.
				for (nWrapperRowsIndex = 0; nWrapperRowsIndex < MAZE_SIZE + 2; nWrapperRowsIndex++)
					{
					for (nWrapperColumnsIndex = 0;
						nWrapperColumnsIndex < MAZE_SIZE + 2;
						nWrapperColumnsIndex++)
						{
						printf("%c ", WRAPPED_MAZE[nWrapperRowsIndex][nWrapperColumnsIndex]);
						}
					printf("\n");
					}
				printf("\n");

				move();
	}

//---------------------------------------------------------------------
//                                Move 
//                               ------ 
// 
// General		: The fuction moves the bully according to the input.
//
// Parameters	: 
//		None.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void move()
	{
	// Variable definition
	int nBulliDirection;
	int nBulliX;
	int nBulliY;
	int nLastDirection;
	int nWrapperRowsIndex;
	int nWrapperColumnsIndex;

	// Code section
	nLastDirection = 0;

	// Loop ends when bulli wins/loses.
	while (1)
		{
		checkWin();

		printf("Enter direction of Bulli: ");
		scanf("%d", &nBulliDirection);
		printf("\n");

		// Every direction
		switch (nBulliDirection)
			{
			// Keeping the same direction when 0 is pressed.
				case 0:
					nBulliDirection = nLastDirection;

					break;

				case 1: // RIGHT
					if (WRAPPED_MAZE[BULLI_X][BULLI_Y + 1] != '*')
						{
						if (WRAPPED_MAZE[BULLI_X][BULLI_Y + 1] == '.')
							{
							NUM_OF_FOODS--;
							}
						WRAPPED_MAZE[BULLI_X][BULLI_Y] = ' ';
						BULLI_Y++;
						}

					break;
				case 2: // LEFT
					if (WRAPPED_MAZE[BULLI_X][BULLI_Y - 1] != '*')
						{
						if (WRAPPED_MAZE[BULLI_X][BULLI_Y - 1] == '.')
							{
							NUM_OF_FOODS--;
							}
						WRAPPED_MAZE[BULLI_X][BULLI_Y] = ' ';
						BULLI_Y--;
						}

					break;
				case 3: // UP
					if (WRAPPED_MAZE[BULLI_X - 1][BULLI_Y] != '*')
						{
						if (WRAPPED_MAZE[BULLI_X - 1][BULLI_Y] == '.')
							{
							NUM_OF_FOODS--;
							}
						WRAPPED_MAZE[BULLI_X][BULLI_Y] = ' ';
						BULLI_X--;
						}

					break;
				case 4: // DOWN
					if (WRAPPED_MAZE[BULLI_X + 1][BULLI_Y] != '*')
						{
						if (WRAPPED_MAZE[BULLI_X + 1][BULLI_Y] == '.')
							{
							NUM_OF_FOODS--;
							}
						WRAPPED_MAZE[BULLI_X][BULLI_Y] = ' ';
						BULLI_X++;
						}

					break;
				default:
					printf("Invalid Input.\n");
					continue;

					break;
			}
		nLastDirection = nBulliDirection;
		WRAPPED_MAZE[BULLI_X][BULLI_Y] = 'B';
		printf("\n");

		// Bear moves only if bulli moves
		if (nBulliDirection != 0)
			{
			moveBear();
			}

		// OPTIONAL- printing the current maze
		for (nWrapperRowsIndex = 0; nWrapperRowsIndex < MAZE_SIZE + 2; nWrapperRowsIndex++)
			{
			for (nWrapperColumnsIndex = 0;
				nWrapperColumnsIndex < MAZE_SIZE + 2;
				nWrapperColumnsIndex++)
				{
				printf("%c ", WRAPPED_MAZE[nWrapperRowsIndex][nWrapperColumnsIndex]);
				}
			printf("\n");
			}
		printf("\n");
		}
	}


//---------------------------------------------------------------------
//                              Move Bear
//                            ------------ 
// 
// General		: The fuction moves the bear according to the 
//				  position of bulli.
//
// Parameters	: 
//		None.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void moveBear()
	{
	// Variable definition
	int nRownsMargin;
	int nColumnsMargin;
	int nRowsDirection;
	int nColumnsDirection;

	// Code section
	nRownsMargin = BULLI_X - BEAR_X;
	nColumnsMargin = BULLI_Y - BEAR_Y;

	// Finding the direction of bear to move.
	if (nRownsMargin < 0)
		{
		nRowsDirection = -1;
		}
	if (nRownsMargin > 0)
		{
		nRowsDirection = 1;
		}
	if (nRownsMargin == 0)
		{
		nRowsDirection = 0;
		}
	if (nColumnsMargin < 0)
		{
		nColumnsDirection = -1;
		}
	if (nColumnsMargin > 0)
		{
		nColumnsDirection = 1;
		}
	if (nColumnsMargin == 0)
		{
		nColumnsDirection = 0;
		}

	// If destined position of bear is a wall.
	if (WRAPPED_MAZE[BEAR_X + nRowsDirection][BEAR_Y + nColumnsDirection] != '*')
		{
		WRAPPED_MAZE[BEAR_X][BEAR_Y] = cPrivousChar;
		cPrivousChar = WRAPPED_MAZE[BEAR_X + nRowsDirection][BEAR_Y + nColumnsDirection];
		BEAR_X += nRowsDirection;
		BEAR_Y += nColumnsDirection;
		WRAPPED_MAZE[BEAR_X][BEAR_Y] = 'D';
		}
	}

//---------------------------------------------------------------------
//                             Check Win
//                            ----------- 
// 
// General		: The fuction checks if bulli won or lost.
//
// Parameters	: 
//		None.
//
// Return Value : None.
//
//---------------------------------------------------------------------
void checkWin()
	{
	// Code section

	// If bear ate bulli
	if (BULLI_X == BEAR_X && BULLI_Y == BEAR_Y)
		{
		printf("SNAIL BEAR WON!");
		exit(1);
		}

	// If bulli ate all foods
	if (NUM_OF_FOODS == 0)
		{
		printf("BULLI WON!");
		exit(1);
		}

	}