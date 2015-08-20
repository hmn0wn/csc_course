
#include <stdio.h>

#define OK 0 // состояния объектов

#define ERROR 1

#define ORIGINAL 0 // типы активационных функций

#define HYPERTAN 1

#define HARDLIMIT 2

#define THRESHOLD 3

#define INNER 0 // тип распределения памяти

#define EXTERN 1

#define HORIZONTAL 1

#define VERTICAL 0

#ifndef max

#define max(a,b) (((a) > (b)) ? (a) : (b))

#define min(a,b) (((a) < (b)) ? (a) : (b))

#endif

// базовый класс нейронов для большинства сетей

class Neuron

{

protected:
	float state; // состояние
	float axon; // выход
	int status; // признак ошибки

public:
	Neuron(void){ state = 0.; axon = 0.; status = OK; };
	virtual float Sigmoid(void) = 0;
	int GetStatus(void){ return status; };

};

class SomeNet

{

protected:
	FILE *pf;
	int imgfile; // 0 - числа; 1 - 2D; 2 - эмуляция
	unsigned rang;
	int status;
	unsigned learncycle;

	int(*emuf)(int n, float *in, float *ou);

public:

	SomeNet(void)

	{
		pf = NULL; imgfile = 0; rang = 0; status = OK; learncycle = 0;
	};

	unsigned GetRang(void){ return rang; };

	void SetLearnCycle(unsigned l){ learncycle = l; };

	int OpenPatternFile(unsigned char *file);

	int ClosePatternFile(void);

	void EmulatePatternFile(int(*p)(int n,		float *, float *))

	{
		emuf = p; imgfile = 2;
	};

	int GetStatus(void){ return status; };

};

class LayerBP;

class NetBP;

// нейрон для полносвязной сети прямого распространения

class NeuronFF : public Neuron

{

protected:

	unsigned rang; // число весов

	float* synapses; // веса

	float **inputs;

	// массив указателей на выходы нейронов предыд. слоя

	void _allocateNeuron(unsigned);

	void _deallocate(void);

public:

	NeuronFF(unsigned num_inputs);

	NeuronFF(void){
		rang = 0; synapses = NULL;

		inputs = NULL; status = OK;
	};

	~NeuronFF();

	virtual void Propagate(void);

	void SetInputs(float *massive);

	void InitNeuron(unsigned numsynapses);

	virtual void RandomizeAxon(void);

	virtual void Randomize(float);

	virtual float Sigmoid(void);

	virtual float D_Sigmoid(void);

	virtual void PrintSynapses(int, int);

	virtual void PrintAxons(int, int);

};

class NeuronBP : public NeuronFF

{
	friend LayerBP;

	friend NetBP;

	float error;

	float *deltas; // изменения весов

	void _allocateNeuron(unsigned);

	void _deallocate(void);

public:

	NeuronBP(unsigned num_inputs);

	NeuronBP(void){ deltas = NULL; error = 0.; };

	~NeuronBP();

	void InitNeuron(unsigned numsynapses);

	int IsConverged(void);

};

class LayerFF

{

protected:

	unsigned rang;

	int status;

	int x, y, dx, dy;

	unsigned char *name; // имя слоя

public:

	LayerFF(void) { rang = 0; name = NULL; status = OK; };

	unsigned GetRang(void){ return rang; };

	void SetShowDim(int _x, int _y, int _dx, int _dy)

	{
		x = _x; y = _y; dx = _dx; dy = _dy;
	};

	void SetName(unsigned char *s) { name = s; };

	unsigned char *GetName(void)

	{
		if (name) return name;

		else return (unsigned char *)&("NoName");
	};

	int GetStatus(void){ return status; };

	int GetX(void){ return x; };

	int GetY(void){ return y; };

	int GetDX(void){ return dx; };

	int GetDY(void){ return dy; };

};

class LayerBP : public LayerFF

{
	friend NetBP;

protected:

	unsigned neuronrang; // число синапсов в нейронах

	int allocation;

	NeuronBP *neurons;

public:

	LayerBP(unsigned nRang, unsigned nSinapses);

	LayerBP(NeuronBP *Neu, unsigned nRang,	unsigned nSinapses);

	LayerBP(void)

	{
		neurons = NULL; neuronrang = 0; allocation = EXTERN;
	};

	~LayerBP();

	void Propagate(void);

	void Randomize(float);

	void RandomizeAxons(void);

	void Normalize(void);

	void Update(void);

	int IsConverged(void);

	virtual void Show(void);

	virtual void PrintSynapses(int, int);

	virtual void PrintAxons(int x, int y/*, int direction*/);

};

class NetBP : public SomeNet

{

	LayerBP * *layers;

	// нулевой слой нейронов без синапсов реализует входы

public:

	NetBP(void) { layers = NULL; };

	NetBP(unsigned nLayers);

	NetBP(unsigned n, unsigned n1, ...);

	~NetBP();

	int SetLayer(unsigned n, LayerBP *pl);

	LayerBP *GetLayer(unsigned n)

	{
		if (n<rang) return layers[n]; else return NULL;
	}

	void Propagate(void);

	int FullConnect(void);

	void SetNetInputs(float *mvalue);

	void CalculateError(float * Target);

	void Learn(void);

	void Update(void);

	void Randomize(float);

	void Cycle(float *Inp, float *Out);

	int SaveToFile(unsigned char *file);

	int LoadFromFile(unsigned char *file);

	int LoadNextPattern(float *IN, float *OU);

	int IsConverged(void);

	void AddNoise(void);

	virtual void PrintSynapses(int x = 0, ...){};

	virtual float Change(float In);

};

// Сервисные функции

void out_char(int x, int y, int c, int at);

void out_str(int x, int y, unsigned char *s, unsigned col);

void ClearScreen(void);

// Глобальные параметры для обратного распространения

int SetSigmoidType(int st);

float SetSigmoidAlfa(float Al);

float SetMiuParm(float Mi);

float SetNiuParm(float Ni);

float SetLimit(float Li);

unsigned SetDSigma(unsigned d);

// Псевдографика

#define GRAFCHAR_UPPERLEFTCORNER 218

#define GRAFCHAR_UPPERRIGHTCORNER 191

#define GRAFCHAR_HORIZONTALLINE 196

#define GRAFCHAR_VERTICALLINE 179

#define GRAFCHAR_BOTTOMLEFTCORNER 192

#define GRAFCHAR_BOTTOMRIGHTCORNER 217

#define GRAFCHAR_EMPTYBLACK 32

#define GRAFCHAR_DARKGRAY 176

#define GRAFCHAR_MIDDLEGRAY 177

#define GRAFCHAR_LIGHTGRAY 178

#define GRAFCHAR_SOLIDWHITE 219

