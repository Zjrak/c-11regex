

#include "lastresult.h"

using namespace std; // _STDAPI_(int) 


bool pattern_t(string _line, const string  _keyword1, const string _keyword2, const string _pattern, string & result_str)
{ // _lineҪƥ����ַ����� _keyword1ƥ��Ĺؼ��֣�_keyword2Ҫƥ��Ĺؼ��֣�_patternƥ��_line��������ʽ�ַ�����result_str�洢���ս��
	if (_keyword1.empty() | _keyword2.empty()) //�жϹؼ����Ƿ�Ϊ��
	{
		cout << "no search keyword";
		return false;
	}

	smatch _match_result;
	regex pattern_regex(_pattern);

	if (regex_search(_line, _match_result, pattern_regex))
	{
		regex pattern_keyword1(_keyword1); //����һ���ؼ���ת��Ϊ������ʽ
		smatch match_keyword1_result;

		regex pattern_keyword2(_keyword2); //���ڶ����ؼ���ת��Ϊ������ʽ
		smatch match_keyword2_result;

		string temp_prefix = _match_result.prefix().str(); // ��ȡ��ϵƥ����ǰ�����ַ���
		string temp_match_result = _match_result[2].str();//��ȡ��ϵƥ�����м���ַ���
		string temp_suffix = _match_result.suffix().str(); //��ȡ��ϵƥ���к󲿵��ַ���


		if (regex_search(temp_prefix, match_keyword1_result, pattern_keyword1)) // �Ե�һ���ؼ��ֽ���ǰ��ƥ��
		{
			result_str += _keyword1;
			result_str += _match_result[1];
		}
		else if (regex_search(temp_match_result, match_keyword1_result, pattern_keyword1)) //�Ե�һ���ؼ��־����м�ƥ��
		{
			result_str += _match_result[1];
			result_str += _keyword1;
		}


		if (regex_search(temp_match_result, match_keyword2_result, pattern_keyword2)) // �Եڶ����ؼ��ֽ���ǰ��ƥ��
		{
			result_str += _keyword2;
			result_str += _match_result[3];
		}
		else if (regex_search(temp_suffix, match_keyword2_result, pattern_keyword2)) //�Եڶ����ؼ��ֽ��к�ƥ��
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
{ // _lineҪƥ����ַ����� _keyword1ƥ��Ĺؼ��֣�_keyword2Ҫƥ��Ĺؼ��֣�_patternƥ��_line��������ʽ�ַ�����result_str�洢���ս��

	if (_keyword1.empty() | _keyword2.empty()) //�жϹؼ����Ƿ�Ϊ��
	{
		cout << "no search keyword";
		return false;
	}
	smatch _match_result;
	regex pattern_regex(_pattern);
	if (regex_search(_line, _match_result, pattern_regex))
	{
		smatch _match_keyword1_result; //�����һ���ؼ��ֵ�����ƥ�����洢λ��
		regex pattern_regex_keyword1(_keyword1); //��keyword1����

		smatch _match_keyword2_result; //����ڶ����ؼ��ֵ�����ƥ�����洢λ��
		regex pattern_regex_keyword2(_keyword2); // ��keyword2����

		string match_result_prefix = _match_result.prefix().str(); //��_match_result prefixλ�õ��ַ���ת��Ϊstring��
		string match_result_suffix = _match_result.suffix().str(); //��_match_result suffix λ�õ��ַ���ת��Ϊstring��

		if (regex_search(match_result_prefix, _match_keyword1_result, pattern_regex_keyword1))
			//��match_result_prefix���в���keyword1����
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
	string line = sen; // �������char* ת��Ϊstring
	string result_temp; //�����ս���洢Ϊstring����

	bool judge = false;

	// �ؼ��ʳ�ȡ
	int keyword_index1 = istart1 * 3 - 3;
	int keyword_index2 = istart2 * 3 - 3;
	string keyword1 = line.substr(keyword_index1, (iend1 - istart1 + 1) * 3);
	string keyword2 = line.substr(keyword_index2, (iend2 - istart2 + 1) * 3);

	/*int keyword_index1 = istart1 * 2 - 2;
	int keyword_index2 = istart2 * 2 - 2;
	string keyword1 = line.substr(keyword_index1, iend1 * 2 - keyword_index1);
	string keyword2 = line.substr(keyword_index2, iend2 * 2 - keyword_index2);*/


	//������ʽ
	string	pattern_but[] = { //ת�� 
		"(��Ȼ|����|��)(.*)(��Ҳ|����|��ȴ|��)",
		"(����)(.*)(����)",
		"(��Ȼ|����|��)(.*)(��|����Ҳ|���ǻ�|����ȴ)",
		"(����)(.*)(����)",
		"(��ʹ|������)(.*)(Ҳ|��)",
		"(����)(.*)(Ҳ|��)",
		"(��Ȼ|��ʹ)(.*)(����|����|Ȼ��|��Ȼ|����|Ҳ|��)",
		"(��Ȼ|����|��Ȼ)(.*)(Ҳ|��|ȴ)",
		"(����|����)(.*)(����|Ҳ��|ҲҪ)",
		"(����|����)(.*)(����|Ҳ��|ҲҪ)",
		"(����|��Ը)(.*)(Ҳ��|����|ҲҪ)",
		"(����|����|����|��ʹ)(.*)(��|Ҳ|��|ʼ��|һֱ)",
		"(��)(.*)(����|��|��|��|ȴ|����|����)",
		"(��Ȼ|��Ȼ|��ʹ)(.*)(��|����|����|��|����|��|ȴ)",
		"(��˵)(.*)(����|��|����|����|��|ȴ)",
		"(����)(.*)(��|Ҳ|��|��Ȼ|��|ʼ��|һֱ)",
		"(����)(.*)(����|����|����|��Ը)"
		};
	string	pattern_seq[] = {//˳��
		"(��Ϊ)(.*)(����)",
		"(��|��|��|��)(.*)(����)",
		"(����|��һ)(.*)(���|Ȼ��)",
		"(����|����)(.*)(��|��|��|��)",
		"(һ����)(.*)(��һ����|��|Ҳ|��)"
		};
	string pattern_more[] = { // ����
		"(����|����)(.*)(����)",
		"(����)(.*)(����|����|Ҳ|��)",
		"(����)(.*)(����|����|Ҳ|��)",
		"(����)(.*)(��|Ҳ|��|ʼ��|һֱ)",
		"(����)(.*)(����|����|Ҳ|��)",
		"(��Ȼ|����)(.*)(����)",
		"(����)(.*)(��|����|����|Ҳ)",
		"(����)(.*)(����|Ҳ|��|��|ʼ��|һֱ)",
		"(��ֻ)(.*)(����|Ҳ|����|��)",
		"(����|����|����|��ֻ)(.*)(����)",
		"(����|��|Ҳ|��|��)(.*)(��|��)",
		"(��Ȼ|��)(.*)(��|��|��|��ô|Ҳ|��)",
		"(����|����|����|��)(.*)(����)",
		"(����)(.*)(����)",
		"(����|����|����|����)(.*)(����)",
		"(����)(.*)(Ҳ)",
		"(Ҫô|����)(.*)(Ҫô|����)"
	};
	string pattern_condition[] = { //����
		"(����)(.*)(����|��|��Ȼ|Ҫ��)",
		"(����)(.*)(����Ļ�)",
		"(����|����|����)(.*)(����|��|��)",
		"(��Ȼ)(.*)(��|��|Ҳ|��)",
		"(����)(.*)(��ô|��|Ҳ|��)",
		"(����|���)(.*)(��ô|��|��|��|��)",
		"(��ʹ|���)(.*)(��ô|��|��|��|��)",
		"(����|���)(.*)(��ô|��|��|��|��)",
		"(��ʹ|����)(.*)(Ҳ|����)",
		"(���|��Ȼ)(.*)(��ô)",
		"(��һ)(.*)(��ô|��)",
		"(Ҫ��|���)(.*)(��|��)",
		"(Ҫ��|���|����)(.*)(��ô|��|��|�Ļ�)",
		"(һ��)(.*)(��)",
		"(��Ȼ|����|��|���)(.*)(��|��)",
		"(ֻҪ)(.*)(��|��|��|��)",
		"(ֻ��)(.*)(��|��)"
	};
	string pattern_1[] = { // �ɹ���������ʽ
		"(֮?����)(.*)(��Ϊ)",
		"(֮?����)(.*)(����)",
		"(֮?����)(.*)(Ե��)"
	};
	string pattern_2[] = { //���򵽹�����ʽ
		"(��Ϊ)(.*)(�Ӷ�)",
		"(��Ϊ)(.*)(Ϊ��)",
		"(��Ȼ)(.*)(����)",
		"(����)(.*)(Ϊ��)",
		"(����)(.*)(��)",
		"(ֻ��)(.*)(��)",
		"(����)(,*)(������?)",
		"(��[Ȼ]?)(.*)(ȴ)",
		"(���)(.*)(��ô)",
		"(���)(.*)(��)",
		"(����)(.*)(�Ӷ�)",
		"(��Ȼ?)(.*)(���)",
		"(���)(.*)(��)",
		"(ֻҪ)(.*)(��)",
		"(��Ϊ)(.*)(����)",
		"(����)(.*)(����)",
		"(��Ϊ)(.*)(���)",
		"(����)(.*)(��)",
		"(��Ϊ)(.*)(������?)",
		"(��Ϊ)(.*)(���)",
		"(����)(.*)(���)",
		"(��Ϊ)(.*)(����)",
		"(����)(.*)(��ʹ)",
		"(��Ϊ)(.*)(��ʹ)",
		"(����)(.*)(������?)",
		"(��Ϊ)(.*)(��)",
		"(��[Ϊ]?)(.*)(������?)",
		"(����)(.*)(����)",
		"(��Ϊ)(.*)(�ʶ�)",
		"(����)(.*)(���)"
		};
	string pattern_3 = "(����|����|��|��ʹ|������?|���|������?|�Ӷ�|���)"; // ���򵽹�����ʽ��ȷ	
	string pattern_4[] = { //���򵽹�����ʽ��ȷ
		"(ǣ��|����|����|ʹ��|����|����|����|ָ��|ʹ|����|����|�ٳ�)",
		"(���|����|���|��ʹ|���|����|��͸|�ٽ�|����|�յ�|����|�ٷ�)",
		"(����|�շ�|�ƽ�|����|�ƶ�|����|Ӱ��|��ʹ|����|����|����|ʹ��)",
		"(����|����|����|����|��Ⱦ|����|Ю��|����|��ϵ|����|�ջ�|����|��ʹ)"
	};
	string pattern_5 = "(Ϊ��|����|����|��Ϊ|��|��|����|ƾ��|����)";// ���򵽹�ǰ��ʽģ��
	string pattern_6 = "(����|�Ա�|Ϊ��|��)";// ���򵽹�����ʽģ��
	string pattern_7 = "(��Ȼ?|��|��Ϊ|���|����|ֻҪ)";// ���򵽹�ǰ��ʽ��ȷ
	string pattern_8 = "(��Դ��|ȡ��|��Դ��|����|ȡ����|Ե��|����|����|��Դ��|����|��Դ��|����|Դ��|��Դ��|����|������)";
	// �ɹ��������ʽģ��
	string pattern_9 = "��?(��Ϊ|����)";// �ɹ�����Ӷ�ʽ��ȷ

	vector<string> pattern_but_temp(pattern_but, pattern_but + 17);
	for (vector<string>::iterator pattern = pattern_but_temp.begin(); pattern != pattern_but_temp.end(); ++pattern) //ת��ģʽƥ��
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
	for (vector<string>::iterator pattern = pattern_seq_temp.begin(); pattern != pattern_seq_temp.end(); ++pattern) //˳��ģʽƥ��
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
	for (vector<string>::iterator pattern = pattern_more_temp.begin(); pattern != pattern_more_temp.end(); ++pattern) //����ģʽƥ��
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
	for (vector<string>::iterator pattern = pattern_condition_temp.begin(); pattern != pattern_condition_temp.end(); ++pattern) //����ģʽƥ��
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
	for (vector<string>::iterator pattern = pattern_1_temp.begin(); pattern != pattern_1_temp.end(); ++pattern) //�ɹ���������ʽ ģʽƥ��
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
	for (vector<string>::iterator pattern = pattern_2_temp.begin(); pattern != pattern_2_temp.end(); ++pattern) // ���򵽹�����ʽƥ��ģʽ
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
	if (pattern_o(line, keyword1, keyword2, pattern_3, result_temp))// ���򵽹�����ʽ��ȷƥ��ģʽ
		judge = true;
	if (judge)
	{
		cout << "pattern_3\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	vector<string> pattern_4_temp(pattern_4, pattern_4 + 4);
	for (vector<string>::iterator pattern = pattern_4_temp.begin(); pattern != pattern_4_temp.end(); ++pattern) {
		if (pattern_o(line, keyword1, keyword2, *pattern, result_temp))//���򵽹�����ʽ��ȷƥ��ģʽ
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
	if (pattern_o(line, keyword1, keyword2, pattern_5, result_temp))// ���򵽹�ǰ��ʽģ��ƥ��ģʽ
		judge = true;
	if (judge)
	{
		cout << "pattern_5\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_6, result_temp)) //���򵽹�����ʽģ��ƥ��ģʽ
		judge = true;
	if (judge)
	{
		cout << "pattern_6\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_7, result_temp)) // ���򵽹�ǰ��ʽ��ȷƥ��ģʽ
		judge = true;
	if (judge)
	{
		cout << "pattern_7\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_8, result_temp)) //�ɹ��������ʽģ��ƥ��ģʽ
		judge = true;
	if (judge)
	{
		cout << "pattern_8\n";
		strcpy(result, const_cast<char *> (result_temp.c_str()));
		return 1;
	}
	if (pattern_o(line, keyword1, keyword2, pattern_9, result_temp)) //�ɹ�����Ӷ�ʽ��ȷƥ��ģʽ
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
