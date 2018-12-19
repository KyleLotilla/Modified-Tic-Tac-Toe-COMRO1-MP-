/*Written by: Kyle Lotilla
Description:
This game is a variant of Tic-tac-toe called "Three board tic-tac-toe misere mode". In this mode, two players takes turns placing markers on 3 boards.
When a space is marked, the space can no longer be marked. When a line forms in a board, the board is considered "dead" and spaces on the board could no longer be marked.
When all the board are dead, the player who killed the last board will lose and the other player wins.*/
#include <stdio.h>
#include <ctype.h>

typedef char arrspace[3][9];
typedef int arrstatus[3];
typedef int arrscore[2];

void startGame(int *, arrspace, arrstatus);
int getBoardNumber(char);
int getSpaceCoordinate(char);
void drawBoard(arrspace);
int isInvalidMove (char, int, int, arrspace, arrstatus);
int isBoardDead(int, arrspace);
void killBoard(int, arrspace, arrstatus);
int getGameStatus(arrstatus);
void printResults(arrscore);

int main ()
{
   arrstatus boardStatus; // Indicates the status of the three boards wether it is alive or dead. 1 = Alive, 0 = Dead
   arrspace marks; // Stores the characters and marks to be printed on the board. The first dimension is the board number of the space and the second is it's coordinate on the board.
   arrscore playerScore = {0, 0}; // Keeps of the scores of the players through multiple games. The first element is player 1's score and the second is player 2's score. 
   int playerTurn; // Keeps track of who's turn is it. 0 = Player 1, 1 = Player 2, !playerturn = the other player
   int boardNumber; // Stores the board number of the board the player's input is on. 0 = first board, 1 = second, 2 = third
   int spaceCoordinate; // Stores the space coordinate of the space where the player's input is located on the corresponding board. Goes from left to right, Up to down
   char move; // Player input
   char reply = 'n'; // Determines whether the players want to continue playing
   
   startGame(&playerTurn, marks, boardStatus);

   while (getGameStatus(boardStatus))
   {
      drawBoard(marks);
       
      do
      {
         fflush(stdin);
         printf("Player %d, enter your move: ", playerTurn + 1);
         scanf("%c", &move);
         move = toupper(move);
         spaceCoordinate = getSpaceCoordinate(move);
         boardNumber = getBoardNumber(move);
      } while(isInvalidMove(move, spaceCoordinate, boardNumber, marks, boardStatus));

      marks[boardNumber][spaceCoordinate] = ' '; // Marks the space the player inputted
       
      if (isBoardDead(boardNumber, marks))
         killBoard(boardNumber, marks, boardStatus);
   
      if (!getGameStatus(boardStatus))
      {
         printf("Since this move kills the last living board, Player %d loses. Player %d wins.\n\n", playerTurn + 1, !playerTurn + 1);
         playerScore[!playerTurn]++; // Add score to the other player
         printf("Player 1 has %d win(s). Player 2 has %d win(s)\n\n", playerScore[0], playerScore[1]);
          
         do
         {
            printf("Do you want to continue? (Y/N) ");
            fflush(stdin);
            scanf("%c", &reply);
         } while (toupper(reply) != 'N' && toupper(reply) != 'Y');
    
         if (toupper(reply) == 'Y')
            startGame(&playerTurn, marks, boardStatus); // Reset the game back to default for continous play
      }
      else
         playerTurn = !playerTurn; // Changes Player Turn
   }
   
   printResults(playerScore);

   getchar();
   return 0;
}

void startGame(int *playerTurn, arrspace marks, arrstatus boardStatus)
{
// Initializes the variable playerTurn and arrays needed to start the game. It is also used to reset the game when the players want to continue playing.
   int i, j, k;
   char letter = 'A';
   *playerTurn = 0;
   
   for (i = 0; i < 3; i++) // Sets all boards to alive, causing the game to reset when the player want to continue playing
      boardStatus[i] = 1;
   
   for(j = 0; j < 3; j++) // Assigns the array marks to default chracters
      for(k = 0; k < 9; k++)
      {
         if (j == 1 && k == 4)
      	    marks[j][k] = '&';  // Assigns '&' to the middle element of the middle board
      	 else 
		 {
      	    marks[j][k] = letter;
      	    letter++;
		 }
	  }
   return;  
}

int getBoardNumber (char move)
{
// Returns the board number of the board where the player's input is on
   if (move >= 'R')
      return 2;
   else if (move >= 'J' || move == '&')
      return 1;
   else
      return 0;
}

int getSpaceCoordinate (char move)
{
// Returns the space coordinate of the space where the player's input is on the corresponding board
   if (move == '&')
      return 4;
   else if (move >= 'R')
      return move - 'R';
   else if (move >= 'N')
      return move - 'N' + 5; // Adds 5 to compensate for the first 5 elements in the board
   else if (move >= 'J')
      return move - 'J';
   else
      return move - 'A';
}

void drawBoard(arrspace marks)
{
// This function prints the three boards, the characters, and marks
   int i, j, k, l;
   int charPosition; // Keeps the position where the next character or mark is going to be printed
   int spaceCoordinate;
   int boardNumber;
	
   printf("\n");
	
   for (i = 0; i < 3; i++) // Prints one row of all three boards at once per iteration by printing three lines
   {
      for (j = 1; j <= 36; j++) // Prints the first line
	     if (j % 12 == 0)
		    printf("\t"); // Prints spaces between tables
		 else if (j % 4 == 0)
		    printf("|"); // Prints borders
		 else
		    printf(" ");
	
      charPosition = 2;
	  boardNumber = 0;
	  spaceCoordinate = i * 3;
	  printf("\n");
	
	  for (k = 1; k <= 36; k++) // Prints the second line, which is where the character or mark is going to be printed
	     if (k == charPosition)
	     {
		    if (spaceCoordinate == i * 3 + 3) // Once the corresponding characters and marks are printed in a row of a board,
		    {
			   spaceCoordinate = i * 3; // the space coordinate is assigned to it's original value in the current iteration of the outer loop
			   boardNumber++; // and the board number increments so the corresponding charatcers and marks could be printed on the same row of the next board
		    }
		      
		    printf("%c", marks[boardNumber][spaceCoordinate]);
		    charPosition += 4;
		    spaceCoordinate++;
	     }
	     else if (k % 12 == 0)
	        printf("\t");
	     else if (k % 4 == 0)
	        printf("|");
	     else
	        printf(" ");
	
      printf("\n");
	
      for (l = 1; l <= 36; l++)
	     if (l % 12 == 0)
	        printf("\t");
	     else if (l % 4 == 0)
	        printf("|");
	     else if (i == 2)
	        printf(" "); // Prints spaces instead of the horizantal border for the last iteration of the outer loop
	     else
	        printf("_"); // Prints the horizontal borders
	
      printf("\n");
   }
    
   printf("\n");
   return;
}

int isInvalidMove (char move, int spaceCoordinate, int boardNumber, arrspace marks, arrstatus boardStatus)
{
// Validates the player's input whether it is a valid or invalid input. Also tells the player what's wrong with his input.
   if (!isalpha(move) && move != '&') // Checks whether the input is a character that is found in the board
   {
      printf("Please enter only characters found on the boards.\n\n");
      return 1;
   }
   else if (!boardStatus[boardNumber]) // Checks whether the board the input is on is dead
   {
      printf("That board is part of a dead board. You cannot place markers on that board anymore.\n\n");
      return 1;
   }
   else if (marks[boardNumber][spaceCoordinate] == ' ') // Checks whether the space is already marked
   {
      printf("That space is already occupied. You cannot place markers on that space anymore.\n\n");
      return 1;
   }
   else
      return 0;
}

int isBoardDead(int boardNumber, arrspace marks)
{
// Checks whether the current player's latest input kills the board by checking if a line has been formed
   int i, j;
  
   if (marks[boardNumber][0] == ' ' && marks[boardNumber][4] == ' ' && marks[boardNumber][8] == ' ' 
   || marks[boardNumber][2] == ' ' && marks[boardNumber][4] == ' ' && marks[boardNumber][6] == ' ') // Checks for diagonal lines
      return 1;
   
   for (i = 0; i < 3; i++)
      if (marks[boardNumber][i] == ' ' && marks[boardNumber][i+3] == ' ' && marks[boardNumber][i+6] == ' ') // Checks for vertical lines
         return 1;
      
   for (j = 0; j <= 6; j += 3)
      if (marks[boardNumber][j] == ' ' && marks[boardNumber][j+1] == ' ' && marks[boardNumber][j+2] == ' ') // Checks for horizontal lines
         return 1;
     
   return 0;
}

void killBoard (int boardNumber, arrspace marks, arrstatus boardStatus)
{
// Kills the corresponding board
   int i;
   boardStatus[boardNumber] = 0; // Sets board status to dead
   
   for (i = 0; i < 9; i++) // Assigns character space to all the spaces of the board to visually represent a dead board
      marks[boardNumber][i] = ' ';
      
   printf("This move kills the board, you can no longer place markers on that board.\n\n");
   return;
}

int getGameStatus (arrstatus boardStatus)
{
// Checks whether a game is still ongoing by checking if all the board are dead
   if (!boardStatus[0] && !boardStatus[1] && !boardStatus[2])
      return 0;
   else
      return 1;
}

void printResults (arrscore playerScore)
{
// Prints the overall results of all the games the players played. It also determines the overall winner.
   printf("\nThe final score is %d win(s) for Player 1 and %d win(s) for Player 2. ", playerScore[0], playerScore[1]);
   if (playerScore[0] > playerScore[1])
      printf("Player 1 is the overall winner.\n\n", playerScore[0]);
   else if (playerScore[0] < playerScore[1])
      printf("Player 2 is the overall winner.\n\n", playerScore[1]);
   else
      printf("It's a tie.\n\n");

   printf("Game Over.");
   return;
}
