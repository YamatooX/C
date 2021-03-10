
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void loading(); // głowne menu

bool inRow( int arr[][9], int row ); // sprawdzenie czy liczba znajduje sie w wierszu

bool inColl( int arr[][9], int coll ); // -||- w kolumnie

bool inBox( int arr[][9], int row, int coll ); // -||- w kwadracie 3x3

void lFile( string fName, int arr[][9], int row, int coll ); // wczytanie pliku

bool isCorrect( int arr[][9] ); // czy wczytywane Sudoku jest poprawne

void Solve( int brr[][9] ); // rozwiąż Sudoku

void print( int arr[][9] ); // pokaż wynik

int *emptyPlace( int arr[][9] ); // czy są pola puste


int main()
{

    int arr[9][9];
    int a;
    do
    {
        loading();
        cin >> a;

        switch(a){
        case 1:
            {
                lFile("sudoku1.txt", arr, 9, 9 );
                cout << endl << " A oto Twoj wynik " << endl << endl;
                Solve(arr);
            break;}
        case 2:
            {
                lFile("sudoku2.txt", arr, 9, 9);
                cout << endl << " A oto Twoj wynik " << endl << endl;
                Solve(arr);
            break;}
        case 3:{
                lFile("sudoku3.txt", arr, 9, 9);
                cout << endl << " A oto Twoj wynik " << endl << endl;
                Solve(arr);
            break;}
        case 4: {
            lFile("sudoku4.txt", arr, 9, 9);
            cout << endl << " A oto Twoj wynik " << endl << endl;
            Solve(arr);
            break;}

        default: exit(0);};

    }while( a > 0 && a < 5 );
    return 0;
}

void loading()
{
    cout << endl;
    cout << "====================================================" << endl;
    cout << "  ||       SudokuSolver by Jaroslaw Bator       ||  " << endl;
    cout << "====================================================" << endl;
    cout << " [1] Sprawdz Sudoku 1" << endl;
    cout << " [2] Sprawdz Sudoku 2" << endl;
    cout << " [3] Sprawdz Sudoku 3" << endl;
    cout << " [4] Sprwadz Sudoku wlasne z 'dodatkowego' pliku sudoku4.txt" << endl;
    cout << " Wcisnij dowolny klawisz, by wyjsc z Solvera" << endl;
    cout << " Dokonaj wyboru: ";
}


void lFile(string fName, int arr[][9], int row, int coll) // wczytanie  danych z pliku
{
    ifstream file;
    file.open( fName.c_str() );

    if(!file.good())
        cout << " Nie udalo sie wczytac pliku!" << endl;
    cout << endl;

    for(row = 0; row < 9; row++ )
        for( coll = 0; coll < 9; coll++)
                file >> arr[row][coll];
    print(arr);
    file.close();
}


bool inRow(int arr[][9], int row)
{
	bool seen[10] = {false} ;
	for(int i =0 ; i< 9;i++)
	{
		int val = arr[row][i];
		if(seen[val] && val != 0) // daje fa³sz i tak. Coœ jest nie tak
			return false;
		else
			seen[val] = true;
	}
	return true;
}

bool inColl( int arr[][9], int coll )
{
    bool seen[10] = {false};
	for(int i =0 ; i < 9;i++)
	{
		int val = arr[i][coll];
		if(seen[val] && val != 0)
			return false;
		else
			seen[val] = true;
	}
	return true;
}

bool inBox( int arr[][9], int row, int coll )
{
    bool seen[10] = {0};
    int sRow = row - row % 3;
    int sColl = coll - coll % 3;

    for( int i = 0; i < 3; i++)
        for( int j = 0; j < 3; j++)
            {
                int val = arr[sRow + i][sColl + j];
                if(seen[val] == 1 && val != 0) // daje 1, gdy wartosc by³a widziana i pomija 0
                    return false;
                else
                    seen[val] = true;}
    return true;
}

bool isCorrect( int arr[][9] )
{
    for( int i = 0; i < 9; i++)
        if( !inRow(arr, i) )
            return false;

    for( int i = 0; i < 9; i++)
        if( !inColl(arr, i) )
            return false;

    for( int i = 0; i < 9; i += 3 )
        for( int j = 0; j < 9; j += 3 )
            if( !inBox(arr, i, j ) )
                return false;
    return true;
}

int *emptyPlace( int arr[][9] ) // wskaznik na puste miejsce w tablicy
{
    for( int i = 0; i < 9; i++ )
        for( int j = 0; j < 9; j++ )
            if( arr[i][j] == 0 )
                return &arr[i][j];
    return nullptr; // wskaznik zerowy
}

void print( int arr[][9]) // drukuje sudoku
{
    cout << endl;
    cout << " To dane, ktore zostaly wprowadzone: " << endl;
    cout << endl;

    for(  int row = 0; row < 9; row++)
    {
        cout << "  ";
        for( int coll = 0; coll < 9; coll++)
        {
            cout << arr[row][coll] << ' ';
            if( coll % 3 == 2 && coll != 8 )
                cout << " | ";
            if( row % 3 == 2 && row != 8 && coll == 8 )
                cout << endl << "-------------------------";
            }
        cout << endl;
    }
    if( !isCorrect(arr) )
        {cout << endl << " Sudoku niepoprawne";
        exit(0);}
}

void Solve( int brr[][9] )
{
    int arr[9][9];

    for( int i = 0; i < 9; i++ )
        for( int j = 0; j < 9; j++ )
            arr[i][j] = brr[i][j]; // Przypisanie wartosci z tablicy pierwotnej do nowej, by zachować wartosc poczatkową i na niej się opierać

    if(!isCorrect(arr))
        return; // eliminuje całą gałąź

    int *a = emptyPlace(arr); // zmienna, która pozwala na prace ze wskaźnikiem lokalnie

    if( a == nullptr ) // jesli Nie ma juz pustych miejsc na planszy, pokaz wynik
        print(arr);
    else
    {
        for( int num = 1; num < 10; num++)
            {
                *a = num;
                Solve(arr); // Znajdowanie najlepszej opcji dla liczby
            }
    }
}
