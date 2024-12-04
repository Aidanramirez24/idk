#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int COLS = 7;
const int ROWS = 6;
string Player1 = "\033[33m X \033[0m",  // Yellow X for Player 1
       Player2 = "\033[31m O \033[0m",  // Red O for Player 2
       Player;
bool winner = false, Draw = false;

void Play(string[][COLS], int ROWS);
void DisplayBoard(string[][COLS], int ROWS);
void Token(string[][COLS], int ROWS, string);
void PlayerinTurn();
bool CheckColumnFull(string[][COLS], int ROWS, int);
bool CheckRow0Full(string[][COLS], int ROWS, int);
bool CheckForWinner(string[][COLS], int ROWS, int COLS, string Player);
void ResetBoard(string[][COLS], int ROWS);

int main() {
    char opcion;
    string Gamearray[ROWS][COLS] = {{" - ", " - ", " - ", " - ", " - ", " - ", " - "}, 
                                    {" - ", " - ", " - ", " - ", " - ", " - ", " - "}, 
                                    {" - ", " - ", " - ", " - ", " - ", " - ", " - "},
                                    { " - ", " - ", " - ", " - ", " - ", " - ", " - "},
                                    { " - ", " - ", " - ", " - ", " - ", " - ", " - "},
                                    { " - ", " - ", " - ", " - ", " - ", " - ", " - "}};
    
    do {
        cout << "\n\t\tConnect Four!\n";
        cout << "\n\t\tA.) Jugar.";
        cout << "\n\t\tB.) Como jugar.";
        cout << "\n\t\tC.) Salir.";
        cout << "\n\t\tOprima opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 'a':  
            case 'A':  
                Play(Gamearray, ROWS);
                break;
            case 'b':
            case 'B': 
                cout << "\n\t\tEl primero que conecte la misma letra horizontalmente, verticalmente o diagonalmente gana el juego.\n";
                break;
            case 'c':
            case 'C': 
                return 0;
            default: 
                cout << "\n\t\t*Opcion invalida!!!!! Ingrese opcion(A, B ó C)*\n";
        }
    } while(opcion != 'C' && opcion != 'c');
}

void Play(string Gamearray[][COLS], int ROWS) {
    if (winner || Draw) {
        ResetBoard(Gamearray, ROWS);
        winner = false;
        Draw = false;
    }

    while (!winner && !Draw) {
        DisplayBoard(Gamearray, ROWS);
        PlayerinTurn();
        Token(Gamearray, ROWS, Player);
        winner = CheckForWinner(Gamearray, ROWS, COLS, Player);
        if (winner) {
            DisplayBoard(Gamearray, ROWS);
            cout << "¡Jugador " << Player << " ha ganado!\n";
            break;
        }
    }
}

void DisplayBoard(string Gamearray[][COLS], int ROWS) {
    cout << "\n 1   2   3   4   5   6   7";
    for (int i = 0; i < ROWS; i++) {
        cout << "\n";
        for (int j = 0; j < COLS; j++) {
            cout << Gamearray[i][j] << "|";
        }
    }
    cout << endl;
}

void Token(string Gamearray[][COLS], int ROWS, string Player) {
    int Column;
    bool Lleno = true;

    cout << " Jugador " << Player;
    cout << " Entra columna (1-7)(Para salir de el juego oprima '-1'): ";
    cin >> Column;

    if (Column == -1) {
        winner = true;
        return;
    }

    while (Column < 1 || Column > 7) {
        DisplayBoard(Gamearray, ROWS);
        cout << "Las columnas son de 1 a 7: ";
        cout << " Jugador " << Player;
        cout << " Entra columna (1-7)(Para salir de el juego oprima '-1'): ";
        cin >> Column;
        if (Column == -1) {
            winner = true;
            return;
        }
    }

    Lleno = CheckColumnFull(Gamearray, ROWS, Column);

    if (Lleno) {
        CheckRow0Full(Gamearray, ROWS, Column);
        return;
    }

    int row = ROWS - 1;
    while (Gamearray[row][Column - 1] != " - ") {
        row--;
    }
    Gamearray[row][Column - 1] = Player;
}

void PlayerinTurn() {
    static int number = 0;
    if (number % 2 == 0)
        Player = Player1;
    else
        Player = Player2;
    number++;
}

bool CheckColumnFull(string Gamearray[][COLS], int ROWS, int Column) {
    for (int i = 0; i < ROWS; i++) {
        if (Gamearray[i][Column - 1] == " - ") {
            return false;
        }
    }
    return true;
}

bool CheckRow0Full(string Gamearray[][COLS], int ROWS, int Column) {
    for (int j = 0; j < COLS; j++) {
        if (Gamearray[0][j] == " - ") {
            return false;
        }
    }
    Draw = true;
    cout << "\n\t\tEmpate!\n\n";
    return true;
}

bool CheckForWinner(string Gamearray[][COLS], int ROWS, int COLS, string Player) {
    // Check horizontal, vertical, and diagonal win conditions
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (Gamearray[row][col] == Player) {
                // Horizontal check
                if (col + 3 < COLS &&
                    Gamearray[row][col + 1] == Player &&
                    Gamearray[row][col + 2] == Player &&
                    Gamearray[row][col + 3] == Player) {
                    return true;
                }
                // Vertical check
                if (row + 3 < ROWS &&
                    Gamearray[row + 1][col] == Player &&
                    Gamearray[row + 2][col] == Player &&
                    Gamearray[row + 3][col] == Player) {
                    return true;
                }
                // Diagonal (down-right) check
                if (row + 3 < ROWS && col + 3 < COLS &&
                    Gamearray[row + 1][col + 1] == Player &&
                    Gamearray[row + 2][col + 2] == Player &&
                    Gamearray[row + 3][col + 3] == Player) {
                    return true;
                }
                // Diagonal (up-right) check
                if (row - 3 >= 0 && col + 3 < COLS &&
                    Gamearray[row - 1][col + 1] == Player &&
                    Gamearray[row - 2][col + 2] == Player &&
                    Gamearray[row - 3][col + 3] == Player) {
                    return true;
                }
            }
        }
    }
    return false;
}

void ResetBoard(string Gamearray[][COLS], int ROWS) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            Gamearray[i][j] = " - ";
        }
    }
}