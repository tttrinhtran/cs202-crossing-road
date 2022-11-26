#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "cPeople.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

void FixConsoleWindow();
void gotoXY(int x, int y);