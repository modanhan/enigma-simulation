#include "rotor.h"
#include "global_var.h"
#include <iostream>

using namespace std;

rotor::rotor() {
	p = 0;
	f.assign(C, 0);
	b.assign(C, 0);
}

bool rotor::config(const string& s) {
	vector<bool> v(C, 0);
	for (int i = 0; i < s.size(); i++) {
		if (s[i] < 97 || s[i] >= 123 || v[s[i] - 97]) {
			cerr << "Rotor misconfiguration at:\n" << s << "\n";
			for (int j = 0; j < i; j++) {
				cerr << " ";
			}
			cerr << "^\n";
			return false;
		} else {
			f[i] = s[i];
			b[s[i] - 97] = i + 97;
			v[s[i] - 97] = 1;
		}
	}
	return true;
}

bool rotor::operator++(int) {
	p++;
	if (p >= C) {
		p -= C;
		return true;
	} else {
		return false;
	}
}

char& rotor::front(char c) {
	return f[(c - 97 + p) % 26];
}

char& rotor::back(char c) {
	return b[(c - 97 + 26 - p) % 26];
}
