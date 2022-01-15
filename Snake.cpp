#include <bits/stdc++.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <vector>
using namespace std;
#define clr system("cls")
#define body printf("*")
#define head printf("O")
int width = 119, height = 28, fx = width / 2 - 10, fy = height / 2 - 5, x = width / 2, y = height / 2, gameover = 0, tx = x, ty = y + 3, slow_down = 100;
unsigned long long int current_player_score = 0;
char ch = 'w', snake[115][30] = {'.'}, tch = 'w', cch;
char current_player_name[50];

struct record
{
	char name[50];
	unsigned long long int score;
};

bool compare_players(record a, record b)
{
	return a.score > b.score;
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
	vector<record> player;
	record tmp;
	fstream file_ptr("score.txt", ios::in);
	if(!file_ptr){
        char tmp_name[15] = "Teertha Deb\0";
        strcpy(tmp.name, tmp_name);
		for(int i = 1 ; i<9 ; i++){
			tmp.score = i;
			player.push_back(tmp);
		}
        tmp.score = 100;
        player.push_back(tmp);
	}
	else
	{
		for (int i = 0; i < 10; i++)
		{
			file_ptr.read(reinterpret_cast<char *>(&tmp), sizeof(tmp));
			player.push_back(tmp);
		}
	}
	file_ptr.close();
	setcolor(01);
	gxy(5, 5);
	printf("Enter current player's name : ");
	cin.getline(current_player_name, 50);
	strcpy(tmp.name, current_player_name);
	tmp.score = current_player_score;
	player.push_back(tmp);
	sort(player.begin(), player.end(), compare_players);
	file_ptr.open("score.txt", ios::out);
	clr;
	setcolor(10);
	drawboard();
	for (int i = 0; i < 10; i++)
	{
		tmp = player[i];
		file_ptr.write(reinterpret_cast<char *>(&tmp), sizeof(tmp));
		gxy(2, i + 2);
		printf("Rank=%3d | name=%35s | score=%5u", i + 1, tmp.name, player[i].score);
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
	setcolor(14);
	gxy(fx, fy);
	printf("%c", 237);
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
	gxy(x, y);
	printf("0\a");
	fx = rand() % width + 1;
	fy = rand() % (height - 4) + 1;
	while (snake[fx][fy] == 'w' || snake[fx][fy] == 'a' || snake[fx][fy] == 's' || snake[fx][fy] == 'd')
	{
		fx = rand() % width + 1;
		fy = rand() % (height - 4) + 1;
	}
	gxy(2, height - 2);
	printf("Score=%u", ++current_player_score);
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
		print_everything();
		Sleep(slow_down - current_player_score);
	}
	Sleep(700);
	clr;
	drawboard();
	gxy(width / 2 - 5, height / 2 - 3);
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