#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "Board.h"
#include <unordered_map>

using namespace std;

struct Comparator {
	bool operator()(Board* lhs, Board* rhs) {
		return lhs->getF() > rhs->getF();
	}
};

size_t hashing(vector<vector<int>> puzzles) {
	string result;
	for (size_t i = 0; i < puzzles.size(); ++i) {
		for (size_t j = 0; j < puzzles[i].size(); ++j) {
			string tmp = to_string(puzzles[i][j]);
			result += tmp;
		}
	}
	return hash<string>{}(result);
}

int getInvCount(vector<vector<int>> puzzle) {
	vector<int> tmp(9);
	for (size_t i = 0; i < puzzle.size(); ++i) {
		for (size_t j = 0; j < puzzle[i].size(); ++j) {
			tmp[i*puzzle[i].size() + j] = puzzle[i][j];
		}
	}
	int count = 0;
	for (size_t i = 0; i < tmp.size() - 1; ++i) {
		for (size_t j = i + 1; j < tmp.size(); ++j) {
			if (tmp[j] && tmp[i] && tmp[i] > tmp[j])
				++count;
		}
	}
	return count;
}

bool isSolvable(const Board& board) {
	vector<vector<int>> puzzle = board.getPuzzles();
	int count = getInvCount(puzzle);
	return count % 2 == 0;
}

void solve(Board* start, const Board* final) {
	if (!isSolvable(*start)) {
		cout << "The puzzle is not solvable" << endl;
		return;
	}

	//creating a priority queue to store each board
	priority_queue<Board*, std::vector<Board*>, Comparator> q;
	//creating map to keep in mind already visited states
	unordered_map<size_t, vector<vector<int>>> visited;
	start->calculateHeuristic(*final);
	start->calculateF();
	q.push(start);

	while (!q.empty()) {

		Board* min = q.top();
		q.pop();
		size_t key = hashing(min->getPuzzles());
		visited[key] = min->getPuzzles();

		if (*min == *final) {
			min->printPath();
			return;
		}
		for (size_t i = 0; i < 4; ++i) {
			pair<int, int> coord = min->getCoordinates();
			if (min->canGenerate(coord.first, coord.second, i)) {
				Board *tmp = min->generateChilds(coord.first, coord.second, i);
				tmp->setParent(min);
				tmp->calculateHeuristic(*final);
				tmp->calculatePath(*min);
				tmp->calculateF();
				size_t tmpKey = hashing(tmp->getPuzzles());
				if (visited.find(tmpKey) == visited.end()) {
					q.push(tmp);
					visited[tmpKey] = tmp->getPuzzles();
				}
			}
		}
	}

}

int main() {
	vector<vector<int>> g = { {1,2,3}, {4,5,6}, {7,8,0} };
	Board* goal = new Board(g);

	//examples for solvable 8-puzzle games
	vector<vector<int>> ex1;
	Board* e1;

	/*ex1 = { {2,0,1}, {6,3,7}, {4,5,8} };
	e1 = new Board(ex1);
	solve(e1, goal);
	delete e1;*/

	/*ex1 = { {4,5,7},{8,1,2},{3,6,0} };
	e1 = new Board(ex1);
	solve(e1, goal);
	delete e1;*/

	/*ex1 = { {1,2,3},{4,0,6},{7,5,8} };
	e1 = new Board(ex1);
	solve(e1, goal);
	delete e1;*/

	/*ex1 = { {6,5,3},{1,4,0},{8,2,7} };
	e1 = new Board(ex1);
	solve(e1, goal);
	delete e1;*/

	/*ex1 = { {2,8,6},{7,5,3},{0,4,1} };
	e1 = new Board(ex1);
	solve(e1, goal);
	delete e1;*/

	//example for not solvable 8-puzzle game

	ex1 = { {2,6,8},{7,5,3},{0,4,1} };
	e1 = new Board(ex1);
	solve(e1, goal);
	delete e1;

	delete goal;
	return 0;
}