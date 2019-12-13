

#include "lastresult.h"

using namespace std; // _STDAPI_(int) 


bool pattern_t(string _line, const string  _keyword1, const string _keyword2, const string _pattern, string & result_str)
{ // _line要匹配的字符串， _keyword1匹配的关键字，_keyword2要匹配的关键字，_pattern匹配_line的正则表达式字符串，result_str存储最终结果
	if (_keyword1.empty() | _keyword2.empty()) //判断关键字是否为空
	{
		cout << "no search keyword";
		return false;
	}

	smatch _match_result;
	regex pattern_regex(_pattern);

	if (regex_search(_line, _match_result, pattern_regex))
	{
		regex pattern_keyword1(_keyword1); //将第一个关键字转化为正则表达式
		smatch match_keyword1_result;

		regex pattern_keyword2(_keyword2); //将第二个关键字转换为正则表达式
		smatch match_keyword2_result;

		string temp_prefix = _match_result.prefix().str(); // 提取关系匹配中前部的字符串
		string temp_match_result = _match_result[2].str();//提取关系匹配中中间的字符串
		string temp_suffix = _match_result.suffix().str(); //提取关系匹配中后部的字符串


		if (regex_search(temp_prefix, match_keyword1_result, pattern_keyword1)) // 对第一个关键字进行前端匹配
		{
			result_str += _keyword1;
			result_str += _match_result[1];
		}
		else if (regex_search(temp_match_result, match_keyword1_result, pattern_keyword1)) //对第一个关键字经行中间匹配
		{
			result_str += _match_result[1];
			result_str += _keyword1;
		}


		if (regex_search(temp_match_result, match_keyword2_result, pattern_keyword2)) // 对第二个关键字进行前端匹配
		{
			result_str += _keyword2;
			result_str += _match_result[3];
		}
		else if (regex_search(temp_suffix, match_keyword2_result, pattern_keyword2)) //对第二个关键字进行后部匹配
		{
			result_str += _match_result[3];
			result_str += _keyword2;
		}

		if (!result_str.empty())
			return true;
		else
			return false;
	}
	else
		return false;

}

bool pattern_o(string _line, const string  _keyword1, const string _keyword2, const string _pattern, string & result_str)
{ // _line要匹配的字符串， _keyword1匹配的关键字，_keyword2要匹配的关键字，_pattern匹配_line的正则表达式字符串，result_str存储最终结果

	if (_keyword1.empty() | _keyword2.empty()) //判断关键字是否为空
	{
		cout << "no search keyword";
		return false;
	}
	smatch _match_result;
	regex pattern_regex(_pattern);
	if (regex_search(_line, _match_result, pattern_regex))
	{
		smatch _match_keyword1_result; //定义第一个关键字的正则匹配结果存储位置
		regex pattern_regex_keyword1(_keyword1); //将keyword1正则化

		smatch _match_keyword2_result; //定义第二个关键字的正则匹配结果存储位置
		regex pattern_regex_keyword2(_keyword2); // 将keyword2正则化

		string match_result_prefix = _match_result.prefix().str(); //将_match_result prefix位置的字符串转化为string型
		string match_result_suffix = _match_result.suffix().str(); //将_match_result suffix 位置的字符串转化为string型

		if (regex_search(match_result_prefix, _match_keyword1_result, pattern_regex_keyword1))
			//对match_result_prefix进行查找keyword1操作
		{
			result_str += _keyword1;
			result_str += _match_result[1];
		}
		if (regex_search(match_result_suffix, _match_keyword2_result, pattern_regex_keyword2))
			result_str += _keyword2;
		else
			cout << "no match\n";


		if (!result_str.empty())
			return true;
		else
			return false;
	}
	else
		return false;
}


int EVENT_GetRelation(char *sen, int istart1, int iend1, int istart2, int iend2, char *result)
{
	if ((istart1 > iend1) | (iend1 > istart2) | (istart2 > iend2))
	{
		cout << "the keyword of index wrong\n";
		return 0;
	}
	string line = sen; // 将传入的char* 转换为string
	string result_temp; //将最终结果存储为string类型

	bool judge = false;

	// 关键词抽取
	int keyword_index1 = istart1 * 3 - 3;
	int keyword_index2 = istart2 * 3 - 3;
	string keyword1 = line.substr(keyword_index1, (iend1 - istart1 + 1) * 3);
	string keyword2 = line.substr(keyword_index2, (iend2 - istart2 + 1) * 3);

	/*int keyword_index1 = istart1 * 2 - 2;
	int keyword_index2 = istart2 * 2 - 2;
	string keyword1 = line.substr(keyword_index1, iend1 * 2 - keyword_index1);
	string keyword2 = line.substr(keyword_index2, iend2 * 2 - keyword_index2);*/


	//正则表达式
	string	pattern_but[] = { //转折 
		"(虽然|尽管|虽)(.*)(但也|但还|但却|但)",
		"(与其)(.*)(不如)",
		"(虽然|尽管|虽)(.*)(但|但是也|但是还|但是却)",
		"(不是)(.*)(而是)",
		"(即使|就算是)(.*)(也|还)",
		"(即便)(.*)(也|还)",
		"(虽然|即使)(.*)(但是|可是|然而|仍然|还是|也|但)",
		"(虽然|尽管|固然)(.*)(也|还|却)",
		"(与其|宁可)(.*)(决不|也不|也要)",
		"(与其|宁肯)(.*)(决不|也不|也要)",
		"(与其|宁愿)(.*)(也不|决不|也要)",
		"(不管|不论|无论|即使)(.*)(都|也|总|始终|一直)",
		"(虽)(.*)(可是|倒|但|可|却|还是|但是)",
		"(虽然|纵然|即使)(.*)(倒|还是|但是|但|可是|可|却)",
		"(虽说)(.*)(还是|但|但是|可是|可|却)",
		"(无论)(.*)(都|也|还|仍然|总|始终|一直)",
		"(与其)(.*)(宁可|不如|宁肯|宁愿)"
		};
	string	pattern_seq[] = {//顺承
		"(因为)(.*)(所以)",
		"(又|再|才|并)(.*)(进而)",
		"(首先|第一)(.*)(其次|然后)",
		"(首先|先是)(.*)(再|又|还|才)",
		"(一方面)(.*)(另一方面|又|也|还)"
		};
	string pattern_more[] = { // 并列
		"(不但|不仅)(.*)(而且)",
		"(不单)(.*)(而且|并且|也|还)",
		"(不但)(.*)(而且|并且|也|还)",
		"(不管)(.*)(都|也|总|始终|一直)",
		"(不光)(.*)(而且|并且|也|还)",
		"(虽然|尽管)(.*)(不过)",
		"(不仅)(.*)(还|而且|并且|也)",
		"(不论)(.*)(还是|也|总|都|始终|一直)",
		"(不只)(.*)(而且|也|并且|还)",
		"(不但|不仅|不光|不只)(.*)(而且)",
		"(尚且|都|也|又|更)(.*)(还|又)",
		"(既然|既)(.*)(就|便|那|那么|也|还)",
		"(无论|不管|不论|或)(.*)(或者)",
		"(或是)(.*)(或是)",
		"(或者|不论|不管|不论)(.*)(或者)",
		"(不是)(.*)(也)",
		"(要么|或者)(.*)(要么|或者)"
	};
	string pattern_condition[] = { //条件
		"(除非)(.*)(否则|才|不然|要不)",
		"(除非)(.*)(否则的话)",
		"(还是|不论|不管)(.*)(还是|都|总)",
		"(既然)(.*)(又|且|也|亦)",
		"(假如)(.*)(那么|就|也|还)",
		"(假若|如果)(.*)(那么|就|那|则|便)",
		"(假使|如果)(.*)(那么|就|那|则|便)",
		"(尽管|如果)(.*)(那么|就|那|则|便)",
		"(即使|就是)(.*)(也|还是)",
		"(如果|既然)(.*)(那么)",
		"(万一)(.*)(那么|就)",
		"(要是|如果)(.*)(就|那)",
		"(要是|如果|假如)(.*)(那么|就|那|的话)",
		"(一旦)(.*)(就)",
		"(既然|假如|既|如果)(.*)(则|就)",
		"(只要)(.*)(就|便|都|总)",
		"(只有)(.*)(才|还)"
	};
	string pattern_1[] = { // 由果溯因配套式
		"(之?所以)(.*)(因为)",
		"(之?所以)(.*)(由于)",
		"(之?所以)(.*)(缘于)"
	};
	string pattern_2[] = { //由因到果配套式
		"(因为)(.*)(从而)",
		"(因为)(.*)(为此)",
		"(既然)(.*)(所以)",
		"(由于)(.*)(为此)",
		"(除非)(.*)(才)",
		"(只有)(.*)(才)",
		"(由于)(,*)(以至于?)",
		"(既[然]?)(.*)(却)",
		"(如果)(.*)(那么)",
		"(如果)(.*)(则)",
		"(由于)(.*)(从而)",
		"(既然?)(.*)(因此)",
		"(如果)(.*)(就)",
		"(只要)(.*)(就)",
		"(因为)(.*)(所以)",
		"(由于)(.*)(于是)",
		"(因为)(.*)(因此)",
		"(由于)(.*)(故)",
		"(因为)(.*)(以致于?)",
		"(因为)(.*)(因而)",
		"(由于)(.*)(因此)",
		"(因为)(.*)(于是)",
		"(由于)(.*)(致使)",
		"(因为)(.*)(致使)",
		"(由于)(.*)(以致于?)",
		"(因为)(.*)(故)",
		"(因[为]?)(.*)(以至于?)",
		"(由于)(.*)(所以)",
		"(因为)(.*)(故而)",
		"(由于)(.*)(因而)"
		};
	string pattern_3 = "(于是|所以|故|致使|以致于?|因此|以至于?|从而|因而)"; // 由因到果居中式明确	
	string pattern_4[] = { //由因到果居中式精确
		"(牵动|已致|导向|使动|导致|勾起|引入|指引|使|予以|产生|促成)",
		"(造成|引导|造就|促使|酿成|引发|渗透|促进|引起|诱导|引来|促发)",
		"(引致|诱发|推进|诱致|推动|招致|影响|致使|滋生|归于|作用|使得)",
		"(决定|攸关|令人|引出|浸染|带来|挟带|触发|关系|渗入|诱惑|波及|诱使)"
	};
	string pattern_5 = "(为了|依据|按照|因为|因|按|依赖|凭借|由于)";// 由因到果前端式模糊
	string pattern_6 = "(以免|以便|为此|才)";// 由因到果居中式模糊
	string pattern_7 = "(既然?|因|因为|如果|由于|只要)";// 由因到果前端式精确
	string pattern_8 = "(根源于|取决|来源于|出于|取决于|缘于|在于|出自|起源于|来自|发源于|发自|源于|根源于|立足|立足于)";
	// 由果溯因居中式模糊
	string pattern_9 = "是?(因为|由于)";// 由果溯因居端式精确

	vector<string> pattern_but_temp(pattern_but, pattern_but + 17);
	for (vector<string>::iterator pattern = pattern_but_temp.begin(); pattern != pattern_but_temp.end(); ++pattern) //转折模式匹配
	{
		if (pattern_t(line, keyword1, keyword2, *pattern, result_temp))
		{
			cout << "pattern_but\n";
			judge = true;
			break;
		}
	}
	if (judge)
	{
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	vector<string> pattern_seq_temp(pattern_seq, pattern_seq + 5);
	for (vector<string>::iterator pattern = pattern_seq_temp.begin(); pattern != pattern_seq_temp.end(); ++pattern) //顺承模式匹配
	{
		if (pattern_t(line, keyword1, keyword2, *pattern, result_temp))
		{
			cout << "pattern_seq\n";
			judge = true;
			break;
		}
	}
	if (judge)
	{
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	vector<string> pattern_more_temp(pattern_more, pattern_more + 17);
	for (vector<string>::iterator pattern = pattern_more_temp.begin(); pattern != pattern_more_temp.end(); ++pattern) //并列模式匹配
	{
		if (pattern_t(line, keyword1, keyword2, *pattern, result_temp))
		{
			std::cout << "pattern_more\n";
			judge = true;
			break;
		}
	}
	if (judge)
	{
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	vector<string> pattern_condition_temp(pattern_condition, pattern_condition + 17);
	for (vector<string>::iterator pattern = pattern_condition_temp.begin(); pattern != pattern_condition_temp.end(); ++pattern) //条件模式匹配
	{
		if (pattern_t(line, keyword1, keyword2, *pattern, result_temp))
		{
			std::cout << "pattern_consition\n";
			judge = true;
			break;
		}
	}
	if (judge)
	{
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	vector<string> pattern_1_temp(pattern_1, pattern_1 + 3);
	for (vector<string>::iterator pattern = pattern_1_temp.begin(); pattern != pattern_1_temp.end(); ++pattern) //由果溯因配套式 模式匹配
	{
		if (pattern_t(line, keyword1, keyword2, *pattern, result_temp))
		{
			cout << "pattern_1\n";
			judge = true;
			break;
		}
	}
	if (judge)
	{
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	vector<string> pattern_2_temp(pattern_2, pattern_2 + 30);
	for (vector<string>::iterator pattern = pattern_2_temp.begin(); pattern != pattern_2_temp.end(); ++pattern) // 由因到果配套式匹配模式
	{
		if (pattern_t(line, keyword1, keyword2, *pattern, result_temp))
		{
			cout << "pattern_2\n";
			judge = true;
			break;
		}
	}
	if (judge)
	{
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_3, result_temp))// 由因到果居中式明确匹配模式
		judge = true;
	if (judge)
	{
		cout << "pattern_3\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	vector<string> pattern_4_temp(pattern_4, pattern_4 + 4);
	for (vector<string>::iterator pattern = pattern_4_temp.begin(); pattern != pattern_4_temp.end(); ++pattern) {
		if (pattern_o(line, keyword1, keyword2, *pattern, result_temp))//由因到果居中式精确匹配模式
		{
			cout << "pattern_4\n";
			judge = true;
			break;
		}
	}
	if (judge)
	{
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_5, result_temp))// 由因到果前端式模糊匹配模式
		judge = true;
	if (judge)
	{
		cout << "pattern_5\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_6, result_temp)) //由因到果居中式模糊匹配模式
		judge = true;
	if (judge)
	{
		cout << "pattern_6\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_7, result_temp)) // 由因到果前端式精确匹配模式
		judge = true;
	if (judge)
	{
		cout << "pattern_7\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_8, result_temp)) //由果溯因居中式模糊匹配模式
		judge = true;
	if (judge)
	{
		cout << "pattern_8\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_9, result_temp)) //由果溯因居端式精确匹配模式
		judge = true;
	if (judge)
	{
		cout << "pattern_9\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	else
		return 0;
}
