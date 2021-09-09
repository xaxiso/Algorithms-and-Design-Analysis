#include <iostream>
#include <bits/stdc++.h>
#include <queue>
#include <limits.h>
#include <vector>
#include <list>
#include <utility>
using namespace std;

#ifndef DIMACS
#include <cryptominisat5/cryptominisat.h>
#else
#include <fstream>
#include <vector>
#endif

namespace sat {

#ifndef DIMACS

CMSat::SATSolver solver;
std::vector<CMSat::Lit> lit_buf;

void Init(int n) { solver.new_vars(n + 1); }

void AddClause(std::vector<int> v) {
	lit_buf.clear();
	lit_buf.reserve(v.size());
	for (int x : v) lit_buf.emplace_back(abs(x), x < 0);
	solver.add_clause(lit_buf);
}

bool Solve() { return solver.solve() == CMSat::l_True; }

int GetResult(int id) {
	auto r = solver.get_model()[id];
	return r == CMSat::l_True ? 1 : r == CMSat::l_False ? -1 : 0;
}

#else

std::vector<std::vector<int>> clauses;
int n_vars;

void Init(int n) { n_vars = n; }

void AddClause(std::vector<int> v) { clauses.emplace_back(std::move(v)); }

bool Solve() {
	std::fstream fs("out.dimacs", fs.trunc | fs.out);
	fs << "p cnf " << n_vars << ' ' << clauses.size() << '\n';
	for (auto &v : clauses) {
		for (auto x : v) fs << x << ' ';
		fs << "0\n";
	}
	fs.close();
	exit(0);
}

int GetResult(int id) { return 0; }

#endif // DIMACS

}  // namespace sat

int board[30][30];

int main(int argc, char const *argv[])
{
	int r, c;
	scanf("%d%d", &r, &c);



	return 0;
}