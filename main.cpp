// 01.04.2017
// https://www.cyberforum.ru/cpp-beginners/thread1950533.html#post10284148
// ���� "��������"
// ���������� ���������

#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <conio.h>

using std::vector;
using std::cout;

const int SIZE = 4; // ������ �������� ����

vector<int> in_game_map(SIZE); 
vector<vector<int>> game_map(SIZE, in_game_map); // ������� �����

vector<int> in_right_map(SIZE); 
vector<vector<int>> right_map(SIZE, in_right_map); // ���������� �������� �����

struct coordinate // ��������� ��������� �������� ��������
{
	int x;
	int y;
} zero; // ������

void create_right_map() // ������� ���������� ����� ���������� �� �������
{
	int right_value = 1;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			right_map[i][j] = right_value++;
	}
	right_map[SIZE-1][SIZE-1] = 0; // ������� ������� � ������ ������ ����
}

void create_game_map() // �������� ������� ������� �����
{
	int limit = SIZE*SIZE;
	vector<int> temporary; // ��������� ������ �� �������� ����� ����� �������� � ������� �����
	for (int i = 0; i < limit; i++)
		temporary.push_back(i);

	int value;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			value = rand() % limit--;
			game_map[i][j] = temporary[value];
			if (temporary[value] == 0) // ��������� ���������� �������� ��������
			{
				zero.x = j;
				zero.y = i;
			}
			temporary.erase(temporary.begin() + value); // ������� ��� �������������� �����
		}
	}
}

bool check_map() // ��������� ������� � ���������� ����� ��� ����������� ����� ����
{
	if (game_map == right_map)
		return true;
	return false;
}

void move() // ��� ������
{
	int arrow = static_cast<int> (_getch()); // UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75
	switch (arrow)
	{
		case 72: // ��� ����� (������� ������� ����)
		{
			if (zero.y < SIZE - 1)
			{
				game_map[zero.y][zero.x] = game_map[zero.y + 1][zero.x];
				zero.y++;
				game_map[zero.y][zero.x] = 0;
			}
			break;
		}
		case 80: // ��� ���� (������� ������� �����)
		{
			if (zero.y > 0)
			{
				game_map[zero.y][zero.x] = game_map[zero.y - 1][zero.x];
				zero.y--;
				game_map[zero.y][zero.x] = 0;
			}
			break;
		}
		case 77: // ��� ������ (������� ������� �����)
		{
			if (zero.x > 0)
			{
				game_map[zero.y][zero.x] = game_map[zero.y][zero.x - 1];
				zero.x--;
				game_map[zero.y][zero.x] = 0;
			}
			break;
		}
		case 75: // ��� ����� (������� ������� ������)
		{
			if (zero.x < SIZE - 1)
			{
				game_map[zero.y][zero.x] = game_map[zero.y][zero.x + 1];
				zero.x++;
				game_map[zero.y][zero.x] = 0;
			}
			break;
		}
		default:
		{
			move();
		}
	}
}

void screen() // ������� ������ �� �����
{
	system("cls");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (game_map[i][j] != 0)
				cout << std::setw(2) << std::setfill('0') << game_map[i][j] << ' ';
			else
				cout << "   "; // ������� �������
		}
		cout << '\n';
	}
}

int main()
{
	srand(static_cast<int>(time(NULL)));
	
	create_right_map(); // �������� ������� ����
	do
	{
		create_game_map();
	} while (check_map());
	
	do // ������� ����
	{
		screen();
		move();
	}
	while (!check_map());

	screen();
	cout << "\nYou win!\nGame over!\n";
	_getch();
}