#pragma once
#include <string>
namespace generator {
void init();
void generate(int);
void write();
void open(std::string);
void close();
void generateref(int);
void generaterot();
}
