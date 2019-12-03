#pragma once

#include "resource.h"
#include <vector>
#include "DrawBuffer.h"

void drawFractal(HDC* hdc, int len, int depth, int x, int y, DrawBuffer* dbuf);
void draw1Fractal(HDC* hdc, int len, int depth, int x, int y, std::vector<int>* buf);
/*
void drawLeft(HDC* hdc, int len, int depth, int x, int y);
void drawRight(HDC* hdc, int len, int depth, int x, int y);
void drawUp(HDC* hdc, int len, int depth, int x, int y);
void drawDown(HDC* hdc, int len, int depth, int x, int y);
*/
void drawFractalParallelized(HDC* hdc, int len, int depth, int x, int y, int pDepth);
void drawFromBuffers(HDC* hdc, std::vector<DrawBuffer>* bufList);
void fractalThread(HDC* hdc, int len, int depth, int x, int y, DrawBuffer* dbuf, int pDepth);
