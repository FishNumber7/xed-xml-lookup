#ifndef LOOKUP_XED_HH
#define LOOKUP_XED_HH

#include <iostream>

void initialize_xed();

std::string decode(unsigned char itext[15]);

const char* lookup(unsigned char itext[15], const char* architecture);

#endif