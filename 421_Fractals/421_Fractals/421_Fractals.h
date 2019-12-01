#pragma once

#include "resource.h"
#include <vector>
#include "DrawBuffer.h"

void drawFractal(HDC* hdc, int len, int depth, int x, int y, DrawBuffer* dbuf);
void drawLeft(HDC* hdc, int len, int depth, int x, int y);
void drawRight(HDC* hdc, int len, int depth, int x, int y);
void drawUp(HDC* hdc, int len, int depth, int x, int y);
void drawDown(HDC* hdc, int len, int depth, int x, int y);
void drawFractalParallelized(HDC* hdc, int len, int depth, int x, int y);
void DrawFromBuffers(HDC* hdc, std::vector<DrawBuffer>* bufList);
void fractalThread(HDC* hdc, int len, int depth, int x, int y, DrawBuffer* dbuf);
