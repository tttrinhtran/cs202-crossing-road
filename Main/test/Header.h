#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "classes.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std::this_thread;
using namespace std::chrono;

void FixConsoleWindow();
void gotoXY(int x, int y);
void bgWork(cGame& g);
void generator(cGame& g);