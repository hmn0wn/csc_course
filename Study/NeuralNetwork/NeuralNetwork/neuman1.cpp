// FILE neuman1.cpp FOR neuro1.prj

#include <string.h>
#include <conio.h>
#include "neuro.h"
#define N0 30
#define N1 10
#define N2 10
void main()
{
	float Inp[N0], Out[N2];
	unsigned count;
	unsigned char buf[256];
	int i;
	NetBP N(3, N0, N1, N2);

	ClearScreen();

	N.FullConnect();

	N.GetLayer(0)->SetName((unsigned char*)"Input");
	N.GetLayer(0)->SetShowDim(1, 1, 5, 6);
	N.GetLayer(1)->SetName((unsigned char*)"Hidden");
	N.GetLayer(1)->SetShowDim(15, 1, 2, 5);
	N.GetLayer(2)->SetName((unsigned char*)"Out");
	N.GetLayer(2)->SetShowDim(23, 1, 10, 1);
	// srand(1);

	// меняем особенность случайной структуры сети

	SetSigmoidType(HYPERTAN);
	SetNiuParm(0.1);
	SetLimit(0.001);
	SetDSigma(1);
	N.Randomize(1);
	N.SetLearnCycle(64000U);
	N.OpenPatternFile((unsigned char*)"char1.img");
	for (count = 0;; count++)

	{

		printf((char*)buf, "Cycle %u", count);
		out_str(1, 23, buf, 10 | (1 << 4));
		out_str(1, 24, (unsigned char*)"ESC breaks ", 11 | (1 << 4));

		if (kbhit() || i == 13) i = getch();
		if (i == 27) break;
		if (i == 's' || i == 'S') goto save;
		if (N.LoadNextPattern(Inp, Out)) break;
		N.Cycle(Inp, Out);

		// N.Propagate(); // "сквозной канал"
		N.GetLayer(0)->Show();
		N.GetLayer(1)->Show();
		N.GetLayer(2)->Show();
		N.GetLayer(2)->PrintAxons(47, 0);

		if (count && N.IsConverged())
		{
			save:
			out_str(40, 24, (unsigned char*)"FileConf:", 15 | (1 << 4));
			gotoxy(50, 25);
			gets((char*)buf);
			if (strlen((char*)buf)) N.SaveToFile(buf);
			break;

		}

	}

	N.ClosePatternFile();

}