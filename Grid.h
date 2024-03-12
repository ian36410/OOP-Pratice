#include <vector>
#include <time.h>

using namespace std;

// Grid class
class Grid {
public: // public static class constants, for direction indicators
	static const int NORTH = 0;
	static const int WEST = 1;
	static const int SOUTH = 2;
	static const int EAST = 3;
	bool tp = true;
	// public member functions
	Grid() {	
		// build 1 x 1 grid with mover in only square, facing east
		(*this).x.resize(1, vector<char>(1, '>'));
		(*this).rowNum = (*this).mRow = 1;
		(*this).colNum = (*this).mCol = 1;
	}
	Grid(int r = 3, int c = 3) {
		// build grid with r rows, c cols,
		// blocks around edge with random exit
		// and random mover position and direction
		if (r > 40) {
			r = 40;
		}
		if (c > 40) {
			c = 40;
		}
		if (r < 3) {
			r = 3;
		}
		if (c < 3) {
			r = 3;
		}
		(*this).rowNum = r;
		(*this).colNum = c;
		(*this).x.resize(r, vector<char>(c, '.'));
		for (int i = 0; i < c; i++) {
			x[0][i] = '#';
			x[r-1][i] = '#';
		}
		for (int i = 0; i < r; i++) {
			x[i][0] = '#';
			x[i][c-1] = '#';
		}
		srand((unsigned)time(NULL));
		int rw = rand() % 4;
		int e1 = 0, e2 = 0;
		(*this).mDir = rand() % 4;
		(*this).mRow = (rand() % r) - 1;
		(*this).mCol = (rand() % c) - 1;
		while (e1 == 0 && e2 == 0) {
			e1 = rand() % r;
			e2 = rand() % c;
		}
		while ((*this).GetRow() == 0 || (*this).GetCol() == 0) {
			(*this).mRow = (rand() % r) - 1;
			(*this).mCol = (rand() % c) - 1;
		}
		switch (rw) {
			case 0:
				for (int i = 1; i < e2 - 1; i++) {
					x[0][i] = '.';
				}
				break;
			case 1:
				for (int i = 1; i < e1 - 1; i++) {
					x[i][(*this).GetNumCols() - 1] = '.';
				}
				break;
			case 2:
				for (int i = 1; i < e2 - 1; i++) {
					x[r - 1][i] = '.';
				}
				break;
			case 3:
				for (int i = 1; i < e1 - 1; i++) {
					x[i][0] = '.';
				}
				break;
			}
		switch ((*this).GetDir()) {
			case NORTH:
				x[(*this).GetRow()][(*this).GetCol()] = '^';
				break;
			case WEST:
				x[(*this).GetRow()][(*this).GetCol()] = '<';
				break;
			case SOUTH:
				x[(*this).GetRow()][(*this).GetCol()] = 'v';
				break;
			case EAST:
				x[(*this).GetRow()][(*this).GetCol()] = '>';
				break;
		}
	}
	Grid(int r, int c, int mr, int mc, int d) {
		// build empty grid with r rows, c cols, and
		// mover at row mr, col mc, and facing direction d
		if (r > 40) {
			r = 40;
		}
		if (c > 40) {
			c = 40;
		}
		if (mr >= r) {
			mr = r - 1;
		}
		if (mc >= c) {
			mc = c - 1;
		}
		srand((unsigned)time(NULL));
		int rw = rand() % 4;
		int e1 = 0, e2 = 0;
		while (e1 == 0 && e2 == 0) {
			e1 = rand() % r;
			e2 = rand() % c;
		}
		(*this).rowNum = r;
		(*this).colNum = c;
		(*this).x.resize(r, vector<char>(c, '.'));
		(*this).mRow = mr;
		(*this).mCol = mc;
		(*this).mDir = d;
		switch ((*this).GetDir()) {
			case NORTH:
				x[(*this).GetRow()][(*this).GetCol()] = '^';
				break;
			case WEST:
				x[(*this).GetRow()][(*this).GetCol()] = '<';
				break;
			case SOUTH:
				x[(*this).GetRow()][(*this).GetCol()] = 'v';
				break;
			case EAST:
				x[(*this).GetRow()][(*this).GetCol()] = '>';
				break;
		}
	}
	bool Move(int s) {
		// move forward s spaces, if possible
		if (s >= 0) {
			bool a = false;
			for (int i = 0; i < s; i++) {
				a = (*this).FrontIsClear();
			}
			if (a) {
				if ((*this).tp) {
					switch ((*this).GetDir()) {
						case NORTH:
							if (x[(*this).GetRow()][(*this).GetCol()] == '@') {
								x[(*this).GetRow()][(*this).GetCol()] = '0';
								for (int i = 1; i < s; i++) {
									x[(*this).GetRow() - i][(*this).GetCol()] = ' ';
								}
							}
							else {
								for (int i = 0; i < s; i++) {
									x[(*this).GetRow() - i][(*this).GetCol()] = ' ';
								}
							}
							x[(*this).GetRow() - s][(*this).GetCol()] = '^';
							(*this).mRow = (*this).mRow - s;
							break;
						case WEST:
							if (x[(*this).GetRow()][(*this).GetCol()] == '@') {
								x[(*this).GetRow()][(*this).GetCol()] = '0';
								for (int i = 1; i < s; i++) {
									x[(*this).GetRow()][(*this).GetCol() - i] = ' ';
								}
							}
							else {
								for (int i = 0; i < s; i++) {
									x[(*this).GetRow()][(*this).GetCol() - i] = ' ';
								}
							}
							x[(*this).GetRow()][(*this).GetCol() - s] = '<';
							(*this).mCol = (*this).mCol - s;
							break;
						case SOUTH:
							if (x[(*this).GetRow()][(*this).GetCol()] == '@') {
								x[(*this).GetRow()][(*this).GetCol()] = '0';
								for (int i = 1; i < s; i++) {
									x[(*this).GetRow() + i][(*this).GetCol()] = ' ';
								}
							}
							else {
								for (int i = 0; i < s; i++) {
									x[(*this).GetRow() + i][(*this).GetCol()] = ' ';
								}
							}
							x[(*this).GetRow() + s][(*this).GetCol()] = 'v';
							(*this).mRow = (*this).mRow + s;
							break;
						case EAST:
							if (x[(*this).GetRow()][(*this).GetCol()] == '@') {
								x[(*this).GetRow()][(*this).GetCol()] = '0';
								for (int i = 1; i < s; i++) {
									x[(*this).GetRow()][(*this).GetCol() + i] = ' ';
								}
							}
							else {
								for (int i = 0; i < s; i++) {
									x[(*this).GetRow()][(*this).GetCol() + i] = ' ';
								}
							}
							x[(*this).GetRow()][(*this).GetCol() + s] = '>';
							(*this).mCol = (*this).mCol + s;
							break;
						}
				}
				else {
					switch ((*this).GetDir()) {
						case NORTH:
							x[(*this).GetRow()][(*this).GetCol()] = '.';
							x[(*this).GetRow() - s][(*this).GetCol()] = '^';
							(*this).mRow = (*this).mRow - s;
							break;
						case WEST:
							x[(*this).GetRow()][(*this).GetCol()] = '.';
							x[(*this).GetRow()][(*this).GetCol() - s] = '<';
							(*this).mCol = (*this).mCol - s;
							break;
						case SOUTH:
							x[(*this).GetRow()][(*this).GetCol()] = '.';
							x[(*this).GetRow() + s][(*this).GetCol()] = 'v';
							(*this).mRow = (*this).mRow + s;
							break;
						case EAST:
							x[(*this).GetRow()][(*this).GetCol()] = '.';
							x[(*this).GetRow()][(*this).GetCol() + s] = '>';
							(*this).mCol = (*this).mCol + s;
							break;
					}
				}
				return a;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	void TogglePath() {
		// toggle whether or not moved path is shown
		(*this).tp = !((*this).tp);
	}
	void TurnLeft() {
		// turn the mover to the left
		switch ((*this).GetDir()) {
			case NORTH:
				(*this).mDir = WEST;
				x[(*this).GetRow()][(*this).GetCol()] = '<';
				break;
			case WEST:
				(*this).mDir = SOUTH;
				x[(*this).GetRow()][(*this).GetCol()] = 'v';
				break;
			case SOUTH:
				(*this).mDir = EAST;
				x[(*this).GetRow()][(*this).GetCol()] = '>';
				break;
			case EAST:
				(*this).mDir = NORTH;
				x[(*this).GetRow()][(*this).GetCol()] = '^';
				break;
		}
	}
	void PutDown() {
		// put down an item at the mover's position
		x[(*this).GetRow()][(*this).GetCol()] = '@';
	}
	bool PutDown(int r, int c) {
		// put down an item at (r, c), if possible
		if (r >= 0 && c >= 0) {
			if (r < (*this).GetNumRows() && c < (*this).GetNumCols()) {
				x[r][c] = '0';
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	} 
	bool PickUp() {
		// pick up item at current position
		if (x[(*this).GetRow()][(*this).GetCol()] == '@' || x[(*this).GetRow()][(*this).GetCol()] == '0') {
			switch ((*this).GetDir()) {
				case NORTH:
					x[(*this).GetRow()][(*this).GetCol()] = '^';
					break;
				case WEST:
					x[(*this).GetRow()][(*this).GetCol()] = '<';
					break;
				case SOUTH:
					x[(*this).GetRow()][(*this).GetCol()] = 'v';
					break;
				case EAST:
					x[(*this).GetRow()][(*this).GetCol()] = '>';
					break;
			}
			return true;
		}
		else {
			return false;
		}
	}
	bool PlaceBlock(int r, int c) {
		// put a block at (r, c), if possible
		if (r >= 0 && c >= 0) {
			if (r < (*this).GetNumRows() && c < (*this).GetNumCols()) {
				x[r][c] = '#';
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	} 
	void Grow(int gr, int gc) {
		// grow the grid by gr rows, gc columns
		(*this).x.resize((*this).GetNumRows() + gr, vector<char>((*this).GetNumCols() + gc, '.'));
	} 
	void Display() const {
		// display the grid on screen
		cout << "The Grid : " << endl;
		for (int i = 0; i < (*this).GetNumRows(); i++)
		{
			for (int j = 0; j < (*this).GetNumCols(); j++)
			{
				cout << x[i][j] << " ";
			}
			cout << endl;
		}
	}

	// Accessors
	bool FrontIsClear() const {
		// check to see if space in front of mover is clear
		switch ((*this).GetDir()) {
			case NORTH:
				if ((*this).GetRow() - 1 < 0) {
					return false;
				}
				else if (x[(*this).GetRow() - 1][(*this).GetCol()] == '.') {
					return true;
				}
				else {
					return false;
				}
				break;
			case WEST:
				if ((*this).GetCol() - 1 < 0) {
					return false;
				}
				else if (x[(*this).GetRow()][(*this).GetCol() - 1] == '.') {
					return true;
				}
				else {
					return false;
				}
				break;
			case SOUTH:
				if ((*this).GetRow() + 1 >= (*this).GetNumRows()) {
					return false;
				}
				else if (x[(*this).GetRow() + 1][(*this).GetCol()] == '.') {
					return true;
				}
				else {
					return false;
				}
				break;
			case EAST:
				if ((*this).GetCol() + 1 >= (*this).GetNumCols()) {
					return false;
				}
				else if (x[(*this).GetRow()][(*this).GetCol() + 1] == '.') {
					return true;
				}
				else {
					return false;
				}
				break;
			default:
				return false;
		}
	} 
	bool RightIsClear() const {
		// check to see if space to right of mover is clear
		switch ((*this).GetDir()) {
		case NORTH:
			if ((*this).GetCol() + 1 >= (*this).GetNumCols()) {
				return false;
			}
			else if (x[(*this).GetRow()][(*this).GetCol() + 1] == '.') {
				return true;
			}
			else {
				return false;
			}
			break;
		case WEST:
			if ((*this).GetRow() - 1 < 0) {
				return false;
			}
			else if (x[(*this).GetRow() - 1][(*this).GetCol()] == '.') {
				return true;
			}
			else {
				return false;
			}
			break;
		case SOUTH:
			if ((*this).GetCol() - 1 < 0) {
				return false;
			}
			else if (x[(*this).GetRow()][(*this).GetCol() - 1] == '.') {
				return true;
			}
			else {
				return false;
			}
			break;
		case EAST:
			if ((*this).GetRow() + 1 >= (*this).GetNumRows()) {
				return false;
			}
			else if (x[(*this).GetRow() + 1][(*this).GetCol()] == '.') {
				return true;
			}
			else {
				return false;
			}
			break;
		default:
			return false;
		}
	} 
	int GetRow() const {
		// return row of the mover
		return (*this).mRow;
	} 
	int GetCol() const {
		// return column of the mover
		return (*this).mCol;
	}
	int GetDir() const {
		// return the mover facing direction
		return (*this).mDir;
	}
	int GetNumRows() const {
		// return number of rows in the grid
		return (*this).rowNum;
	} 
	int GetNumCols() const {
		// return number of columns in the grid
		return (*this).colNum;
	} 
private:
	int rowNum = 0, colNum = 0;
	int mRow = 0, mCol = 0;
	int mDir = 0;
	vector <vector<char>> x;
};
