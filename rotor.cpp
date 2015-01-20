#include <iostream>
#include <algorithm>
#include "rotor.h"
#include "global_var.h"

using namespace std;

rotor::rotor() {
	p = 0;
	f.assign(C, 0);
}

bool rotor::config(const std::string& s) {
	if (s.size() < C) {
		cout << "Rotor misconfiguration:\nInsufficient sequence\n";
		return false;
	}
	vector<bool> v(C, 0);
	for (int i = 0; i < C; i++) {
		if (s[i] < 97 || s[i] >= 123 || v[s[i] - 97]) {
			cout << "Rotor misconfiguration at:\n" << s << "\n";
			for (int j = 0; j < i; j++) {
				cout << " ";
			}
			cout << "^\n";
			return false;
		} else {
			f[i] = s[i];
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

char rotor::front(char c) {
	return f[(c - 97 + p) % 26];
}

char rotor::back(char c) {
	int d = distance(f.begin(), find(f.begin(), f.end(), c));
	d += 26 - p;
	d %= 26;
	return (char) (d + 97);
}
