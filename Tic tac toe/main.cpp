//By Maziyar kolagar ---> My GitHub : Thrymheim

/*Whole code in one look:
we use 2D array to make tic tac toe shape :  1  2  3
                                             4  5  6
                                             7  8  9
Then player1 make a move --> check if win or draw --> player2 make a move --> check if win or draw --> repeat the process */

#include <iostream>

using namespace std;

void showBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
            cout << "\t\t\t" << board[i][j] << "\t";
        cout << "\n\n";
    }
}

bool checkIfPositionValid(char board[3][3], int position)
{
    if (position > 9 || position < 1)
        return false;
    //We get position from players example--> player enter 8--> row = 2 and col = 1 (We know index starts from 0)
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    if (board[row][col] == 'X' || board[row][col] == 'O')
        return false;
    return true;
}

void userTurn(char board[3][3], char playerMark)
{
    while (true)
    {
        int position;
        cout << "\t\t\tPlayer ";
        if (playerMark == 'X')
        {
            cout << "1";
        }
        else
        {
            cout << "2";
        }
        cout << " make a move: ";
        cin >> position;
        cout << endl;
        if (checkIfPositionValid(board, position))
        {
            int row = (position - 1) / 3;
            int col = (position - 1) % 3;
            board[row][col] = playerMark;
            break;
        }
        else
        {
            cout << "Error: Position is either invalid or already filled!\n\n";
        }
    }
}

bool checkWinner(char board[3][3])
{
    // Check for rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == 'X')
            {
                cout << "Player 1 won!\n\n";
            }
            else
            {
                cout << "Player 2 won!\n\n";
            }
            return true;
        }
    }
    // Check for columns
    for (int j = 0; j < 3; j++)
    {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j])
        {
            if (board[0][j] == 'X')
            {
                cout << "Player 1 won!\n\n";
            }
            else
            {
                cout << "Player 2 won!\n\n";
            }
            return true;
        }
    }
    // Check for diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'X')
        {
            cout << "Player 1 won!\n\n";
        }
        else
        {
            cout << "Player 2 won!\n\n";
        }
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'X')
        {
            cout << "Player 1 won!\n\n";
        }
        else
        {
            cout << "Player 2 won!\n\n";
        }
        return true;
    }
    return false;
}

bool checkTie(char board[3][3])
{
    if (!checkWinner(board))
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] != 'X' && board[i][j] != 'O')
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    cout << "Player 1 mark is 'X' and Player 2 mark is 'O'\n\n";
    int currentPlayer = 1;
    int moves = 0;
    bool gameEnded = false;

while (!gameEnded)
{
    showBoard(board);
    if (currentPlayer == 1)
    {
        userTurn(board, 'X');
    }
    else
    {
        userTurn(board, 'O');
    }
    moves++;

    if (checkWinner(board))
    {
        gameEnded = true;
    }
    else if (checkTie(board))
    {
        cout << "The game ends in a tie!\n\n";
        gameEnded = true;
    }
    else
    {
        if (currentPlayer == 1)
        {
            currentPlayer = 2;
        }
        else
        {
            currentPlayer = 1;
        }
    }
}

    return 0;
}
