#define _K参数_ 13
#define _世界大小_X_ 20
#define _世界大小_Y_ 20
#define _正例个数_ 5
#define _负例个数_ 5

#if _K参数_>(_正例个数_+_负例个数_)
	#define _K参数_ _正例个数_+_负例个数_
#endif
#if (_正例个数_+_负例个数_)>(_世界大小_X_*_世界大小_Y_)
	#error "逗我？！"
#endif

#include <iostream>

typedef struct 样本struct 样本struct;
typedef unsigned int uint;

enum 类型{ 空, 正例, 负例, 正判定, 负判定 };

struct 样本struct
{
	uint X;
	uint Y;
	int Distance;
};

类型 World[_世界大小_X_][_世界大小_Y_];
样本struct 样本[_正例个数_ + _负例个数_];
int K = _K参数_;

void Display();
void 生成初始样本();
void 计算距离(uint _X, uint _Y);
void 以距离为基准排序();
void 清空距离();

void main()
{
	

}

void Display()
{
	for (int i = 0; i < _世界大小_X_; i++)
	{
		for(int j=0;j<_世界大小_Y_;j++)
			switch (World[i][j])
			{
			case 正例:
				std::cout << "@ ";
				break;
			case 负例:
				std::cout << "X ";
				break;
			case 正判定:
				std::cout << "o ";
				break;
			case 负判定:
				std::cout << "x ";
				break;
			default:
				std::cout << "  ";
				break;
			}
		std::cout << std::endl;
	}
}

void 生成初始样本()
{

}