#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lastresult.h"

int main()
{

	char * result = new char[1024];
	char * test = "��Ϊ�����ǣ����Ե�������·��Ƶ����¸¸�";
	int start1 = 3;
	int end1 = 4;
	int start2 = 14;
	int end2 = 15;

	EVENT_GetRelation(test, start1, end1, start2, end2, result);

	fprintf(stderr, "%s\n", result);
	delete[]result;
	return 0;
}