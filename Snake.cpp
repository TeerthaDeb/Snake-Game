/**
	AUTHOR 		:	MAHARAJ TEERTHA DEB
	STOP_STALK 	:	stopstalk.com/user/profile/Teertha_Deb
	GitHub		:	github.com/TeerthaDeb
**/


#include "Player.h"
#include <bits/stdc++.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
#define clr system("cls")
#define body printf("*")
#define head printf("O")
int width = 119, height = 28, fx = width / 2 - 10, fy = height / 2 - 5, x = width / 2, y = height / 2, tx = x, ty = y + 3, slow_down = 100 , sfx, sfy , special_food_count_down , loop_count;
unsigned long long int current_player_score = 0;
char ch = 'w', snake[115][30] = {'.'}, tch = 'w', cch , current_player_name[50];
bool  gameover = 0 , special_food_generated = false , generate_special_food_again = false;

/**
 * The function compares two players and returns true if the first player is greater than the second
 * player.
 *
 * @param a The first player object to compare.
 * @param b The parameter "b" is a player object that is being compared to another player object "a".
 *
 * @return a boolean value.
 */
bool compare_players(player a, player b)
{
	return a.is_greater(b);
}

/**
 * The function `gxy` sets the cursor position in the console window to the specified column and row.
 *
 * @param col The "col" parameter represents the column position in the console window where you want
 * 				to move the cursor to. It is of type "short", which means it can hold integer values from -32,768 to
 *				32,767.
 * @param row The "row" parameter represents the vertical position of the cursor on the console screen.
 * 				It specifies the row number where you want to move the cursor to.
 */
void gxy(short col, short row)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {col, row};
	SetConsoleCursorPosition(h, position);
}

/**
 * The function "setcolor" is used to change the text color in the console output in C++.
 * 
 * @param ForgC The parameter "ForgC" is an integer that represents the foreground color. It is used to
 * 				set the text color in the console.
 */
void setcolor(int ForgC)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

/**
 * @brief The function "drawboard" is used to draw a game board with specific dimensions and display controls
 * 			for the game.
 * 
 */
void drawboard()
{
	int i, j;
	gxy(0, 0);
	printf("%c", 201);
	for (i = 0; i < width - 1; i++)
		printf("%c", 205);
	printf("%c", 187);
	for (i = 0; i < height; i++)
	{
		gxy(0, i + 1);
		printf("%c", 186);
		gxy(width, i + 1);
		printf("%c", 186);
	}
	gxy(0, height - 3);
	printf("%c", 204);
	for (i = 0; i < width - 1; i++)
	{
		printf("%c", 205 - (i == width / 2 - 4) * 2);
	}
	printf("%c", 185);
	gxy(width / 2 - 3, height - 2);
	printf("%c w=%c a=%c s=%c d=%c", 186, 94, 60, 251, 62);
	gxy(0, height + 1);
	printf("%c", 200);
	for (i = 0; i < width - 1; i++)
		printf("%c", 205 - (i == width / 2 - 4) * 3);
	printf("%c", 188);
	gxy(width / 2 - 3, height - 1);
	printf("%c p=pause", 186);
	gxy(width / 2 - 3, height);
	printf("%c x=exit", 186);
}


/**
 * @brief The function "high_score" manages the high scores of players in a game by reading and writing data
 * 			to a file, sorting the scores, and displaying them on the console.
 */
void high_score()
{
	vector<player> players;
	player temp;
	const char* dirname = "C:\\Users\\Public\\Documents\\TDsoftwares\\Snake_Game";

	/* The code is checking if a directory with the name specified in the variable "dirname" already
	exists. If the directory does not exist, it attempts to create the directory using the mkdir
	function. If the mkdir function returns -1, it checks if the error code is not equal to 17. If the
	error code is not equal to 17, it prints an error message and exits the program. */
	if (mkdir(dirname) == -1){
		if(errno != 17){
			gxy(10 , 6) , printf("Mail teertha.deb579@gmail.com with the errorcode: ");cout<<errno;
			exit(0);
		}
	}
	fstream file_ptr;
	file_ptr.open("C:\\Users\\Public\\Documents\\TDsoftwares\\Snake_Game\\Score.MTD" , ios::in);

	/* The code is checking if the file pointer "file_ptr" is null. If it is null, it creates a new
	object "temp" of type "Player" and sets its name to "Teertha Deb". Then, it enters a loop from 1 to
	8 and sets the score of "temp" to the current loop iteration. It then adds "temp" to the "players"
	vector. Finally, it sets the score of "temp" to 100 and adds it to the "players" vector again. */
	if(!file_ptr){
	    temp.set_name("Teertha Deb");
		for(long long int i = 1 ; i<9 ; i++){
			temp.set_score(i);
			players.push_back(temp);
		}
        temp.set_score(100);
        players.push_back(temp);
	}
	else
	{
		/* The code is reading data from a file and storing it in a vector called "players". It is
		using a for loop to iterate 10 times. In each iteration, it reads the data from the file using the
		read() function and stores it in a temporary variable called "temp". Then, it adds the value of
		"temp" to the end of the "players" vector using the push_back() function. */
		for (int i = 0; i < 10; i++)
		{
			file_ptr.read((char*) &temp , sizeof(temp));
			players.push_back(temp);
		}
	}
	/* The code is closing a file pointer. */
	file_ptr.close();

	/* The code is setting the color of the console output to a specific value. It then prompts the
	user to enter the current player's name and reads it into the variable "current_player_name". It
	creates an object of a class called "temp" and sets its name and score using the values entered by
	the user. Finally, it adds the "temp" object to a vector called "players". */
	setcolor(01);
	gxy(5, 5);
	printf("Enter current player's name : ");
	cin.getline(current_player_name, 50);
	temp.set_name(current_player_name);
	temp.set_score(current_player_score);
	players.push_back(temp);

	/* Sorting players according to their score */
	sort(players.begin(), players.end(), compare_players);

	/* The code is opening a file named "Score.MTD" in write mode at the specified file path. It
	then clears the screen and sets the color to green. It calls a function "drawboard()" to draw a
	game board. */
	file_ptr.open("C:\\Users\\Public\\Documents\\TDsoftwares\\Snake_Game\\Score.MTD" , ios::out);
	clr;
	setcolor(10);
	drawboard();
	for (int i = 0; i < 10; i++)
	{
		file_ptr.write((char *)(&players[i]), sizeof(players[i]));
		gxy(2, i + 2);
		printf("Rank=%3d | name=%35s | score=%5u", i + 1, players[i].get_name().c_str() , players[i].get_score());
		cout << '\n';
	}
	file_ptr.close();
}

/**
 * @brief The function `takeinput()` checks for user input and assigns the corresponding direction to the
 *			 variable `ch`.
 */
void takeinput()
{
	/* The code is checking for user input using the `_kbhit()` function. If the user inputs 'x',
	the variable `gameover` is set to 1, indicating that the game should end. Otherwise, it checks for
	arrow key inputs or their corresponding numeric keypad inputs. If the user inputs the up arrow key
	or '8', the variable `cch` is set to 'w'. If the user inputs the down arrow key or '2', `cch` is
	set to 's'. If the user inputs the left arrow key or '4', `cch` is */
	if (_kbhit())
	{
		/* The code is checking for user input using the `getch()` function. If the user inputs 'x',
		the variable `gameover` is set to 1, indicating that the game should end. Otherwise, it checks for
		arrow key inputs or their corresponding numeric keypad inputs. If the user inputs the up arrow key
		or '8', the variable `cch` is set to 'w'. If the user inputs the down arrow key or '2', `cch` is
		set to 's'. If the user inputs the left arrow key or '4', `cch` is */
		cch = getch();
		if (cch == 'x')
			gameover = 1;
		else
		{
			if (cch == 72 || cch == '8')
				cch = 'w';
			else if (cch == 80 || cch == '2')
				cch = 's';
			else if (cch == 75 || cch == '4')
				cch = 'a';
			else if (cch == 77 || cch == '6')
				cch = 'd';
		}
		/* The code is checking the values of two variables, `ch` and `cch`, and determining if they
		represent opposite directions (e.g. 'w' and 's', 'a' and 'd'). If they do, then no action is
		taken. If `cch` represents a valid direction ('w', 'a', 's', or 'd'), then its value is assigned
		to `ch`. */
		if ((ch == 'w' && cch == 's') || (ch == 's' && cch == 'w') || (ch == 'a' && cch == 'd') || (ch == 'd' && cch == 'a'))
			/* No need to do anything*/	; 
		else if (cch == 'w' || cch == 'a' || cch == 's' || cch == 'd')
			ch = cch;
	}

	while (cch == 'p') // Logic to pause the game
	{
		if (_kbhit()) // If any directional key is pressed, the game continues;
		{
			cch = getch();
			if (cch == 72 || cch == '8')
				cch = 'w';
			else if (cch == 80 || cch == '2')
				cch = 's';
			else if (cch == 75 || cch == '4')
				cch = 'a';
			else if (cch == 77 || cch == '6')
				cch = 'd';
			if ((ch == 'w' && cch == 's') || (ch == 's' && cch == 'w') || (ch == 'a' && cch == 'd') || (ch == 'd' && cch == 'a'))
				;
			else if (cch == 'w' || cch == 'a' || cch == 's' || cch == 'd')
				ch = cch;
			else
				cch = 'p';
		}
	}
}

/**
 * @brief function updates the position of the snake based on the user's input.
 */
void place_xy_in_snake()
{
	if (ch == 'w')
	{
		y--, snake[x][y + 1] = 'w';
	}
	else if (ch == 'a')
	{
		x--, snake[x + 1][y] = 'a';
	}
	else if (ch == 's')
	{
		y++, snake[x][y - 1] = 's';
	}
	else if (ch == 'd')
	{
		x++, snake[x - 1][y] = 'd';
	}
}

/**
 * The function replacexy ensures that the values of x and y are within certain bounds.
 */
void replacexy()
{
	if (x > width - 1)
		x = 1;
	else if (x < 1)
		x = width - 1;
	if (y > height - 4)
		y = 1;
	else if (y < 1)
		y = height - 4;
}

/**
 * ****** Only for Debugging purpose
 * 
 * @brief The function "print_everything" is responsible for printing the game elements on the screen, such as
 * 			the snake's head and body, as well as the food.
 */
void print_everything()
{
	setcolor(07);
	if (ch == 'w')
	{
		gxy(x, y);
		head;
		if (y != height - 4)
		{
			gxy(x, y + 1);
			body;
		}
		else
		{
			gxy(x, 1);
			body;
		}
	}
	else if (ch == 's')
	{
		gxy(x, y);
		head;
		if (y != 1)
		{
			gxy(x, y - 1);
			body;
		}
		else
		{
			gxy(x, height - 4);
			body;
		}
	}
	else if (ch == 'a')
	{
		gxy(x, y);
		head;
		if (x != width - 1)
		{
			gxy(x + 1, y);
			body;
		}
		else
		{
			gxy(1, y);
			body;
		}
	}
	else if (ch == 'd')
	{
		gxy(x, y);
		head;
		if (x != 1)
		{
			gxy(x - 1, y);
			body;
		}
		else
		{
			gxy(width - 1, y);
			body;
		}
	}
	gxy(tx, ty);
	printf(" ");
	gxy(fx, fy);
	setcolor(17);
	printf("%c", 237);
	//Need to take the beeping pointer to the end of the terminal, so it does not beep after the food.
	gxy(width , height+1); printf("");
}

/**
 * @brief function "position_eraser" updates the position of an eraser based on the position left by the snake
 */
void position_eraser()
{
	if (tch == 'w')
		ty--;
	else if (tch == 'a')
		tx--;
	else if (tch == 's')
		ty++;
	else if (tch == 'd')
		tx++;
	if (tx > width - 1)
		tx = 1;
	else if (tx < 1)
		tx = width - 1;
	if (ty > height - 4)
		ty = 1;
	else if (ty < 1)
		ty = height - 4;
}

/**
 * @brief eraser function replaces the character at the specified position in the snake array with a
 *		 period.
 */
void eraser()
{
	tch = snake[tx][ty];
	snake[tx][ty] = '.';
}

/**
 * @brief function "food" generates a special food item on the game board and updates the player's score.
 */
void food()
{
	// gxy(x, y);
	// printf("0\a");
	generate_special_food_again = true;
	fx = rand() % width + 1;
	fy = rand() % (height - 4) + 1;
	while (snake[fx][fy] == 'w' || snake[fx][fy] == 'a' || snake[fx][fy] == 's' || snake[fx][fy] == 'd')
	{
		fx = rand() % width + 1;
		fy = rand() % (height - 4) + 1;
	}
	snake[fx][fy] = 'F';
	setcolor(07);
	gxy(2 , height - 2);
	printf("Score: %u", ++current_player_score);
}

/**
 * @brief : 	This function is called when user has a score that is divisible by 10
				A special fool will be generated for 10 seconds and if user can get it score will be increased by 5
*/
void special_food()
{

	loop_count = 0;
	special_food_generated = true;
	special_food_count_down = 50;
	sfx = rand() % width + 1;
	sfy = rand() % (height - 4) + 1;
	while (snake[sfx][sfy] == 'w' || snake[sfx][sfy] == 'a' || snake[sfx][sfy] == 's' || snake[sfx][sfy] == 'd' || snake[sfx][sfy] == 'F')
	{
		sfx = rand() % width + 1;
		sfy = rand() % (height - 4) + 1;
	}
	gxy(sfx , sfy);
	setcolor(01);
	generate_special_food_again = false;
	printf("&");//Print the special food.
}

/**
 * @brief The function updates the game state when a special food item is eaten by the player.
 */
void special_food_eaten()
{
	special_food_generated = false;
	special_food_count_down = 0;
	current_player_score += 5;
	gxy(sfx , sfy);
	printf("0");
	gxy(1 , height - 1);
	snake[sfx][sfy] = '.';
	printf("                                     ");
	setcolor(07);
	gxy(2 , height - 2);
	printf("Score: %u", ++current_player_score);
	generate_special_food_again = true;
}

/**
 * @brief The function "game_over" checks if the snake's position is on a specific character and sets the
 * 			gameover variable to 1 if true.
 */
void game_over()
{
	if (snake[x][y] == 'w' || snake[x][y] == 'a' || snake[x][y] == 's' || snake[x][y] == 'd')
	{
		gameover = 1;
	}
}

int main()
{
	SetConsoleTitle("                                                                                                                                      Snake Game");
	
	
	//Introduction.......
	/* The code is displaying a title and the name of the designer for a snake game. It sets the
	color of the text, positions it on the screen, and uses the Sleep function to pause the program for
	a certain amount of time before moving on to the next line of code. */
	{
		clr;
		setcolor(70);
		gxy(width / 2 - 15 , height / 2 - 5);
		printf("Snake game 3.1.0 <August , 2023>");
		Sleep(1500);
		setcolor(int(rand() % 19));
		gxy(width / 2 - 7 , height / 2 - 4);
		printf("Designed by:    \n\t\t\t\t\t\tMaharaj Teertha Deb");
		Sleep(5000);
	}
    clr;

    /* The code is a snippet of a C++ program. It appears to be a part of a larger program that
	involves drawing a board and taking user input to determine the Windows version. Because 
	Windows 7 and Windows 10 have different terminal size*/
	drawboard();
	gxy(10, 5), printf("enter your windows version: ");
	gxy(10, 7), printf("[1] windows 7 (or previous version)");
	gxy(10, 9), printf("[2] windows 10(or later version after 7)");
	gxy(11, 15), printf("Enter choice: (1/2) : ");
	char choice;
	choice = getch();
	if (choice == '1')
	{
		width = 79, height = 22, slow_down = 130;
	}
	snake[tx][y + 1] = 'w';
	snake[tx][y + 2] = 'w';
	clr;
	setcolor(02);
	drawboard();
	setcolor(15);
	/* The above code is part of a game loop in C++. It is continuously running until the gameover
	condition is met. Inside the loop, it takes user input, updates the position of the snake, checks
	if the snake has collided with any obstacles or itself, and handles the logic for generating and
	eating food and special food. It also updates the game screen, pausing the program for a certain
	amount of time before each iteration of the loop. */
	while (!gameover)
	{

		takeinput();
		place_xy_in_snake();
		replacexy();
		game_over();
		/* The code is checking if the variables `x` and `y` are equal to the variables `fx` and `fy`
		respectively. If they are equal, the function `food()` is called. */
		if (x == fx && y == fy)
		{
			food();
		}
		/* The above code is part of a C++ program. It is an "else" statement that is executed when a certain
		condition is not met. Inside the else block, there are two function calls: "position_eraser()" and
		"eraser()". These functions are likely responsible for positioning and using an eraser in some
		kind of graphical application or game. */
		else
		{
			position_eraser();
			eraser();
		}
		/* The above code is checking multiple conditions using an if statement. It checks if the variable
		special_food_generated is false, generate_special_food_again is true, the current_player_score is
		divisible by 10, and the current_player_score is greater than 0. If all these conditions are true,
		it calls the special_food() function. */
		if(special_food_generated == false and generate_special_food_again == true and current_player_score % 10 == 0 and  current_player_score > 0){
			special_food();
		}
		/* The above code is checking if a special food has been generated. If it has, it increments the loop
		count and decreases the special food countdown. It then checks if the special food has been eaten
		by comparing its coordinates with the current coordinates (x and y). If the special food has been
		eaten, it calls the special_food_eaten() function. If the special food countdown is still greater
		than 0, it prints a "|" character at a specific position on the screen. If the special food
		countdown reaches 0, it sets the special_food_generated flag to false, clears the special food
		from the screen*/
		if(special_food_generated){
			loop_count++;
			special_food_count_down--;
			if(sfx == x and sfy == y){
				special_food_eaten();
			}
			else if(special_food_count_down > 0){
				gxy(floor(loop_count*0.1) + 2, height - 1);
				printf("|");
			}
			if(special_food_count_down == 0){
				special_food_generated = false;
				gxy(sfx , sfy);
				printf(" ");
				gxy(1 , height - 1);
				snake[sfx][sfy] = '.';
				printf("                                     ");
			}
		}
		/* The above code is written in C++. It is calling a function named "print_everything()" and then
		using the "Sleep()" function to pause the program for a certain amount of time. The amount of time
		is calculated by subtracting the current player score multiplied by 2 from the "slow_down"
		variable. */
		print_everything();
		Sleep(slow_down - current_player_score*2);
	}
	Sleep(1700);
	clr;
	drawboard();
	gxy(width / 2 - 5, height / 2 - 3);
	setcolor(16);
	/* The above code is written in C++ and it is displaying the message "!!! Game Over !!!" on the
	console. It also displays the current player's score and waits for 1500 milliseconds before
	continuing execution. */
	printf("!!! Game Over !!!");
	gxy(width / 2 - 5, height / 2);
	printf("!!! Score = %u !!!", current_player_score);
	Sleep(1500);
	clr;
	high_score(); // To sort players
	Sleep(3500); 
	setcolor(02);
	gxy(width / 2 - 8, height / 2 + 5);
	printf("press any key to exit...\b"); // Exit Message
	getch();
	Sleep(1000);
	gxy(24, height + 1);
	return 0;
}
