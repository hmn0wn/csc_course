//FILE neuro_ff.cpp FOR neuro1.prj & neuro2.prj

#include <stdlib.h>

#include <math.h>

#include "neuro.h"

static int SigmoidType = ORIGINAL;

static float SigmoidAlfa = 2.; // > 4 == HARDLIMIT

int SetSigmoidType(int st)

{

	int i;

	i = SigmoidType;

	SigmoidType = st;

	return i;

}

float SetSigmoidAlfa(float Al)

{

	float a;

	a = SigmoidAlfa;

	SigmoidAlfa = Al;

	return a;

}

void NeuronFF::Randomize(float range)

{

	for (unsigned i = 0; i<rang; i++)

		synapses[i] = range*((float)rand() / RAND_MAX - 0.5);

}

void NeuronFF::RandomizeAxon(void)

{

	axon = (float)rand() / RAND_MAX - 0.5;

}

float NeuronFF::D_Sigmoid(void)

{

	switch (SigmoidType)

	{

	case HYPERTAN: return (1. - axon*axon);

	case ORIGINAL: return SigmoidAlfa*(axon + 0.5)*

		(1.5 - axon);

	default: return 1.;

	}

}

float NeuronFF::Sigmoid(void)

{

	switch (SigmoidType)

	{

	case HYPERTAN: return 0.5*tanh(state);

	case ORIGINAL: return -0.5 + 1. /

		(1 + exp(-SigmoidAlfa*state));

	case HARDLIMIT:if (state>0) return 0.5;

				   else if (state<0) return -0.5;

				   else return state;

	case THRESHOLD:if (state>0.5) return 0.5;

				   else if (state<-0.5) return -0.5;

				   else return state;

	default: return 0.;

	}

}

void NeuronFF::_allocateNeuron(unsigned num_inputs)

{

	synapses = NULL; inputs = NULL; status = OK; rang = 0;

	if (num_inputs == 0) return;

	synapses = new float[num_inputs];

	if (synapses == NULL) status = ERROR;

	else

	{

		inputs = new float *[num_inputs];

		if (inputs == NULL) status = ERROR;

		else

		{

			rang = num_inputs;

			for (unsigned i = 0; i<rang; i++)

			{
				synapses[i] = 0.; inputs[i] = NULL;
			}

		}

	}

}

NeuronFF::NeuronFF(unsigned num_inputs)

{

	_allocateNeuron(num_inputs);

}

void NeuronFF::_deallocate(void)

{

	if (rang && (status == OK))

	{
		delete[] synapses; delete[] inputs;

		synapses = NULL; inputs = NULL;
	}

}

NeuronFF::~NeuronFF()

{

	_deallocate();

}

void NeuronFF::Propagate(void)

{

	state = 0.;

	for (unsigned i = 0; i<rang; i++)

		state += (*inputs[i] * 2)*(synapses[i] * 2);

	state /= 2;

	axon = Sigmoid();

}

void NeuronFF::SetInputs(float *vm)

{

	for (unsigned i = 0; i<rang; i++) inputs[i] = &vm[i];

}

void NeuronFF::InitNeuron(unsigned num_inputs)

{

	if (rang && (status == OK))

	{
		delete[] synapses; delete[] inputs;
	}

	_allocateNeuron(num_inputs);

}

void NeuronFF::PrintSynapses(int x = 0, int y = 0)

{

	unsigned char buf[20];

	for (unsigned i = 0; i<rang; i++)

	{

		printf((char*)buf, "%+7.2f", synapses[i]);

		out_str(x + 8 * i, y, buf, 11);

	}

}

void NeuronFF::PrintAxons(int x = 0, int y = 0)

{

	unsigned char buf[20];

	printf((char*)buf, "%+7.2f", axon);

	out_str(x, y, buf, 11);

}