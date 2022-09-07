#pragma once

#ifndef COORDS_H
#define COORDS_H

struct coords {
	int row = 0;
	int col = 0;

	bool operator==(const coords& other) const {
		return row == other.row && col == other.col;
	}
	bool operator!=(const coords& other) const {
		return !(*this == other);
	}
	coords& operator=(const coords& rhs) {
		row = rhs.row;
		col = rhs.col;
		return *this;
	}
};

#endif
