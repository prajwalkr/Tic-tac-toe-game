// Author K R Prajwal   *claps* :P
// This is a full featured tic tac toe game with MiniMax algorithm.

// all required headers
#include <iostream>      							// cin,cout
#include <algorithm>	 							// fill()
#include <cstdlib>		 							// system()
#include <ctime>									// seed value for rand()
#include <vector>									//  for a vector of pair of moves
#include <utility>									//	for a pair of desired move
using namespace std;
# define n 3  										// change n to the value you wish
char a[n][n],victor;								// a[n][n] is the board, victor is the temporary winner in the game tree, not actual.
const char first = 'X',second = 'O',blank = '-';	// self - explanatory
class common_features								// Using the power of inheritance to reduce code. All common features
{													// of oneplayer and twoplayer in a single class.
protected:											// Cuz, private members don't support inheritance
	void initialize()								// Board is now full of '-'s. Instructions given to user.
	{
		for (int i = 0; i < n; ++i)
		{
			fill(a[i],a[i] + n,blank);				// std::fill(container.begin(),container.end(),element);
		}
		cout << "Instructions: \n1. Your response to each turn should be of the format:  i  j \n   where i and j are 0-indexed positions of the board.\n";
		cout << "2.'X' is for the first player, 'O' is for the second dude.\n\n";
	}
	void printboard()								// prints the board at a given state.
	{
		int i,j;
		cout << " \n\n\t\t\t Current board view";
		for (i = 0; i < n; ++i)
		{
			cout << endl << endl << "\t\t";
			for (j = 0; j < n; ++j)
			{
				cout << a[i][j] << "\t\t";
			}
		}
	}
    bool endgame(char a[][n])					// Checks whether the current game has ended
	{											// 2 possibilities exist:
		if (checkforvictory(a))					// A win by a player
			return true;
		int i,j;								// OR
		for (i = 0; i < n; ++i)
		{										// No more blank spots on board, i.e a draw
			for (j = 0; j < n; ++j)
			{
				if (a[i][j] == blank)			// If there's one blank space,
					return false;				// then the game is not over.
			}
		}
		return true;
	}
	bool checkforvictory(char a[][n])			// checkforvictory() = 1 if any player wins
	{											// 					   0 otherwise
		int i,j;
		char temp;

		bool win = false;
		for (i = 0; i < n; ++i)
		{										// row-wise check for victory
		    temp = a[i][0];
		    if(temp == blank)
                continue;
            win = true;
            for(j = 0; j < n; j++)
            {
                if(a[i][j] != temp)
                {
                     win = false;
                     break;
                }
            }
			if(win)
            {
                victor = temp;					// store the victor
                return true;
            }
		}

		win = false;
		for (i = 0; i < n; ++i) 				// column-wisecheck for victory
		{
			temp = a[0][i];
			if(temp == blank)
                continue;
			win = true;
			for (j = 0; j < n; ++j)
			{
				if (a[j][i] != temp)
				{
					win = false;
					break;
				}
			}
			if (win)
			{
				victor = temp;
				return true;
			}
		}

		if(a[0][0] != blank)				// check along princpal diagonal
		{
		    temp = a[0][0];
            bool finish = true;
            for (i = 0; i < n; ++i)
            {
                if (a[i][i] != temp)
                {
                    finish = false;
                    break;
                }
            }
            if (finish)
            {
                victor = temp;
                return true;
            }
		}

		if(a[n-1][0] != blank)			  // other diagonal
		{
		    char temp = a[n-1][0];
            bool finish = true;
            for (i = 0; i < n; ++i)
            {
                if (a[i][n-i-1] != temp)
                {
                    finish = false;
                    break;
                }
            }
            if (finish)
            {
                victor = temp;
                return true;
            }
		}
		return false;
	}
	void result(int c)										// Display the final result of the game
	{
		if (c == 0)											// c == 0 => Player 2 played last
		{													//   == 1 => Player 1 played last
			cout << "Player 2, Hats off!" << endl;
			cout << "Enjoy how Player 1 sucked: \n\n";
		}
		else if(c == 1)
		{
			cout << "Player 1, Hats off!" << endl;
			cout << "Enjoy how Player 2 sucked: \n\n";
		}
		else
        {
            cout << "...Wow. That was a draw." << endl;
            cout << "Your lovely board: \n\n";
        }
		printboard();
		cout << "\n\n\n";
	}
};
class twoplayer : public common_features							// implements features specific to a two-player mode
{																	// inherits the rest from common features
public:
	twoplayer()
	{
		initialize();												// constructor initialises the board.
	}
	void choose_the_first()
	{
		srand(time(NULL));											// Randomly chose a player to start first
		game((rand()%100)%2);
	}
private:
	void game(int c)												// c == 0 => Player 1's turn
	{
		bool gameover = false;										// c == 1 => Player 2's turn
		int i,j;
		while(!gameover)											// while game is not yet over...
		{
			printboard();
			cout << "\n\nPlayer " << c + 1 << "'s turn:  ";			// Get input from the respective player
			cin >> i >> j;
			yeah:
			if (i < n && j < n && a[i][j] == blank)					// A valid move by user....
			{
				a[i][j] = c?second:first;
				c = !c;
				system("cls");
			}
			else													// if user inputs an invalid move
			{
				cout << "What the hell are you doing? Do it again and I will end your little game. Both of you lose. -_- \n";
				cout << "\n\nPlayer " << c + 1 << "'s turn:  ";
				cin >> i >> j;
				if (i >= n || j >= n)								// These are JFF. :D
					return;
				else goto yeah;
			}
			gameover = endgame(a);									// Check with the endgame() function if game is not yet over.
		}
		bool win_lose = checkforvictory(a);							// win_lose = 1 if any player wins.
		if(win_lose == false)										//          = 0 if it's a draw.
            c = -1;
		result(c);													// Print the result of the game
	}
};
class oneplayer : private common_features							// Implements 1-player mode ---- against the machine
{
public:
	oneplayer()
	{
		initialize();
	}
	void choose_the_first()
	{
		cout << "\n\n Note that Player 2 = The Machine itself.\n\n";     // Player 2 is always the machine and Player 1 = User
		srand(time(NULL));
		game((rand()%100)%2);											// Randomly choose who gets to play first
	}
private:
	int winner(char a[][n])												// winner() =  0        if draw,
	{																	//			= -32000    if the user wins
		if (checkforvictory(a))											//          =  32000    if the computer wins
		{
			if(victor == first)
            {
                return -32000;
            }
            return 32000;
		}
		return 0;
	}
/*********************************************************************************************************
* From now, the Minimax algorithm begins. Now, there are two functions below max_box() and min_box()	 *
* They can be quite easily combined to get a single function Minimax() but....the split up functions     *
* provide better understanding of the code. 															 *
* So, a bit lof the shortness of the code is being sacrificed for better understanding.					 *
* Let's get down to the algorithm now.																	 *
* 1. At every computer's turn, choose_best_box() is called.												 *
* 2. For every blank box in the current board, evaluate the end score for all blank boxes and take their *
*    maximum. 																							 *
*    2.1 Try a particular box, mark it with 'O'. 														 *
* 	 2.2 Call min_box() to minimise user'score.															 *
* 3. In min_box():																						 *
*	 3.1 Check for base case :- [If endgame reached return winner()]									 *
*    3.2 For every blank box:																			 *
*		 3.2.1 Mark the box with 'X'																	 *
*		 3.2.2 Call max_box() for the rest of the board and store the scores obtained					 *
*		 3.2.3 Unmark that box       																	 *
*	 3.3 Return the minimum score obtained from all the blank boxes									     *
* 4. In max_box(), the computer score is maximised and human's score is minimized by calling min_box()   *
*    4.1 Check for base case :- [If endgame reached return winner()]									 *
*    4.2 For every blank box:																			 *
*		 4.2.1 Mark the box with 'O'																	 *
*		 4.2.2 Call max_box() for the rest of the board and store the scores obtained					 *
*		 4.2.3 Unmark that box 																			 *
*	 4.3 Return the maximum score obtained from all the blank boxes									     *
* 5. The required move is the box that has the maximum score                                             *
* 6. As an extra feature, rand() can be used to choose any of the best moves 							 *
**********************************************************************************************************/

	void choose_best_box(char a[][n])
	{
		int i,j,cur_score,best = -32001;						// best score is -32001
		vector < pair <int,int> > moves;						// list of all possible moves
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j)
			{
				if (a[i][j] == blank)							// if blank
				{
					a[i][j] = second;							// try machine move at this square
					cur_score = min_box(a);						// check if it's the best
					if (cur_score > best)						// if it's the better than prev score,
					{											// delete all previous moves and create a new list of best moves
						moves.clear();
						moves.push_back(make_pair(i,j));
						best = cur_score;						// new best score
					}
					if (cur_score == best)						// if it's equal to current best, add it to the list of best moves
					{
						moves.push_back(make_pair(i,j));
					}
					a[i][j] = blank;							// reset the marked square
				}
			}
		}
		pair <int,int> move = moves[rand()%moves.size()];
		a[move.first][move.second] = second;					// assign one random square from the list of best squares
	}
	int max_box(char a[][n])									// returns best score from the current board state
	{
		if (endgame(a))											// if game is over
	        return winner(a);									// return the score of the current board
		int i,j,best = -2,cur_score;

		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j)
			{
				if (a[i][j] == blank)						   // For every blank square
				{
					a[i][j] = second;						  // mark it with the machine's letter

					cur_score = min_box(a);					 // and call min_box() for human's turn.
					if (cur_score > best)					 // if this square generates a better score
					{
						best = cur_score;					// Store the better square
					}
                    a[i][j] = blank;					    // Unmark the square
				}
			}
		}
		return best;										// Return the best value obtained from the current board state
	}
	int min_box(char a[][n])								// returns the worst possible score from the current board
	{
		int i,j,cur_score,worst = 2;
		if (endgame(a))										// same base case
			return winner(a);
		for (i = 0; i < n; ++i)
		{
			for (j = 0; j < n; ++j)
			{
				if (a[i][j] == blank)						// if blank square
				{

					a[i][j] = first; 					    // mark the square with human's letter
					cur_score = max_box(a);					// obtain the score for this square
					if (cur_score < worst)				    // if this score is lesser
						worst = cur_score;					// this score is the worst score
                    a[i][j] = blank;						// Unmark the square
				}
			}
		}
		return worst;										// return the worst possible score from this state of the board
	}
	void game(int c)
	{
		int i,j;
		bool gameover = false;								// game not yet over
		while(!gameover)								    // while game not yet over
		{
			printboard();									// print the current board
			if (c == 1)										// if Human's turn
			{
				cout << "\n\nYour turn:  ";
				cin >> i >> j;								// input box index
				yay:
				if (i < n && j < n && a[i][j] == blank)		// check for validity of the inputted choice of square
				{
					a[i][j] = first;
					c = !c;
					system("cls");
				}
				else
				{
					cout << "What the hell are you doing? Do it again and I will end your little game. -_- \n";
					cout << "\n\nYour turn:  ";
					cin >> i >> j;
					if (i >= n || j >= n)
						return;
					else goto yay;
				}
			}
			else										// Machine's turn then!
			{
			    system("cls");
                choose_best_box(a);
				c = !c;
				system("cls");
				cout << "Now,this is my move.\n\n";
			}
			gameover = endgame(a);					// check if game's over or not.
		}
		system("cls");
		bool win_lose = checkforvictory(a);			// win_lose = 1 if any player wins.
		if(win_lose == false)						//          = 0 if it's a draw.
            result(-1);
		else result(!c);							// print the result of the game
	}
};
int main()
{
	int choice;   																// one-player or two player
	cout << "\t\t\t Welcome to the Tic tac toe game!! \n\n ";
	cout << "1. Play against a dufus \n 2. Play against the machine\n\n";
	cin >> choice;
	system("cls");
	if (choice == 1)															// choice = 1 => two-player mode
	{
		twoplayer obj;
		obj.choose_the_first();
	}
	else
	{
		oneplayer o;															// else one-player mode
		o.choose_the_first();
	}
	system("PAUSE");
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\t\t\tCreated By Prajwal\n\n\n\n\n\n";				// Credits :P
	system("PAUSE");
	return 0;
}
