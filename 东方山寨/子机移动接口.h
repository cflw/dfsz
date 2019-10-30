#pragma once
#include "数学包含.h"
namespace 东方山寨 {
class C玩家;
class C子机;
class I子机移动 {
public:
	virtual void f接口_计算() = 0;
	virtual void f接口_复位(int 数量) = 0;	//子机数量发生变化时调用
	virtual void f接口_绑定玩家(C玩家 &);
protected:
	void f初始化_绑定玩家(C玩家 &);
	std::vector<C子机> *va子机;	//多个子机
	const t向量2 *v自机坐标;	//自机坐标
	const int *v子机数量;	//子机实时数量
	const float *v低速渐变;	//玩家低速渐变
};
}