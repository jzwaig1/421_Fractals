#pragma once

#include "resource.h"
#include <vector>

void drawFractal(HDC* hdc, int len, int depth, int x, int y, std::vector<int>* buf);
void drawLeft(HDC* hdc, int len, int depth, int x, int y);
void drawRight(HDC* hdc, int len, int depth, int x, int y);
void drawUp(HDC* hdc, int len, int depth, int x, int y);
void drawDown(HDC* hdc, int len, int depth, int x, int y);
//void drawFractalParallelized(HDC* hdc, int len, int depth, int x, int y);
