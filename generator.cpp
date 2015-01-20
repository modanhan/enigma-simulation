#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include "rotor.h"
#include "generator.h"
#include "global_var.h"
using namespace std;

namespace generator {
ofstream file;
int index;
char* memblock;
vector<char> ref, rot;

void init() {
	index = 0;
	memblock = new char[104];
	ref.assign(C, 0);
	rot.assign(C, 0);
}

void generate(int c) {
	generateref(c);
	generaterot();
	generaterot();
	generaterot();
}

void write() {
	file.write(memblock, 104);
}

void open(string s) {
	file.open(s, ios::out | ios::binary);
	if (file.is_open()) {
		cout << "File successfully opened and output will be written to " << s
				<< "\n";
	}
}

void close() {
	file.close();
}

void generateref(int c) {
	for (int i = 0; i < C; i++) {
		ref[i] = i + 97;
	}
	vector<bool> b(C, 1);
	srand(time(0));
	while (c > 0) {
		int l = rand() % C, r = rand() % C;
		if ((l != r) && b[l] && b[r]) {
			ref[l] ^= ref[r];
			ref[r] ^= ref[l];
			ref[l] ^= ref[r];
			b[l] = 0;
			b[r] = 0;
			c--;
		}
	}
	for (int i = 0; i < C; i++) {
		memblock[index] = ref[i];
		index++;
	}
}

void generaterot() {
	for (int i = 0; i < C; i++) {
		rot[i] = i + 97;
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(rot.begin(), rot.end(), g);
	int i = index + 26;
	for (int i = 0; i < C; i++) {
		memblock[index] = rot[i];
		index++;
	}
}
}
