#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "rotor.h"
#include "reflector.h"
#include "generator.h"
#include "global_var.h"
using namespace std;

int main(int argc, char* argv[]) {
	int fflag = 0, vflag = 0, cflag = 0, oflag = 0
	ccount = 10;
	int c;
	int command = 0;
	if (argc > 1) {
		if (string(argv[1]) == "config") {
			command = 1;
		} else if (string(argv[1]) == "gen") {
			command = 2;
		} else {

		}
	}
	while ((c = getopt(argc, argv, "f:vc:o:")) != -1) {
		switch (c) {
		case 'f': {
			cout << optarg << "\n";
			break;
		}
		case 'v': {
			cout << "viewing mode\n";
			break;
		}
		case 'c': {
			int com = atoi(optarg);
			cout << com << " complexity\n";
			break;
		}
		case 'o': {
			break;
		}
		default:
			cout << "hi\n";
			break;
		}
	}

	switch (command) {
	case 0: {
		break;
	}
	case 1: {
		break;
	}
	case 2: {
		break;
	}
	}
	return 0;
}
