#pragma once
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
class Kostka1
{
public:
	int pozycjaX;
	int pozycjaY;
	int size;
	char** orange;
	char** blue;
	char** red;
	char** green;
	char** yellow;
	char** white;
	char** pomocnicza;
	Kostka1(int a)
	{
		pozycjaX = 0;
		pozycjaY = 0;
		size = a;
		orange = new char* [size];
		blue = new char* [size];
		red = new char* [size];
		green = new char* [size];
		yellow = new char* [size];
		white = new char* [size];
		pomocnicza = new char* [size];
		for (int i = 0; i < size; i++)
		{
			orange[i] = new char[size];
			blue[i] = new char[size];
			red[i] = new char[size];
			green[i] = new char[size];
			yellow[i] = new char[size];
			white[i] = new char[size];
			pomocnicza[i] = new char[size];
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				orange[i][j] = 'o';
				blue[i][j] = 'b';
				green[i][j] = 'g';
				red[i][j] = 'r';
				white[i][j] = 'w';
				yellow[i][j] = 'y';
				pomocnicza[i][j] = 'q';
			}
		}

	}
	void losuj()
	{
		srand(time(NULL));
		int losowanko;
		for (int k = 0; k < 10000; k++)
		{
			losowanko = rand() % size;
			pozycjaX = losowanko;
			pozycjaY = losowanko;
			RuchX();
			RuchY();
		}
		pozycjaX = 0;
		pozycjaY = 0;

	}
	void RuchX()
	{
		for (int i = 0; i < size; i++)
		{
			pomocnicza[pozycjaX][i] = orange[pozycjaX][i];
			orange[pozycjaX][i] = blue[pozycjaX][i];
			blue[pozycjaX][i] = red[pozycjaX][i];
			red[pozycjaX][i] = green[pozycjaX][i];
			green[pozycjaX][i] = pomocnicza[pozycjaX][i];
		}
		//MAX lewo
		if (pozycjaX == 0)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					pomocnicza[i][j] = yellow[i][j];
				}
			}
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					yellow[i][j] = pomocnicza[size - 1 - j][i];

				}
			}
		}
		// MAX prawo
		if (pozycjaX == size - 1)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					pomocnicza[i][j] = white[i][j];
				}
			}
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					white[i][j] = pomocnicza[j][size - 1 - i];
				}
			}
		}
	}
	void RuchY()
	{
		for (int i = 0; i < size; i++)
		{
			pomocnicza[i][pozycjaY] = orange[i][pozycjaY];
			orange[i][pozycjaY] = white[i][pozycjaY];
			white[i][pozycjaY] = red[size - 1 - i][size - 1 - pozycjaY];
			red[size - 1 - i][size - 1 - pozycjaY] = yellow[i][pozycjaY];
			yellow[i][pozycjaY] = pomocnicza[i][pozycjaY];
		}
		//MAX lewo
		if (pozycjaY == 0)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					pomocnicza[i][j] = green[i][j];
				}
			}
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					green[i][j] = pomocnicza[j][size - 1 - i];
				}
			}
		}
		//MAX prawo
		if (pozycjaY == size - 1)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					pomocnicza[i][j] = blue[i][j];
				}
			}
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					blue[i][j] = pomocnicza[size - 1 - j][i];

				}
			}
		}
	}
	void RuchF()
	{
		//Front
		for (int i = 0; i < size; i++)
		{
			pomocnicza[i][size - 1] = green[i][size - 1];
			green[i][size - 1] = white[0][i];
			white[0][i] = blue[size - 1 - i][0];
			blue[size - 1 - i][0] = yellow[size - 1][size - 1 - i];
			yellow[size - 1][size - 1 - i] = pomocnicza[i][size - 1];
		}
		//obrot
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				pomocnicza[i][j] = orange[i][j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				orange[i][j] = pomocnicza[size - 1 - j][i];

			}
		}
	}
	void RuchB()
	{
		//BACK
		for (int i = 0; i < size; i++)
		{
			pomocnicza[i][size - 1] = blue[i][size - 1];
			blue[i][size - 1] = white[size - 1][size - 1 - i];
			white[size - 1][size - 1 - i] = green[size - 1 - i][0];
			green[size - 1 - i][0] = yellow[0][i];
			yellow[0][i] = pomocnicza[i][size - 1];
		}
		//obrot
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				pomocnicza[i][j] = red[i][j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				red[i][j] = pomocnicza[size - 1 - j][i];

			}
		}

	}
	void obrotkostkiR()
	{
		//obrot kostki w prawo
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				pomocnicza[i][j] = orange[i][j];
				orange[i][j] = green[i][j];
				green[i][j] = red[i][j];
				red[i][j] = blue[i][j];
				blue[i][j] = pomocnicza[i][j];
			}
		}

		//obrot
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				pomocnicza[i][j] = yellow[i][j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				yellow[i][j] = pomocnicza[j][size - 1 - i];

			}
		}
		//obrot
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				pomocnicza[i][j] = white[i][j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				white[i][j] = pomocnicza[size - 1 - j][i];

			}
		}
	}
	void obrotkostkiU()
	{
		//obrot kostki w gore
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				pomocnicza[i][j] = orange[i][j];
				orange[i][j] = white[i][j];
				white[i][j] = red[size - 1 - i][size - 1 - j];
				red[size - 1 - i][size - 1 - j] = yellow[i][j];
				yellow[i][j] = pomocnicza[i][j];
			}
		}
		//obrot prawej sciany
		//obrot
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				pomocnicza[i][j] = blue[i][j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				blue[i][j] = pomocnicza[size - 1 - j][i];

			}
		}
		//obrot
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				pomocnicza[i][j] = green[i][j];
			}
		}
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				green[i][j] = pomocnicza[j][size - 1 - i];

			}
		}
	}
	int check()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (orange[i][j] == orange[0][0] && green[i][j] == green[0][0] && blue[i][j] == blue[0][0] && red[i][j] == red[0][0] && white[i][j] == white[0][0] && yellow[i][j] == yellow[0][0])
				{
					if (i == size - 1 && j == size - 1)
					{
						return 9999;
					}
				}
				else return 0;
			}
		}
	}

};

