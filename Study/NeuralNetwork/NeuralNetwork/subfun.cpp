// FILE subfun.cpp FOR neuro1.prj & neuro2.prj

#include <string.h>

#include <math.h>

//#include <values.h>
#include <limits.h>

#include "neuro.h"

#define vad(x,y) ((y)*160+(x)*2)

void out_char(int x, int y, int c, int at)

{

	unsigned char *p;

	p = (unsigned char*)(0xB8000000L + (unsigned long)vad(x, y));

	*p = (c & 255) | (at << 8);

}

void out_str(int x, int y, unsigned char *s, unsigned col)

{

	for (int i = 0; i<strlen((const char*)s); i++) out_char(x + i, y, s[i], col);

}

void ClearScreen(void)

{

	for (int i = 0; i<80; i++) for (int j = 0; j<25; j++)

		out_char(i, j, ' ', 7);

}
/*
int matherr(struct exception *pe)

{

	if (strcmp(pe->name, "exp") == 0)

	{

		if (pe->type == OVERFLOW) pe->retval = MAXDOUBLE;

		if (pe->type == UNDERFLOW) pe->retval = MINDOUBLE;

		return 10;

	}

	else

	{

		if (pe->type == UNDERFLOW || pe->type == TLOSS) return 1;

		else return 0;

	}

}*/

int SomeNet::OpenPatternFile(unsigned char *file)

{

	fopen_s(&pf,(const char*)file, "rt");

	if (strstr((const char*)file, ".img")) imgfile = 1;

	else imgfile = 0;

	return !((int)pf);

}

int SomeNet::ClosePatternFile(void)

{

	int i;

	if (pf)

	{

		i = fclose(pf);

		pf = NULL;

		return i;

	}

	return 0;

}