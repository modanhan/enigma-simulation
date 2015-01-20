// enigma-simulation.cpp : Defines the entry point for the console application.
//

#include "rotor.h"
#include "reflector.h"
#include "generator.h"
#include "global_var.h"
#include <vector>
#include <iostream>
using namespace std;

typedef vector<rotor> machine;

machine m;
int size;

void enc() {
	size = 3;
	m.resize(size);
	bool c = 1;

	c = c && m[0].config("bjscatmvzwhuoxrinleyfpkdqg");
	c = c && m[1].config("abcdefghijklmnopqrstuvwxyz");
	c = c && m[2].config("qwertyuioplkjhgfdsazxcvbnm");
	reflector ref;
	c = c && ref.config("rfmnjbvsleuicdpozahykgxwtq");
	if (!c) {
		return;
	}
	string s;
	getline(cin, s);
	for (char c : s) {
		if (c < 97 || c > 122) {
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

int main(int argc, char* argv[]) {
	if (argc == 1) {
		enc();
	} else {
		for (int i = 1; i < argc; i++) {
			if (string(argv[i]) == "--help") {
				cout << argv[0] << " is an Enigma machine simulator, "
						<< "and can be used to encrypt and decrypt messages.\n\n"
						<< "Usage:\t" << argv[0]
						<< " <command(s)> <option(s)>\n" << "Options:\n"
						<< "\t--help\tShow the help message\n" << "Commands:\n"
						<< "\tconfig\tConfigure the machine\n"
						<< "\tgen\tGenerates a configuration for the machine\n"
						<< "\n" << argv[0]
						<< " help <command> lists available options for the command.\n";
				return 0;
			} else if (string(argv[i]) == "gen") {
				i++;
				if (i < argc && string(argv[i]) == "-ref") {
					cerr << "Reflector configuration:\n";
					generateref();
				} else if (i < argc && string(argv[i]) == "-rot") {
					cerr << "Rotor configuration:\n";
					generaterot();
					generaterot();
					generaterot();
				} else {
					i--;
					cerr << "Reflector configuration:\n";
					generateref();
					cerr << "\nRotor configuration:\n";
					generaterot();
					generaterot();
					generaterot();
					continue;
				}
			} else if (string(argv[i]) == "config") {
				i++;
				if (i < argc) {
					
				} else {

				}
			} else {
				cout << "Unknown option: " << argv[i] << "\nUsage:\t" << argv[0]
						<< " <command(s)> <option(s)>\n" << "Options:\n"
						<< "\t--help\tShow the help message\n" << "Commands:\n"
						<< "\tconfig\tConfigure the machine\n"
						<< "\tgen\tGenerates a configuration for the machine\n"
						<< "\n" << argv[0]
						<< " help <command> lists available options for the command.\n";
				return 0;
			}
		}
	}

	return 0;
}
