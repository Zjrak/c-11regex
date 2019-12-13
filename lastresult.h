#ifndef _LASTRESULT_H_
#define _LASTRESULT_H_

#include "unitype.h"
#include <iostream>
#include <iterator>
#include <string.h>
#include <iostream> 
#include <regex>
#include<vector>
#include <string>
using namespace std;

int EVENT_GetRelation(char *sen, int istart1, int iend1, int istart2, int iend2, char *result);
bool pattern_t(string _line, const string  _keyword1, const string _keyword2, const string _pattern, string & result_str);
bool pattern_o(string _line, const string  _keyword1, const string _keyword2, const string _pattern, string & result_str);

#endif