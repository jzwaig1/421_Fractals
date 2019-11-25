#pragma once

#include "resource.h"

void drawFractal(HDC* hdc, int len, int depth, int x, int y);
void drawLeft(HDC* hdc, int len, int depth, int x, int y);
void drawRight(HDC* hdc, int len, int depth, int x, int y);
void drawUp(HDC* hdc, int len, int depth, int x, int y);
void drawDown(HDC* hdc, int len, int depth, int x, int y);
void drawFractalParallelized(HDC* hdc, int len, int depth, int x, int y);
