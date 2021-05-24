#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <cmath>

using namespace std;

int height;
int width;
bool** cells;
bool** new_generation;
int count_of_alive_cells;
const char alive_cell = '*';
const char not_alive_cell = '-';

void create(int percent);
void show();
void calculation();

int main()
{
    int percent;
    int user_choise;
    cout << "input height" << endl;
    cin >> height;
    cout << "input width" << endl;
    cin >> width;
    cells = new bool* [height];
    for (int i = 0;i<height;i++)
    {
        cells[i] = new bool [width];
    }
    new_generation = new bool* [height];
    for (int i = 0;i<height;i++)
    {
        new_generation[i] = new bool [width];
    }
    cout << "input percent of alive cells u want?" << endl;
    cin >> percent;
    create(percent);
    show();
    cout << "Any int - start" << endl;
    cout << "0 - exit" << endl;
    cin >> user_choise;
    system("cls");
    while(user_choise!=0)
    {
        cout << "Any int - continue" << endl;
        cout << "0 - exit" << endl;
        calculation();
        show();
        cin >> user_choise;
        system("cls");
    }
    for (int i = 0;i<height;i++)
    {
        delete[] cells[i];
    }
    delete[] cells;
    for (int i = 0;i<height;i++)
    {
        delete[] new_generation[i];
    }
    delete[] new_generation;
    return 0;
}

void create(int percent)
{
   for (int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            cells[i][j] = (rand()%100 < percent);
            count_of_alive_cells += cells[i][j];
        }
    for (int i=0;i<height;i++)
        for(int j=0;j<width;j++)
        {
            new_generation[i][j] = FALSE;
        }
}

void show()
{
    cout << char(201) << setfill(char(205)) << setw (2*width+1) << char(187) << endl;
    for (int i=0;i<height;i++)
    {
        cout << char(186);
        for(int j=0;j<width;j++)
        {
            if (cells[i][j])
                cout << alive_cell<<" ";
            else
                cout << not_alive_cell << " ";
        }
        cout << char(186);
        cout << endl;
    }
    cout << char(200) << setfill(char(205)) << setw (2*width+1) << char(188) << endl;
}

void calculation()
{
    for (int i = 0;i<height;i++)
        for (int j = 0; j<width;j++)
        {
            int neighbours = 0;
            if ((i==0 && j==0) || (i==0 && j==width-1) || (i==height-1 && j==0) || (i==height-1 && j==width-1))
            {
               neighbours = cells[abs(i-1)][j] + cells[i][abs(j-1)]+cells[abs(i-1)][abs(j-1)] + cells[abs(i-height+1)][abs(j-width+1)] + cells[abs(i-height+1)][j]+ cells[abs(i-height+1)][abs(j-1)] + cells[i][abs(j-width+1)] + cells[abs(i-1)][abs(j-width+1)];
            }
            else
            {
                if (i==0 || i==height-1)
                    neighbours = cells[i][j+1] + cells[i][j-1] + cells[abs(i-1)][j-1] + cells[abs(i-1)][j] + cells[abs(i-1)][j+1]+cells[abs(i-height+1)][j]+ cells[abs(i-height+1)][j-1]+cells[abs(i-height+1)][j+1];
                else
                {
                    if (j==0 || j==width-1)
                        neighbours = cells[i+1][j] + cells[i-1][j] + cells[i-1][abs(j-1)] + cells[i][abs(j-1)] + cells[i+1][abs(j-1)]+cells[i][abs(j-width+1)]+ cells[i-1][abs(j-width+1)]+cells[i+1][abs(j-width+1)];
                    else
                    {
                        for (int k=-1;k<2;k++)
                            for (int n=-1;n<2;n++)
                                neighbours += cells[i+k][j+n];
                        neighbours -= cells[i][j];
                    }
                }
            }
            if (neighbours == 3 && cells[i][j]==FALSE)
                new_generation[i][j] = TRUE;
            if (neighbours <2 || neighbours>3)
                new_generation[i][j] = FALSE;
            if (neighbours==2)
                new_generation[i][j] = cells[i][j];
        }
    for (int i=0;i<height;i++)
        for(int j=0;j<width;j++)
            cells[i][j] = new_generation[i][j];
}
