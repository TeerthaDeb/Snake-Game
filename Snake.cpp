/**
	AUTHOR 		:	MAHARAJ TEERTHA DEB
	STOP_STALK 	:	stopstalk.com/user/profile/Teertha_Deb
	GitHub		:	github.com/TeerthaDeb
**/


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

class player
{
private:
	char name[50];
	unsigned long long int score = 0;
	//friend bool compare_players(player , player); /* not gonna use it again */
public:
	player()
	{
	}
	~player()
	{
	}

	//setters:

	void set_score(long long int player_score)
	{
		score = player_score;
	}
	void set_name(string player_name)
	{
		strcpy(name , player_name.c_str());
	}

	//getters:

	string get_name()
	{
		return name;
	}
	unsigned long long int get_score()
	{
		return score;
	}
	bool is_greater(const player b)
	{
		return (this -> score > b.score);
	}
};


bool compare_players(player a, player b)
{
	return a.is_greater(b);
}

void gxy(short col, short row)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = {col, row};
	SetConsoleCursorPosition(h, position);
}

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

void high_score()
{
	vector<player> players;
	player temp;
	const char* dirname = "C:\\Users\\Public\\Documents\\TDsoftwares\\Snake_Game";
	if (mkdir(dirname) == -1){
		if(errno != 17){
			gxy(10 , 6) , printf("Mail teertha.deb579@gmail.com with the errorcode: ");cout<<errno;
			exit(0);
		}
	}
	fstream file_ptr;
	file_ptr.open("C:\\Users\\Public\\Documents\\TDsoftwares\\Snake_Game\\Score.MTD" , ios::in);
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
		for (int i = 0; i < 10; i++)
		{
			file_ptr.read((char*) &temp , sizeof(temp));
			players.push_back(temp);
		}
	}
	file_ptr.close();
	setcolor(01);
	gxy(5, 5);
	printf("Enter current player's name : ");
	cin.getline(current_player_name, 50);
	temp.set_name(current_player_name);
	temp.set_score(current_player_score);
	players.push_back(temp);
	sort(players.begin(), players.end(), compare_players);
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

void takeinput()
{
	if (_kbhit())
	{
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
		if ((ch == 'w' && cch == 's') || (ch == 's' && cch == 'w') || (ch == 'a' && cch == 'd') || (ch == 'd' && cch == 'a'))
			;
		else if (cch == 'w' || cch == 'a' || cch == 's' || cch == 'd')
			ch = cch;
	}
	while (cch == 'p')
	{
		if (_kbhit())
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

void eraser()
{
	tch = snake[tx][ty];
	snake[tx][ty] = '.';
}

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


void special_food()
{
/**
	* @brief : 	This function is called when user has a score that is divisible by 10
				A special fool will be generated for 10 seconds and if user can get it score will be increased by 5
 	* @return (void)
*/
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


void special_food_eaten()
{
/***
 *** @brief :  	This function is called when special food is eaten.
				the score will be increased by 5;
				the special food count down will be gone from the screen.
 *** @return: 	NONE
***/
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
	{
		clr;
		setcolor(70);
		gxy(width / 2 - 15 , height / 2 - 5);
		printf("Snake game 3.0.0 <June , 2023>");
		Sleep(1500);
		setcolor(int(rand() % 19));
		gxy(width / 2 - 7 , height / 2 - 4);
		printf("Designed by:    \n\t\t\t\t\t\tMaharaj Teertha Deb");
		Sleep(5000);
	}

    clr;
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
	clr;
	snake[tx][y + 1] = 'w';
	snake[tx][y + 2] = 'w';
	clr;
	setcolor(02);
	drawboard();
	setcolor(15);
	while (!gameover)
	{

		takeinput();
		place_xy_in_snake();
		replacexy();
		game_over();
		if (x == fx && y == fy)
		{
			food();
		}
		else
		{
			position_eraser();
			eraser();
		}
		if(special_food_generated == false and generate_special_food_again == true and current_player_score % 10 == 0 and  current_player_score > 0){
			special_food();
		}
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
		print_everything();
		Sleep(slow_down - current_player_score*2);
	}
	Sleep(700);
	clr;
	drawboard();
	gxy(width / 2 - 5, height / 2 - 3);
	setcolor(16);
	printf("!!! Game Over !!!");
	gxy(width / 2 - 5, height / 2);
	printf("!!! Score = %u !!!", current_player_score);
	Sleep(1500);
	clr;
	high_score();
	Sleep(3500);
	setcolor(02);
	gxy(width / 2 - 8, height / 2 + 5);
	printf("press any key to exit...\b");
	getch();
	Sleep(1000);
	gxy(24, height + 1);
	return 0;
}
