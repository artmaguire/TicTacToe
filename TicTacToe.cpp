#include "TicTacToe.h"
#include <iostream>

int XO [3][3];
int turn;
int match;
bool winner = false, instructions = false;
int player1, player2;

void TicTacToe::initialise() {
    turn = 1;
    for (auto &i : XO) {
        for (int &j : i) {
            j = -1;
        }
    }
}

void TicTacToe::printXO() {
    if (instructions) {
        char ans;

        cout << "\nRows go across (0-2)" << endl;
        cout << "------------▷\n" << endl;
        cout << "Columns go down (0-2)" << endl;
        cout << "\t\t\t|\n" << "\t\t\t|\n" << "\t\t\t|\n" << "\t\t\t|\n" << "\t\t\t|\n" << "\t\t\t▽" << endl;

        cout << "\nTo quit type 'q' between game play or at the start." << endl;

        cout << "\nWould you like an example? (y/n)" << endl;
        cin >> ans;
        if (ans == 'y') {
            printExample();
        } else if (ans == 'q') {
            exit(0);
        }
    }

    cout << "----|---|----" << endl;
    cout << "| " << convert(XO[0][0]) << " | " << convert(XO[0][1]) << " | " << convert(XO[0][2]) << " |" << endl;
    cout << "|-----------|" << endl;
    cout << "| " + convert(XO[1][0]) << " | " << convert(XO[1][1]) + " | " << convert(XO[1][2]) << " |" << endl;
    cout << "|-----------|" << endl;
    cout << "| " << convert(XO[2][0]) << " | " + convert(XO[2][1]) << " | " << convert(XO[2][2]) << " |" << endl;
    cout << "----|---|----" << endl;
}

bool TicTacToe::validate(int r, int c) {
    if (r < 0 || r > 2) return false;
    if (c < 0 || c > 2) return false;
    if (static_cast<char>(r) == 'q' || static_cast<char>(c) == 'q') { //Check for quit command
        exit(0);
    }

    return XO[r][c] == -1;
}

bool TicTacToe::checkWin(int r, int c) {
    int count = 0;

    for (int i = 0; i < 3; i++) {
        if (XO[r][i] == turn) count++;
    }
    if (count == 3) return true;
    count = 0;

    for (auto &i : XO) {
        if (i[c] == turn) count++;
    }
    if (count == 3) return true;
    count = 0;

    if (r == c) {
        for (int i = 0; i < 3; i++) {
            if (XO[i][i] == turn) count++;
        }
        if (count == 3) return true;
        count = 0;
    }

    if (r + c == 2) {
        for (int i = 0; i < 3; i++) {
            if (XO[i][2 - i] == turn) count++;
        }
        if (count == 3) return true;
    }

    return false;
}

string TicTacToe::convert(int n) {
    switch (n) {
        case 0: return "O";
        case 1: return "X";
        default: return " ";
    }
}

void TicTacToe::run() {
    int x = 0;
    char in;
    printWelcome();
    initialise();
    printXO();
    int counter = 0;

    while (x < match) {
        winner = false;
        if (x > 0) {
            initialise();
            printXO();
            counter = 0;
        }

        while (!winner) {
            cout << convert(turn) << "'s turn" << endl;
            string c;
            string r;
            int row, column;
            while (true) {
                cout << "Select a row on the board: " << endl;
                cin >> r;
                cout << "Select a column on the board: " << endl;
                cin >> c;

                if (r == "q" || c == "q") {
                    exit(0);
                } else {
                    row = stoi(r);
                    column = stoi(c);
                }

                if (validate(row, column)) {
                    break;
                } else {
                    cout << "Invalid Input. Please input different values.\n" << endl;
                }
            }

            XO[row][column] = turn;
            counter++;
            printXO();
            if (checkWin(row, column)) {
                cout << convert(turn) << " Wins!" << endl;
                if (turn == 1) {
                    player1++;
                    cout << "Player 1 " << player1 << " - " << player2 << " Player 2" << endl;
                    winner = true;
                } else {
                    player2++;
                };
                if (x >= match)
                    winner = true;
            } else {
                if (counter == 9) {
                    cout << "Draw" << endl;
                    player1 = player2 = 1;
                }
            }
            turn = (turn == 1) ? 0 : 1;
        }
        x++;
        if (player1 == match || player2 == match) {
            winner = true;
        }
    }
    cout << "Do you want a rematch? (y/n)" << endl;
    cin >> in;
    if (in == 'y') {
        run();
    } else {
        exit(0);
    }
}

void TicTacToe::printWelcome() {
    bool type = false;
    int x = 0;
    char ans, inst;

    cout << "Welcome to Tic Tac Toe!\n" << endl;

    cout << "Would you like game instructions? (y/n)\n";
    cin >> inst;
    cout << endl;

    if (inst == 'y') {
        help();
        instructions = true;
    } else if (inst == 'n') {
        while (!type) {
            cout << "Select a game type!" << endl;
            cout << "Best of (1-5)" << endl;
            cin >> x;

            if (x < 1 || x > 5) {
                type = false;
                cout << "Invalid Input!" << endl;
            } else {

                cout << "Are you sure you want Best of " << x << "? (y/n)" << endl;
                cin >> ans;

                if (ans == 'q')
                    exit(0);

                type = ans == 'y';
            }
        }
        match = x;
    } else {
        cout << "Invalid input." << endl;
    }
}

void TicTacToe::help() {
    cout << "How to play." << endl;
    printXO();
    cout << endl;
}

void TicTacToe::printExample() {
    cout << "\nHere is an Example." << endl;

    cout << "row = 1" << endl;
    cout << "column = 1" << endl;

    cout << "----|---|----" << endl;
    cout << "| " << " " << " | " << " " << " | " << " " << " |" << endl;
    cout << "|-----------|" << endl;
    cout << "| " << " " << " | " << "X" << " | " << " " << " |" << endl;
    cout << "|-----------|" << endl;
    cout << "| " << " " << " | " << " " << " | " << " " << " |" << endl;
    cout << "----|---|----" << endl;

    instructions = false;
    run();
}
