#ifndef OLD_MAIN_H
#define OLD_MAIN_H
#include "Token.h"
#include "Relation.h"
#include "Parser.h"
#include <vector>
#include <queue>

std::vector <Token *> analyzer_tokens(string input_file);
DatalogProgram * main_parser(string input_file);
#endif
