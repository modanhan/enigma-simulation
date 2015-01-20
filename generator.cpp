#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include "rotor.h"
#include "generator.h"
#include "global_var.h"
using namespace std;

void generateref() {
	vector<char> v(C, 0);
	for (int i = 0; i < C; i++) {
		v[i] = i + 97;
	}
	int c = C >> 1;
	vector<bool> b(C, 1);
	srand(time(0));
	while (c > 0) {
		int l = rand() % C, r = rand() % C;
		if ((l != r) && b[l] && b[r]) {
			v[l] ^= v[r];
			v[r] ^= v[l];
			v[l] ^= v[r];
			b[l] = 0;
			b[r] = 0;
			c--;
		}
	}
	for (int i = 0; i < C; i++) {
		cout << v[i];
	}
	cout << "\n";
}

void generaterot() {
	vector<char> v(C, 0);
	for (int i = 0; i < C; i++) {
		v[i] = i + 97;
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(v.begin(), v.end(), g);
	for (int i = 0; i < C; i++) {
		cout << v[i];
	}
	cout << "\n";
}
