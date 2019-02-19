//
// Created by aelni on 16/02/2019.
//

#ifndef TICTACTOE_TICTACTOE_H
#define TICTACTOE_TICTACTOE_H

#include <iostream>

using namespace std;


class TicTacToe {
public:
    static void run();

private:
    static void printWelcome();
    static void help();
    static void initialise();
    static bool validate(int r, int c);
    static bool checkWin(int r, int c);
    static void printXO();
    static string convert(int n);
};


#endif //TICTACTOE_TICTACTOE_H
