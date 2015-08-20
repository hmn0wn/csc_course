// FILE neuro_bp.cpp FOR neuro1.prj & neuro2.prj

#include <stdlib.h>

//#include <alloc.h>

#include <math.h>

#include <string.h>

#include <stdarg.h>

#include <limits.h>

#include "neuro.h"

static float MiuParm = 0.0;

static float NiuParm = 0.1;

static float Limit = 0.000001;

static unsigned dSigma = 0;

float SetMiuParm(float Mi)

{

	float a;

	a = MiuParm;

	MiuParm = Mi;

	return a;

}

float SetNiuParm(float Ni)

{

	float a;

	a = NiuParm;

	NiuParm = Ni;

	return a;

}

float SetLimit(float Li)

{

	float a;

	a = Limit;

	Limit = Li;

	return a;

}

unsigned SetDSigma(unsigned d)

{

	unsigned u;

	u = dSigma;

	dSigma = d;

	return u;

}

void NeuronBP::_allocateNeuron(unsigned num_inputs)

{

	deltas = NULL;

	if (num_inputs == 0) return;

	deltas = new float[num_inputs];

	if (deltas == NULL) status = ERROR;

	else for (unsigned i = 0; i<rang; i++) deltas[i] = 0.;

}

NeuronBP::NeuronBP(unsigned num_inputs)

	:NeuronFF(num_inputs)

{

	_allocateNeuron(num_inputs);

}

void NeuronBP::_deallocate(void)

{

	if (deltas && (status == OK))

	{
		delete[] deltas; deltas = NULL;
	}

}

NeuronBP::~NeuronBP()

{

	_deallocate();

}

void NeuronBP::InitNeuron(unsigned num_inputs)

{

	NeuronFF::InitNeuron(num_inputs);

	if (deltas && (status == OK)) delete[] deltas;

	_allocateNeuron(num_inputs);

}

int NeuronBP::IsConverged(void)

{

	for (unsigned i = 0; i<rang; i++)

		if (fabs(deltas[i])>Limit) return 0;

	return 1;

}

//

LayerBP::LayerBP(unsigned nRang, unsigned nSynapses)

{

	allocation = EXTERN; status = ERROR; neuronrang = 0;

	if (nRang == 0) return;

	neurons = new NeuronBP[nRang];

	if (neurons == NULL) return;

	for (unsigned i = 0; i<nRang; i++)

		neurons[i].InitNeuron(nSynapses);

	rang = nRang;

	neuronrang = nSynapses;

	allocation = INNER;

	name = NULL; status = OK;

}

LayerBP::LayerBP(NeuronBP *Neu, unsigned nRang,

	unsigned nSynapses)

{

	neurons = NULL; neuronrang = 0; allocation = EXTERN;

	for (unsigned i = 0; i<nRang; i++)

		if (Neu[i].rang != nSynapses) status = ERROR;

	if (status == OK)

	{

		neurons = Neu;

		rang = nRang;

		neuronrang = nSynapses;

	}

}

LayerBP::~LayerBP(void)

{

	if (allocation == INNER)

	{

		for (unsigned i = 0; i<rang; i++)

			neurons[i]._deallocate();

		delete[] neurons; neurons = NULL;

	}

}

void LayerBP::Propagate(void)

{

	for (unsigned i = 0; i<rang; i++)

		neurons[i].Propagate();

}

void LayerBP::Update(void)

{

	for (unsigned i = 0; i<rang; i++)

	{

		for (unsigned j = 0; j<neuronrang; j++)

			neurons[i].synapses[j] -= neurons[i].deltas[j];

	}

}

void LayerBP::Randomize(float range)

{

	for (unsigned i = 0; i<rang; i++)

		neurons[i].Randomize(range);

}

void LayerBP::RandomizeAxons(void)

{

	for (unsigned i = 0; i<rang; i++)

		neurons[i].RandomizeAxon();

}

void LayerBP::Normalize(void)

{

	float sum;

	unsigned i;

	for (i = 0; i<rang; i++)

		sum += neurons[i].axon*neurons[i].axon;

	sum = sqrt(sum);

	for (i = 0; i<rang; i++) neurons[i].axon /= sum;

}

void LayerBP::Show(void)

{

	unsigned char sym[5] = { GRAFCHAR_EMPTYBLACK, GRAFCHAR_DARKGRAY, GRAFCHAR_MIDDLEGRAY, GRAFCHAR_LIGHTGRAY, GRAFCHAR_SOLIDWHITE };

	int i, j;

	if (y && name) for (i = 0; i<strlen((const char*)name); i++)

		out_char(x + i, y - 1, name[i], 3);

	out_char(x, y, GRAFCHAR_UPPERLEFTCORNER, 15);

	for (i = 0; i<2 * dx; i++)

		out_char(x + 1 + i, y, GRAFCHAR_HORIZONTALLINE, 15);

	out_char(x + 1 + i, y, GRAFCHAR_UPPERRIGHTCORNER, 15);

	for (j = 0; j<dy; j++)

	{

		out_char(x, y + 1 + j, GRAFCHAR_VERTICALLINE, 15);

		for (i = 0; i<2 * dx; i++) out_char(x + 1 + i, y + 1 + j,

			sym[(int)((neurons[j*dx + i / 2].axon + 0.4999) * 5)], 15);

		out_char(x + 1 + i, y + 1 + j, GRAFCHAR_VERTICALLINE, 15);

	}

	out_char(x, y + j + 1, GRAFCHAR_BOTTOMLEFTCORNER, 15);

	for (i = 0; i<2 * dx; i++)

		out_char(x + i + 1, y + j + 1, GRAFCHAR_HORIZONTALLINE, 15);

	out_char(x + 1 + i, y + j + 1, GRAFCHAR_BOTTOMRIGHTCORNER, 15);

}

void LayerBP::PrintSynapses(int x, int y)

{

	for (unsigned i = 0; i<rang; i++)

		neurons[i].PrintSynapses(x, y + i);

}

void LayerBP::PrintAxons(int x, int y)

{

	for (unsigned i = 0; i<rang; i++)

		neurons[i].PrintAxons(x, y + i);

}

int LayerBP::IsConverged(void)

{

	for (unsigned i = 0; i<rang; i++)

		if (neurons[i].IsConverged() == 0) return 0;

	return 1;

}

//

NetBP::NetBP(unsigned nLayers)

{

	layers = NULL;

	if (nLayers == 0) { status = ERROR; return; }

	layers = new LayerBP *[nLayers];

	if (layers == NULL) status = ERROR;

	else

	{

		rang = nLayers;

		for (unsigned i = 0; i<rang; i++) layers[i] = NULL;

	}

}

NetBP::~NetBP()

{

	if (rang)

	{

		for (unsigned i = 0; i<rang; i++) layers[i]->~LayerBP();

		delete[] layers; layers = NULL;

	}

}

int NetBP::SetLayer(unsigned n, LayerBP * pl)

{

	unsigned i, p;

	if (n >= rang) return 1;

	p = pl->rang;

	if (p == 0) return 2;

	if (n) // если не первый слой

	{

		if (layers[n - 1] != NULL)

			// если предыдущий слой уже подключен, про-

		{ // веряем, равно ли число синапсов каждого

			// его нейрона числу нейронов предыд. слоя

			for (i = 0; i<p; i++)

				if ((*pl).neurons[i].rang != layers[n - 1]->rang)

					return 3;

		}

	}

	if (n<rang - 1) // если не последний слой

	{

		if (layers[n + 1])

			for (i = 0; i<layers[n + 1]->rang; i++)

				if (p != layers[n + 1]->neurons[i].rang) return 4;

	}

	layers[n] = pl;

	return 0;

}

void NetBP::Propagate(void)

{

	for (unsigned i = 1; i<rang; i++)

		layers[i]->Propagate();

}

int NetBP::FullConnect(void)

{

	LayerBP *l;

	unsigned i, j, k, n;

	for (i = 1; i<rang; i++) // кроме входного слоя

	{ // по всем слоям

		l = layers[i];

		if (l->rang == 0) return 1;

		n = (*layers[i - 1]).rang;

		if (n == 0) return 2;

		for (j = 0; j<l->rang; j++) // по нейронам слоя

		{

			for (k = 0; k<n; k++) // по синапсам нейрона

			{

				l->neurons[j].inputs[k] =

					&(layers[i - 1]->neurons[k].axon);

			}

		}

	}

	return 0;

}

void NetBP::SetNetInputs(float *mv)

{

	for (unsigned i = 0; i<layers[0]->rang; i++)

		layers[0]->neurons[i].axon = mv[i];

}

void NetBP::CalculateError(float * Target)

{

	NeuronBP *n;

	float sum;

	unsigned i;

	int j;

	for (i = 0; i<layers[rang - 1]->rang; i++)

	{

		n = &(layers[rang - 1]->neurons[i]);

		n->error = (n->axon - Target[i])*n->D_Sigmoid();

	}

	for (j = rang - 2; j>0; j--) // по скрытым слоям

	{

		for (i = 0; i<layers[j]->rang; i++) // по нейронам

		{

			sum = 0.;

			for (unsigned k = 0; k<layers[j + 1]->rang; k++)

				sum += layers[j + 1]->neurons[k].error

				*layers[j + 1]->neurons[k].synapses[i];

			layers[j]->neurons[i].error =

				sum*layers[j]->neurons[i].D_Sigmoid();

		}

	}

}

void NetBP::Learn(void)

{

	for (int j = rang - 1; j>0; j--)

	{

		for (unsigned i = 0; i<layers[j]->rang; i++)

		{ // по нейронам

			for (unsigned k = 0; k<layers[j]->neuronrang; k++)

				// по синапсам

				layers[j]->neurons[i].deltas[k] = NiuParm*

				(MiuParm*layers[j]->neurons[i].deltas[k] +

				(1. - MiuParm)*layers[j]->neurons[i].error

				*layers[j - 1]->neurons[k].axon);

		}

	}

}

void NetBP::Update(void)

{

	for (unsigned i = 0; i<rang; i++) layers[i]->Update();

}

void NetBP::Randomize(float range)

{

	for (unsigned i = 0; i<rang; i++)

		layers[i]->Randomize(range);

}

void NetBP::Cycle(float *Inp, float *Out)

{

	SetNetInputs(Inp);

	if (dSigma) AddNoise();

	Propagate();

	CalculateError(Out);

	Learn();

	Update();

}

int NetBP::SaveToFile(unsigned char *file)

{

	FILE *fp;

	fopen_s(&fp,(const char*)file, "wt");

	if (fp == NULL) return 1;

	fprintf(fp, "%u", rang);

	for (unsigned i = 0; i<rang; i++)

	{

		fprintf(fp, "\n+%u", layers[i]->rang);

		fprintf(fp, "\n¦%u", layers[i]->neuronrang);

		for (unsigned j = 0; j<layers[i]->rang; j++)

		{

			fprintf(fp, "\n¦+%f", layers[i]->neurons[j].state);

			fprintf(fp, "\n¦¦%f", layers[i]->neurons[j].axon);

			fprintf(fp, "\n¦¦%f", layers[i]->neurons[j].error);

			for (unsigned k = 0; k<layers[i]->neuronrang; k++)

			{

				fprintf(fp, "\n¦¦%f",

					layers[i]->neurons[j].synapses[k]);

			}

			fprintf(fp, "\n¦+");

		}

		fprintf(fp, "\n+");

	}

	fclose(fp);

	return 0;

}

int NetBP::LoadFromFile(unsigned char *file)

{

	FILE *fp;

	unsigned i, r, nr;

	unsigned char bf[12];

	if (layers) return 1; // возможно использование только

	// экземпляров класса, сконструированных по умолчанию

	// с помощью NetBP(void).

	fopen_s(&fp,(const char*)file, "rt");

	if (fp == NULL) return 1;

	fscanf_s(fp, "%u\n", &r);

	if (r == 0) goto allerr;

	layers = new LayerBP *[r];

	if (layers == NULL)

	{
	allerr: status = ERROR; fclose(fp); return 2;
	}

	else

	{

		rang = r;

		for (i = 0; i<rang; i++) layers[i] = NULL;

	}

	for (i = 0; i<rang; i++)

	{

		fgets((char *)bf, 10, fp);

		r = atoi((char *)bf + 1);

		fgets((char *)bf, 10, fp);

		nr = atoi((char *)bf + 1);

		layers[i] = new LayerBP(r, nr);

		for (unsigned j = 0; j<layers[i]->rang; j++)

		{

			fscanf_s(fp, "¦+%f\n", &(layers[i]->neurons[j].state));

			fscanf_s(fp, "¦¦%f\n", &(layers[i]->neurons[j].axon));

			fscanf_s(fp, "¦¦%f\n", &(layers[i]->neurons[j].error));

			for (unsigned k = 0; k<layers[i]->neuronrang; k++)

			{

				fscanf_s(fp, "¦¦%f\n", &(layers[i]->neurons[j].synapses[k]));

			}

			fgets((char *)bf, 10, fp);

		}

		fgets((char *)bf, 10, fp);

	}

	fclose(fp);

	return 0;

}

NetBP::NetBP(unsigned n, unsigned n1, ...)

{

	unsigned i, num, prenum;

	va_list varlist;

	status = OK; rang = 0; pf = NULL; learncycle = 0; layers = NULL;

	layers = new LayerBP *[n];

	if (layers == NULL) { allerr: status = ERROR; }

	else

	{

		rang = n;

		for (i = 0; i<rang; i++) layers[i] = NULL;

		num = n1;

		layers[0] = new LayerBP(num, 0);

		va_start(varlist, n1);

		for (i = 1; i<rang; i++)

		{

			prenum = num;

			num = va_arg(varlist, unsigned);

			layers[i] = new LayerBP(num, prenum);

		}

		va_end(varlist);

	}

}

int NetBP::LoadNextPattern(float *IN,

	float *OU)

{

	unsigned char buf[256];

	unsigned char *s, *ps;

	int i;

	if (pf == NULL) return 1;

	if (imgfile)

	{

	restart:

		for (i = 0; i<layers[0]->dy; i++)

		{

			if (fgets((char *)buf, 256, pf) == NULL)

			{

				if (learncycle)

				{

					rewind(pf);

					learncycle--;

					goto restart;

				}

				else return 2;

			}

			for (int j = 0; j<layers[0]->dx; j++)

			{

				if (buf[j] == 'x') IN[i*layers[0]->dx + j] = 0.5;

				else if (buf[j] == '.') IN[i*layers[0]->dx + j] = -0.5;

			}

		}

		if (fgets((char *)buf, 256, pf) == NULL) return 3;

		for (i = 0; i<layers[rang - 1]->rang; i++)

		{

			if (buf[i] != '.') OU[i] = 0.5;

			else OU[i] = -0.5;

		}

		return 0;

	}

	// "scanf often leads to unexpected results

	// if you diverge from an expected pattern." (!)

	// Borland C On-line Help

start:

	if (fgets((char *)buf, 250, pf) == NULL)

	{

		if (learncycle)

		{

			rewind(pf);

			learncycle--;

			goto start;

		}

		else return 2;

	}

	s = buf;

	for (; *s == ' '; s++);

	for (i = 0; i<layers[0]->rang; i++)

	{

		ps = strchr()
			((unsigned char*)s, ' ');

		if (ps) *ps = 0;

		IN[i] = atof(s);

		s = ps + 1; for (; *s == ' '; s++);

	}

	if (fgets((char *)buf, 250, pf) == NULL) return 4;

	s = buf;

	for (; *s == ' '; s++);

	for (i = 0; i<layers[rang - 1]->rang; i++)

	{

		ps = strchr(s, ' ');

		if (ps) *ps = 0;

		OU[i] = atof(s);

		s = ps + 1; for (; *s == ' '; s++);

	}

	return 0;

}

int NetBP::IsConverged(void)

{

	for (unsigned i = 1; i<rang; i++)

		if (layers[i]->IsConverged() == 0) return 0;

	return 1;

}

float NetBP::Change(float In)

{

	// для бинарного случая

	if (In == 0.5) return -0.5;

	else return 0.5;

}

void NetBP::AddNoise(void)

{

	unsigned i, k;

	for (i = 0; i<dSigma; i++)

	{

		k = random(layers[0]->rang);

		layers[0]->neurons[k].axon =

			Change(layers[0]->neurons[k].axon);

	}

}