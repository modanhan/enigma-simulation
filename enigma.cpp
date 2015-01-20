#include <vector>
#include <iostream>
#include <fstream>
#include "rotor.h"
#include "reflector.h"
#include "enigma.h"
using namespace std;

namespace enigma {
typedef vector<rotor> machine;
machine m;
reflector ref;
int size;

bool config() {
	bool b = 1;
	size = 3;
	m.resize(size);
	ifstream file;
	char* memblock = new char[104];
	file.open(".config", ios::in | ios::binary);
	if (file.is_open()) {
		file.read(memblock, 104);
		b = b && ref.config(memblock);
		b = b && m[0].config(memblock + 26);
		b = b && m[1].config(memblock + 26 * 2);
		b = b && m[2].config(memblock + 26 * 3);
	} else {
		cout << "Failed to open enigma configuration file!\n";
		return false;
	}
	return b;
}

void type() {
	string s;
	getline(cin, s);
	for (char c : s) {
		bool cap = false;
		if (c >= 65 && c <= 90) {
			c += 32;
			cap = true;
		} else if (c < 97 || c > 122) {
			cout << c;
			continue;
		}
		for (int i = 0; i < size; i++) {
			c = m[i].front(c);
		}
		c = ref[c];
		for (int i = size - 1; i >= 0; i--) {
			c = m[i].back(c);
		}
		if (cap) {
			c -= 32;
		}
		cout << c;
		bool r = true;
		for (int i = 0; i < size; i++) {
			if (r) {
				r = m[i]++;
			} else {
				break;
			}
		}
	}
	cout << "\n";
}
}
