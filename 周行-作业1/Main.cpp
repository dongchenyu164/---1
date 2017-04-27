#define _K_ 1
#define _WorldSize_X_ 20
#define _WorldSize_Y_ 20
#define _PSample_ 5
#define _QSample_ 5

#if _K_>(_PSample_+_QSample_)
#undef _K_
#define _K_ _PSample_+_QSample_
#endif
#if (_K_%2)==0
#error "K_Error"
#endif
#if (_PSample_+_QSample_)>(_WorldSize_X_*_WorldSize_Y_)
#error "Sample_Error"
#endif

#include <iostream>
#include <ctime>
#include <cstdlib>

enum type { empty = 0, PSample, QSample, P, Q };

typedef unsigned int uint;
typedef struct Samplestruct
{
	uint X;
	uint Y;
	uint Distance;
	type Type;
}SPS;

type World[_WorldSize_X_][_WorldSize_Y_];
SPS Sample[_PSample_ + _QSample_];
int K = _K_;

void SetSimpleDataToWorld()
{
	for (int i = 0; i < (_PSample_ + _QSample_); i++)
	{
		World[Sample[i].X][Sample[i].Y] = Sample[i].Type;
	}
}
void Display()
{
	for (int i = 0; i < _WorldSize_X_; i++)
	{
		for (int j = 0; j < _WorldSize_Y_; j++)
			switch (World[i][j])
			{
			case PSample:
				std::cout << "@ ";
				break;
			case QSample:
				std::cout << "X ";
				break;
			case P:
				std::cout << "o ";
				break;
			case Q:
				std::cout << "x ";
				break;
			default:
				std::cout << "- ";
				break;
			}
		std::cout << std::endl;
	}
}uint Space = 0;
bool RepeatCheck(uint _X, uint _Y)
{
	for (uint i = 0; i < Space; i++)
	{
		if (Sample[i].X == _X && Sample[i].Y == _Y)
			return true;
	}
	return false;
}
uint Roll(uint start, uint end)
{
	return (start + (end - start) * rand() / (RAND_MAX + 1.0));
}
void BGSampleSample()
{
	uint _t_X = 0, _t_Y = 0;
	srand(unsigned(time(0)));

	for (int i = 0; i < (_PSample_ + _QSample_); i++)
	{
		do
		{
			_t_X = Roll(0, _WorldSize_X_);
			_t_Y = Roll(0, _WorldSize_Y_);
		} while (RepeatCheck(_t_X, _t_Y));

		Sample[i].X = _t_X;
		Sample[i].Y = _t_Y;
		if (i < _PSample_)
			Sample[i].Type = PSample;
		else
			Sample[i].Type = QSample;

		Space++;
	}
	Space = 0;//Mission completed
}
void Distance(uint _X, uint _Y)
{
	for (int i = 0; i < (_PSample_ + _QSample_); i++)
		Sample[i].Distance = (Sample[i].X - _X)*(Sample[i].X - _X) + (Sample[i].Y - _Y)*(Sample[i].Y - _Y);
}
void Clear()
{
	for (int i = 0; i < (_PSample_ + _QSample_); i++)
		Sample[i].Distance = 0;
}
void ExchangeSample(SPS* _A, SPS* _B)
{
	uint _TA = 0;
	type _TB;
	_TA = _A->X;
	_A->X = _B->X;
	_B->X = _TA;

	_TA = _A->Y;
	_A->Y = _B->Y;
	_B->Y = _TA;

	_TA = _A->Distance;
	_A->Distance = _B->Distance;
	_B->Distance = _TA;

	_TB = _A->Type;
	_A->Type = _B->Type;
	_B->Type = _TB;
}
void DistanceRank()
{
	for (int i = 0; i < (_PSample_ + _QSample_) - 1; i++)
	{
		for (int j = i + 1; j < (_PSample_ + _QSample_); j++)
		{
			if (Sample[i].Distance > Sample[j].Distance)
				ExchangeSample(&Sample[i], &Sample[j]);
		}
	}
}
void TypeJudge(uint _X, uint _Y)
{
	int PSampleCount = 0, QSampleCount = 0;
	Distance(_X, _Y);
	DistanceRank();
	for (int i = 0; i < (_K_); i++)
	{
		if (Sample[i].Type == PSample)
			PSampleCount++;
		else if (Sample[i].Type == QSample)
			QSampleCount++;
	}
	if (PSampleCount > QSampleCount)
		World[_X][_Y] = P;
	else
		World[_X][_Y] = Q;
}

int main()
{
	BGSampleSample();
	SetSimpleDataToWorld();

	for (int i = 0; i < _WorldSize_X_; i++)
	{
		for (int j = 0; j < _WorldSize_Y_; j++)
			switch (World[i][j])
			{
			case PSample:
				break;
			case QSample:
				break;
			default:
				TypeJudge(i, j);
				break;
			}
	}

	Display();
	return 0;
}
