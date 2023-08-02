#include <iostream>
#include <time.h>
#include <algorithm>
#include <conio.h> 
#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void SetColor(int fg, int bg) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, fg | (bg << 4));
}

void delay(clock_t a) {
    clock_t start = clock();
    while (clock() - start < a);
}

#include "Question.h"
#include "User.h"
#include "Admin.h"
#include "Player.h"
#include "Design.h"

int main() {
    srand(time(NULL));

    FirstPage();
    SecondPage();

    return 0;
}