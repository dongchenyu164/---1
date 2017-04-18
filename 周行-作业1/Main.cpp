#define _K参数_ 7
#define _世界大小_X_ 20
#define _世界大小_Y_ 20
#define _正例个数_ 13
#define _负例个数_ 25

#if _K参数_>(_正例个数_+_负例个数_)
	#undef _K参数_
	#define _K参数_ _正例个数_+_负例个数_
#endif
#if (_K参数_%2)==0
	#error "K参数不能为偶数"
#endif
#if (_正例个数_+_负例个数_)>(_世界大小_X_*_世界大小_Y_)
	#error "逗我？！"
#endif

#include <iostream>
#include <ctime>
#include <cstdlib>

typedef struct 样本struct 样本struct;
typedef unsigned int uint;

enum 类型 { 空 = 0, 正例, 负例, 正判定, 负判定 };

struct 样本struct
{
	uint X;
	uint Y;
	类型 Type;
	uint Distance;
};

类型 World[_世界大小_X_][_世界大小_Y_];
样本struct 样本[_正例个数_ + _负例个数_];
int K = _K参数_;

void SetSimpleDataToWorld();
void Display();
bool 是否重复(uint _X, uint _Y);
void 生成初始样本();
void 计算距离(uint _X, uint _Y);
void 以距离为基准排序();
void 判断该点的类型(uint _X, uint _Y);
void 清空距离();

int main()
{
	生成初始样本();
	SetSimpleDataToWorld();

	for (int i = 0; i < _世界大小_X_; i++)
	{
		for (int j = 0; j < _世界大小_Y_; j++)
			switch (World[i][j])
			{
			case 正例 :
				break;
			case 负例 :
				break;
			default:
				判断该点的类型(i,j);
				break;
			}
	}
	
	Display();
	return 0;
}

void SetSimpleDataToWorld()
{
	for (int i = 0; i < (_正例个数_ + _负例个数_); i++)
	{
		World[样本[i].X][样本[i].Y] = 样本[i].Type;
	}
}
void Display()
{
	for (int i = 0; i < _世界大小_X_; i++)
	{
		for (int j = 0; j < _世界大小_Y_; j++)
			switch (World[i][j])
			{
			case 正例:
				std::cout << "@ ";
				break;
			case 负例:
				std::cout << "1 ";
				break;
			case 正判定:
				std::cout << "o ";
				break;
			case 负判定:
				std::cout << "x ";
				break;
			default:
				std::cout << "- ";
				break;
			}
		std::cout << std::endl;
	}
}

uint 当前数据生成数 = 0;
bool 是否重复(uint _X, uint _Y)
{
	for (uint i = 0; i < 当前数据生成数; i++)
	{
		if (样本[i].X == _X && 样本[i].Y == _Y)
			return true;
	}
	return false;
}
uint 随机数生成(uint start, uint end)
{
	return (start + (end - start) * rand() / (RAND_MAX + 1.0));
}
void 生成初始样本()
{
	uint _t_X = 0, _t_Y = 0;
	srand(unsigned(time(0)));

	for (int i = 0; i < (_正例个数_ + _负例个数_); i++)
	{
		do
		{
			_t_X = 随机数生成(0, _世界大小_X_);
			_t_Y = 随机数生成(0, _世界大小_Y_);
		}
		while (是否重复(_t_X, _t_Y));

		样本[i].X = _t_X;
		样本[i].Y = _t_Y;
		if (i < _正例个数_)
			样本[i].Type = 正例;
		else
			样本[i].Type = 负例;

		当前数据生成数++;
	}
	当前数据生成数 = 0;//使命结束，所以归零。
}

void 计算距离(uint _X, uint _Y)
{
	for (int i = 0; i < (_正例个数_ + _负例个数_); i++)
		样本[i].Distance = (样本[i].X - _X)*(样本[i].X - _X) + (样本[i].Y - _Y)*(样本[i].Y - _Y);
}
void 清空距离()
{
	for (int i = 0; i < (_正例个数_ + _负例个数_); i++)
		样本[i].Distance = 0;
}
void 交换两个样本(样本struct* _A, 样本struct* _B)
{
	uint _TA = 0;
	类型 _TB;
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
void 以距离为基准排序()
{
	for (int i = 0; i < (_正例个数_ + _负例个数_)-1; i++)
	{
		for (int j = i+1; j < (_正例个数_ + _负例个数_); j++)
		{
			if (样本[i].Distance > 样本[j].Distance)
				交换两个样本(&样本[i], &样本[j]);
		}
	}
}
void 判断该点的类型(uint _X, uint _Y)
{
	int 正例计数 = 0, 负例计数 = 0;
	计算距离(_X, _Y);
	以距离为基准排序();
	for (int i = 0; i < (_K参数_); i++)
	{
		if (样本[i].Type == 正例)
			正例计数++;
		else if(样本[i].Type == 负例)
			负例计数++;
	}
	if (正例计数 > 负例计数)
		World[_X][_Y] = 正判定;
	else
		World[_X][_Y] = 负判定;
}