#pragma once
#include "stdafx.h"
#include "DrawBuffer.h"
#include <mutex>
#include <vector>

class DrawBuffer {
public:
	std::vector<int> buf;
	bool done = false;
	int cursor = 0;
	std::mutex* mutex;

	DrawBuffer(std::mutex* mut) {
		mutex = mut;
	}

	~DrawBuffer() {

	}

	DrawBuffer(const DrawBuffer& dbuf) {
		buf = dbuf.buf;
		done = dbuf.done;
		cursor = dbuf.cursor;
		mutex = dbuf.mutex;
	}

};

