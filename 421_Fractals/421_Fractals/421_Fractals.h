#pragma once

#include "resource.h"

void drawFractal(HDC* hdc, int len, int depth, int x, int y);
void drawFractalParallelized(HDC* hdc, int len, int depth, int x, int y);
