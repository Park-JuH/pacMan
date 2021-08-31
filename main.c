#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <process.h>

struct Ghost
{
	int x;
	int y;
};
void cursor_view(int s)      // 0넣으면숨기기, 1넣으면보이기

{

	HANDLE hConsole;

	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = s;

	ConsoleCursor.dwSize = 2;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);

}

void gotoxy(int x, int y)

{
	COORD pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

int main()
{
	system("mode con lines=34 cols=80");
	struct Ghost ghost[3];
	cursor_view(0);

	char map_xy[33][54] = { "111111111111111111111111111111111111111111111111111111",
						"110900090009000900090009011110900090009000900090009011",
						"110111111110111111111111011110111111111111011111111011",
						"110111111110111111111111011110111111111111011111111211",
						"110090009000970090009000900090009000900090009000900011",
						"110111111110111101111111111111111111101111011111111011",
						"110111111110111101111111111111111111101111011111111011",
						"119000900090111100900090011119000900091111009000900011",
						"111111011110111111111111011110111111111111011110111111",
						"111111011110111111111111011110111111111111011110111111",
						"111111011110111100090009000900090009011111011110111111",
						"111111700900111101111111110111111111011111009000111111",
						"111111011110111191110000000000000011911111011110111111",
						"111111011110090001110000000000000011000090011110111111",
						"111111000900111101111111111111111111011111090009111111",
						"111111011110111100900900009000009000011111011110111111",
						"111111000900090001111111111111111111000000000900111111",
						"111111111011111111111111111111111111111111110111111111",
						"110009000900090009000900000009000900000009000900090011",
						"110111111111111111111101111111101111111111111111111011",
						"110090000000901111111101111111101111111110900000009011",
						"110111111011100900000009000000000000000900111011111011",
						"110111111011101111111111111111111111111110111011111011",
						"110009000090001111111111111111111111111110009000200011",
						"111111111111101111111111111111111111111110111111111111",
						"110000000200000900000009000000090000000900000000900011",
						"111111111111011110111101111111111011110111101111111111",
						"111111111111011110111101111111111011110111101111111111",
						"119000900009000900111100009000090011110900009000900011",
						"110111111111111111111111111011111111111111111111111011",
						"110111111111111111111111111011111111111111111111111011",
						"110090009000000900090000000900090009000900000009000011",
						"111111111111111111111111111111111111111111111111111111" };


	int x = 2, y = 2, over = 1, coin_total = 0, coin = 0, count, over_count = 0;
	char key_value = 'd';
	int x_bf, y_bf, i = 0, j = 0, change = 0, change_ct = 0, ghost_timer = 0, jump = 0;
	clock_t start, end, ghost_start, ghost_end; //특정한 것을 먹을경우 고스트를 먹을 수 있음
	srand(time(NULL));
	int ghost_bf_x[3], ghost_bf_y[3];
	while (i < 33)
	{
		j = 0;
		while (j < 54)
		{
			if (map_xy[i][j] == '1')
				printf("1");
			else if (map_xy[i][j] == '2')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("@");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (map_xy[i][j] == '0')
				printf(" ");
			else if (map_xy[i][j] == '9')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				printf("$");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else if (map_xy[i][j] == '7')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf("*");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			j++;
		}
		printf("\n");
		i++;
	}

	while (1)
	{
		i = 0, j = 0;
		if (_kbhit())
		{
			key_value = _getch();
			switch (key_value)
			{
			case 'w':
				if (map_xy[x - 1][y] != '1')
				{
					x--;
				}
				break;
			case 's':
				if (map_xy[x + 1][y] != '1')
				{
					x++;
				}
				break;
			case 'a':
				if (map_xy[x][y - 1] != '1')
				{
					y--;
				}
				break;
			case 'd':
				if (map_xy[x][y + 1] != '1')
				{
					y++;
				}
				break;
			}
		}
		else
		{
			switch (key_value)
			{
			case 'w':
				if (map_xy[x - 1][y] != '1')
				{
					x--;
				}
				break;
			case 's':
				if (map_xy[x + 1][y] != '1')
				{
					x++;
				}
				break;
			case 'a':
				if (map_xy[x][y - 1] != '1')
				{
					y--;
				}
				break;
			case 'd':
				if (map_xy[x][y + 1] != '1')
				{
					y++;
				}
				break;
			}
		}

		int ghost_i = 0, ghost_j = 0;

		if (jump == 1)
		{
			while (i < 33)
			{
				j = 0;
				while (j < 54)
				{
					if (map_xy[i][j] == '2')
					{
						if (change == 1)
						{
							end = clock();
							if (end - start < 15000)
							{
								for (int k = 0; k < 3; k++)
								{
									gotoxy(ghost_bf_y[k], ghost_bf_x[k]);
									printf(" ");
								}
								ghost[ghost_i].x = i;
								ghost[ghost_j].y = j;
								ghost_i++;
								ghost_j++;
								gotoxy(j, i);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
								printf("#");
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
							}
							else
								change = 0;
						}
						else
						{
							for (int k = 0; k < 3; k++)
							{
								gotoxy(ghost_bf_y[k], ghost_bf_x[k]);
								printf(" ");
							}
							ghost[ghost_i].x = i;
							ghost[ghost_j].y = j;
							ghost_i++;
							ghost_j++;
							gotoxy(j, i);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
							printf("@");
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						}
					}
					j = j + 1;
				}
				printf("\n");
				i++;
			}
		}
		else
		{
			while (i < 33)
			{
				j = 0;
				while (j < 54)
				{
					if (map_xy[i][j] == '2')
					{
						if (change == 1)
						{
							end = clock();
							if (end - start < 15000)
							{
								for (int k = 0; k < 3; k++)
								{
									gotoxy(ghost_bf_y[k], ghost_bf_x[k]);
									printf(" ");
								}
								ghost[ghost_i].x = i;
								ghost[ghost_j].y = j;
								ghost_i++;
								ghost_j++;
							}
							else
								change = 0;
						}
						else
						{
							ghost[ghost_i].x = i;
							ghost[ghost_j].y = j;
							ghost_i++;
							ghost_j++;
						}
					}
					j = j + 1;
				}
				i++;
			}
			jump = 1;
		}

		if (map_xy[x][y] == '7') //특별 스코어
		{
			map_xy[x][y] = '0';
			change = 1;
			start = clock();
		}
		if (map_xy[x][y] == '2')   //게임 끝내기
		{
			if (change == 1)
			{
				coin_total = coin_total + 500;
				map_xy[x][y] = '0';
				map_xy[10][26] = '2';
				if (change_ct == 0)
				{
					ghost[0].x = 10;
					ghost[0].y = 26;
					change_ct++;
				}
				else if (change_ct == 1)
				{
					ghost[1].x = 10;
					ghost[1].y = 26;
					change_ct++;
				}
				if (change_ct == 2)
				{
					ghost[2].x = 10;
					ghost[2].y = 26;
					change_ct = 0;
				}
			}
			else
			{
				gotoxy(62, 1);
				printf("Game Over\n");
				gotoxy(62, 2);
				printf("Score: %d", coin_total);
				return 0;
			}
		}

		if (key_value == 'w')
		{
			gotoxy(y, x + 1);
			printf(" ");
			gotoxy(y, x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("c");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (map_xy[x][y + 1] == '1')
			{
				gotoxy(y + 1, x);
				printf("1");
			}
			if (map_xy[x][y - 1] == '1')
			{
				gotoxy(y - 1, x);
				printf("1");
			}
			if (map_xy[x + 1][y] == '1')
			{
				gotoxy(y, x + 1);
				printf("1");
			}
			if (map_xy[x - 1][y] == '1')
			{
				gotoxy(y, x - 1);
				printf("1");
			}
		}
		else if (key_value == 'd')
		{
			gotoxy(y - 1, x);
			printf(" ");
			gotoxy(y, x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("c");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (map_xy[x][y + 1] == '1')
			{
				gotoxy(y + 1, x);
				printf("1");
			}
			if (map_xy[x][y - 1] == '1')
			{
				gotoxy(y - 1, x);
				printf("1");
			}
			if (map_xy[x + 1][y] == '1')
			{
				gotoxy(y, x + 1);
				printf("1");
			}
			if (map_xy[x - 1][y] == '1')
			{
				gotoxy(y, x - 1);
				printf("1");
			}
		}
		else if (key_value == 'a')
		{
			gotoxy(y + 1, x);
			printf(" ");
			gotoxy(y, x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("c");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (map_xy[x][y + 1] == '1')
			{
				gotoxy(y + 1, x);
				printf("1");
			}
			if (map_xy[x][y - 1] == '1')
			{
				gotoxy(y - 1, x);
				printf("1");
			}
			if (map_xy[x + 1][y] == '1')
			{
				gotoxy(y, x + 1);
				printf("1");
			}
			if (map_xy[x - 1][y] == '1')
			{
				gotoxy(y, x - 1);
				printf("1");
			}
		}
		else
		{
			gotoxy(y, x - 1);
			printf(" ");
			gotoxy(y, x);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("c");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			if (map_xy[x][y + 1] == '1')
			{
				gotoxy(y + 1, x);
				printf("1");
			}
			if (map_xy[x][y - 1] == '1')
			{
				gotoxy(y - 1, x);
				printf("1");
			}
			if (map_xy[x + 1][y] == '1')
			{
				gotoxy(y, x + 1);
				printf("1");
			}
			if (map_xy[x - 1][y] == '1')
			{
				gotoxy(y, x - 1);
				printf("1");
			}
		}
		if (map_xy[x][y] == '9')
		{
			coin_total = coin_total + 100;
			map_xy[x][y] = '0';
			gotoxy(y, x);
			printf(" ");
			over_count++;
		}
		gotoxy(62, 2);
		printf("SCORE: %d", coin_total);
		if (over_count == 98)
		{
			gotoxy(62, 1);
			printf("Clear!!\n");
			gotoxy(62, 2);
			printf("Score: %d", coin_total);
			return 0;
		}

		Sleep(200);

		ghost_j = 0;
		int ghost_ct = 0, move[3] = { 0. };
		for (ghost_i = 0; ghost_i < 3; ghost_i++)
		{
			count = rand() % 4 + 1;
			if (count == 1)
			{
				if (map_xy[ghost[ghost_i].x + 1][ghost[ghost_j].y] == '0')
				{
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y] = '0';
					ghost_bf_x[ghost_i] = ghost[ghost_i].x;
					ghost_bf_y[ghost_i] = ghost[ghost_j].y;
					map_xy[ghost[ghost_i].x + 1][ghost[ghost_j].y] = '2';
					move[ghost_i] = 1;
				}
				else if (map_xy[ghost[ghost_i].x + 1][ghost[ghost_j].y] == '9')
				{
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y] = '0';
					ghost_bf_x[ghost_i] = ghost[ghost_i].x;
					ghost_bf_y[ghost_i] = ghost[ghost_j].y;
					map_xy[ghost[ghost_i].x + 2][ghost[ghost_j].y] = '2';
					move[ghost_i] = 1;
				}
			}
			else if (count == 2)
			{
				if (map_xy[ghost[ghost_i].x][ghost[ghost_j].y - 1] == '0')
				{
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y] = '0';
					ghost_bf_x[ghost_i] = ghost[ghost_i].x;
					ghost_bf_y[ghost_i] = ghost[ghost_j].y;
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y - 1] = '2';
					move[ghost_i] = 1;
				}
				else if (map_xy[ghost[ghost_i].x][ghost[ghost_j].y - 1] == '9')
				{
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y] = '0';
					ghost_bf_x[ghost_i] = ghost[ghost_i].x;
					ghost_bf_y[ghost_i] = ghost[ghost_j].y;
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y - 2] = '2';
					move[ghost_i] = 1;
				}
			}
			else if (count == 3)
			{
				if (map_xy[ghost[ghost_i].x - 1][ghost[ghost_j].y] == '0')
				{
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y] = '0';
					ghost_bf_x[ghost_i] = ghost[ghost_i].x;
					ghost_bf_y[ghost_i] = ghost[ghost_j].y;
					map_xy[ghost[ghost_i].x - 1][ghost[ghost_j].y] = '2';
					move[ghost_i] = 1;
				}
				else if (map_xy[ghost[ghost_i].x - 1][ghost[ghost_j].y] == '9')
				{
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y] = '0';
					ghost_bf_x[ghost_i] = ghost[ghost_i].x;
					ghost_bf_y[ghost_i] = ghost[ghost_j].y;
					map_xy[ghost[ghost_i].x - 2][ghost[ghost_j].y] = '2';
					move[ghost_i] = 1;
				}
			}
			else if (count == 4)
			{
				if (map_xy[ghost[ghost_i].x][ghost[ghost_j].y + 1] == '0')
				{
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y] = '0';
					ghost_bf_x[ghost_i] = ghost[ghost_i].x;
					ghost_bf_y[ghost_i] = ghost[ghost_j].y;
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y + 1] = '2';
					move[ghost_i] = 1;
				}
				else if (map_xy[ghost[ghost_i].x][ghost[ghost_j].y + 1] == '9')
				{
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y] = '0';
					ghost_bf_x[ghost_i] = ghost[ghost_i].x;
					ghost_bf_y[ghost_i] = ghost[ghost_j].y;
					map_xy[ghost[ghost_i].x][ghost[ghost_j].y + 2] = '2';
					move[ghost_i] = 1;
				}
			}
			if (move[ghost_i] == 0)
			{
				ghost_i--;
				ghost_j--;
			}
			ghost_j++;
		}
	}
}