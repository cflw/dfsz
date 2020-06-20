#pragma once
#include "数学基础.h"
#include "图形包含.h"
namespace 东方山寨 {
constexpr int c最大次数 = 4;
//==============================================================================
// 边框接口
//==============================================================================
struct S画边框参数 {
	二维::C画图形 &m画图形;
	float m渐变;	//-1->0出现 0->1消失
};
class I边框 {
public:
	virtual bool f判断(const t向量2 &坐标, float 外偏移) const = 0;	//坐标在边框外返回true
	virtual int f反弹(t向量2 &坐标, t向量2 &速度, float 外偏移, int 次数 = c最大次数) const = 0;	//判断并反弹
	virtual int f限制(t向量2 &坐标, float 外偏移, int 次数 = c最大次数) const = 0;	//判断并限制
	virtual void f显示(const S画边框参数 &) const = 0;
};
class C边框管理 {
public:
	C边框管理();
	void f计算();
	void f显示() const;
	void f切换边框(const I边框 &);
	const I边框 *m边框 = nullptr;
};
}	//namespace 东方山寨