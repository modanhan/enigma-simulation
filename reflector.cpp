#include <iostream>
#include "reflector.h"
#include "global_var.h"
using namespace std;

reflector::reflector() {
	v.assign(C, 0);
	for (int i = 0; i < C; i++) {
		v[i] = i + 97;
	}
}

bool reflector::config(string s) {
	if (s.size() < C) {
		cerr << "Reflector misconfiguration:\nInsufficient sequence\n";
		return false;
	}
	fill(v.begin(), v.end(), 0);
	for (int i = 0; i < C; i++) {
		if (v[i] == 0) {
			v[i] = s[i];
			if ((*this)[s[i]] == 0) {
				(*this)[s[i]] = i + 97;
			} else if ((*this)[s[i]] != i + 97) {
				cerr << "Reflector misconfiguration at:\n";
				cerr << s << "\n";
				for (int j = 0; j < i; j++) {
					cerr << ' ';
				}
				cerr << "^\n";
				return false;
			}
		} else {
			if (v[i] != s[i]) {
				cerr << "Reflector misconfiguration at:\n";
				cerr << s << "\n";
				for (int j = 0; j < i; j++) {
					cerr << ' ';
				}
				cerr << "^\n";
				return false;
			}
		}
	}
	return true;
}

char& reflector::operator[](char c){
	return v[c-97];
}
