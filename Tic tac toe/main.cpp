// By Maziyar Kolagar ---> My GitHub : Thrymheim
// Contribution: Rares Racsan ---> Github: RaresRacsan

/* Features added by Rares
    1. Game instruction display
    2. Input validation
    3. Replay option
    4. Scoreboard
    5. Automatic board reset for new game
    6. User friendly prompts and messages
    7. End message
*/

#include <iostream>
#include <limits> // for numeric_limits

using namespace std;

// Function to display instructions at the start of the game
void displayInstructions() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    cout << "Player 1 is 'X' and Player 2 is 'O'.\n";
    cout << "To make a move, enter the number corresponding to the desired position:\n\n";
    cout << "  1  |  2  |  3  \n";
    cout << "-----|-----|-----\n";
    cout << "  4  |  5  |  6  \n";
    cout << "-----|-----|-----\n";
    cout << "  7  |  8  |  9  \n\n";
    cout << "Let's start!\n\n";
}

// Function to display the current state of the Tic-Tac-Toe board
void showBoard(char board[3][3]) {
    cout << "\n";
    // Loop through each row of the board
    for (int i = 0; i < 3; i++) {
        // Loop through each column in the row
        for (int j = 0; j < 3; j++) {
            // Print the board cell value
            cout << "  " << board[i][j];
            // Print the vertical separator between columns
            if (j < 2) cout << "  |";
        }
        cout << "\n";
        // Print the horizontal separator between rows (except after the last row)
        if (i < 2) cout << "-----|-----|-----\n";
    }
    cout << "\n";
}

// Function to validate player input and ensure it corresponds to an unoccupied board position
int getValidInput(char board[3][3]) {
    int position;
    // Keep asking for input until a valid position is given
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> position;

        // Check if input is a valid number between 1 and 9
        if (cin.fail() || position < 1 || position > 9) {
            // Clear the error flag in case of invalid input
            cin.clear();
            // Ignore invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 9.\n";
        } else {
            // Calculate row and column based on the input position
            int row = (position - 1) / 3;
            int col = (position - 1) % 3;
            // Check if the position is already occupied
            if (board[row][col] == 'X' || board[row][col] == 'O') {
                cout << "Position already taken. Choose another.\n";
            } else {
                break; // Valid position found, exit the loop
            }
        }
    }
    return position;
}

// Function to manage a player's turn by placing their mark on the board
void userTurn(char board[3][3], char playerMark) {
    int position = getValidInput(board);
    // Calculate row and column based on the position chosen
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    // Place the player's mark on the board
    board[row][col] = playerMark;
}

// Function to check if there is a winner on the board
bool checkWinner(char board[3][3]) {
    // Check all rows and columns for a winning combination
    for (int i = 0; i < 3; i++) {
        // Check if all three cells in a row are the same
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        // Check if all three cells in a column are the same
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }

    // Check both diagonals for a winning combination
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;

    // No winner found
    return false;
}

// Function to check if the game is a tie (all spaces filled and no winner)
bool checkTie(char board[3][3]) {
    // Only check for a tie if there is no winner
    if (!checkWinner(board)) {
        // Loop through all cells in the board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // If any cell is not marked, it's not a tie
                if (board[i][j] != 'X' && board[i][j] != 'O') return false;
            }
        }
        return true; // All cells are marked and no winner, so it's a tie
    }
    return false;
}

// Function to reset the board to its initial state for a new game
void resetBoard(char board[3][3]) {
    char resetValue = '1'; // Start with '1' for the first cell
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = resetValue++; // Set each cell to its initial value
        }
    }
}

// Function to handle the gameplay, including alternating turns and checking for end conditions
void playGame(int &player1Wins, int &player2Wins, int &ties) {
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    int currentPlayer = 1;
    bool gameEnded = false;

    // Continue the game until there's a winner or a tie
    while (!gameEnded) {
        showBoard(board); // Display the current board
        cout << "Player " << currentPlayer << "'s turn.\n";

        // Player 1 is 'X', Player 2 is 'O'
        if (currentPlayer == 1) {
            userTurn(board, 'X');
        } else {
            userTurn(board, 'O');
        }

        // Check if there's a winner
        if (checkWinner(board)) {
            showBoard(board);
            cout << "Player " << currentPlayer << " won!\n\n";
            // Update the scoreboard
            if (currentPlayer == 1) player1Wins++; else player2Wins++;
            gameEnded = true;
        } else if (checkTie(board)) {
            // If it's a tie, display the message and update the scoreboard
            showBoard(board);
            cout << "The game ends in a tie!\n\n";
            ties++;
            gameEnded = true;
        } else {
            // Switch turns if the game hasn't ended
            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }
    }
}

// Function to display the scoreboard showing the number of wins and ties
void displayScoreboard(int player1Wins, int player2Wins, int ties) {
    cout << "\n--- Scoreboard ---\n";
    cout << "Player 1 Wins: " << player1Wins << "\n";
    cout << "Player 2 Wins: " << player2Wins << "\n";
    cout << "Ties: " << ties << "\n";
}

// Main function to control the flow of the game, replay option, and final message
int main() {
    displayInstructions(); // Show game instructions at the start
    int player1Wins = 0, player2Wins = 0, ties = 0;
    char playAgain;

    // Main loop to allow the user to play multiple games
    do {
        playGame(player1Wins, player2Wins, ties); // Play one game session
        displayScoreboard(player1Wins, player2Wins, ties); // Display current scoreboard

        // Ask if the user wants to play again
        cout << "Would you like to play again? (y/n): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any extra input

    } while (playAgain == 'y' || playAgain == 'Y'); // Repeat if the user chooses 'y'

    cout << "Thank you for playing!\n"; // End message
    return 0;
}
