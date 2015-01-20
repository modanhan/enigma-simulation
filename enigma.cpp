#include <vector>
#include <iostream>
#include "rotor.h"
#include "reflector.h"
#include "enigma.h"
using namespace std;

typedef vector<rotor> machine;

machine m;
int size;

void type() {
	size = 3;
	m.resize(size);
	bool b = 1;

	b = b && m[0].config("bjscatmvzwhuoxrinleyfpkdqg");
	b = b && m[1].config("abcdefghijklmnopqrstuvwxyz");
	b = b && m[2].config("qwertyuioplkjhgfdsazxcvbnm");
	reflector ref;
	b = b && ref.config("abcnjfvsleuimdpozrhykgxwtq");
	if (!b) {
		return;
	}
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
