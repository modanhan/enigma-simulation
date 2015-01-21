#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include "rotor.h"
#include "reflector.h"
#include "generator.h"
#include "enigma.h"
#include "global_var.h"
using namespace std;

void couthelp(char* argv[]) {
	cout << "\nUsage:\t" << argv[0] << " <command(s)> <option(s)>\n\n"
			<< argv[0] << " --help\tshow the help message\n";
}

int main(int argc, char* argv[]) {
	int fflag = 0, vflag = 0, cflag = 0, oflag = 0, cvalue = 10;
	char* fvalue = NULL;
	int c;
	int command = 0;
	if (argc > 1) {
		if (string(argv[1]) == "config") {
			command = 1;
		} else if (string(argv[1]) == "gen") {
			command = 2;
		} else if (string(argv[1]) == "reset") {
			command = 3;
		} else if (string(argv[1]) == "--help") {
			cout << argv[0] << " is an Enigma machine simulator, "
					<< "and can be used to encrypt and decrypt messages.\n\n"
					<< "Usage:\t" << argv[0] << " <command(s)> <option(s)>\n"
					<< "Options:\n" << "\t--help\tShow the help message\n"
					<< "Commands:\n"
					<< "\tconfig\tConfigures the enigma with a new configuration\n"
					<< "\tgen\tGenerates a configuration for the enigma\n"
					<< "\treset\tResets the enigma with a new configuration\n";
			return 0;
		} else {
			cout << argv[0] << ": invalid option: " << argv[1] << "\n";
			couthelp(argv);
			return 0;
		}
	}

	while ((c = getopt(argc, argv, "f:vc:o:")) != -1) {
		switch (c) {
		case 'f': {
			fflag = 1;
			fvalue = optarg;
			break;
		}
		case 'v': {
			vflag = 1;
			break;
		}
		case 'c': {
			cflag = 1;
			cvalue = atoi(optarg);
			break;
		}
		case 'o': {
			oflag = 1;
			fvalue = optarg;
			break;
		}
		default: {
			couthelp(argv);
			return 0;
		}
		}
	}

	switch (command) {
	case 0: {
		if (!enigma::config()) {
			return 0;
		}
		enigma::type();
		break;
	}
	case 1: {
		if (fflag) {
			ifstream file;
			char* memblock = new char[104];
			file.open(fvalue, ios::in | ios::binary);
			if (file.is_open()) {
				file.read(memblock, 104);
				ofstream ofile;
				ofile.open(".config", ios::out | ios::binary);
				ofile.write(memblock, 104);
				ofile.close();
				file.close();
				cout << "Enigma configured to the specified file: " << fvalue
						<< "\n";
			} else {
				cout << "Failed to open the specified file: " << fvalue
						<< "!\n";
				return 0;
			}
		} else if (vflag) {
			ifstream file;
			char* memblock = new char[104];
			file.open(".config", ios::in | ios::binary);
			if (file.is_open()) {
				file.read(memblock, 104);
				cout << "Current enigma configuration:\n";
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 26; j++) {
						cout << memblock[i * 26 + j];
					}
					cout << "\n";
				}

				file.close();
			} else {
				cout << "Failed to open the specified file: " << fvalue
						<< "!\n";
				return 0;
			}
		} else {
			cout << "Command requires an argument: -f <file>\n";
			couthelp(argv);
		}
		break;
	}
	case 2: {
		if (cvalue < 0 || cvalue > 13) {
			cout << "Reflector complexity value must be between 0 and 13\n";
			couthelp(argv);
			return 0;
		}
		generator::init();
		if (fflag || oflag) {
			generator::open(fvalue);
		} else {
			generator::open("enigma.config");
		}
		cout << cvalue;
		generator::generate(cvalue);
		generator::write();
		generator::close();
		break;
	}
	case 3: {
		generator::init();
		generator::generate(cvalue);
		generator::open(".config");
		generator::write();
		generator::close();
		generator::open("enigma.config");
		generator::write();
		generator::close();
		cout << "Enigma reinitialized with a new configuration.\n";
		break;
	}
	}
	return 0;
}
