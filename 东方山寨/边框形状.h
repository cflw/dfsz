#pragma once
#include "边框基础.h"
namespace 东方山寨::边框 {
//==============================================================================
// 矩形边框
//==============================================================================
class C矩形 : public I边框 {
public:
	static const C矩形 c标准, c窗口;
	C矩形();
	C矩形(const t矩形 &);
	//边框
	bool f判断(const t向量2 &坐标, float 外偏移) const override;
	int f反弹(t向量2 &坐标, t向量2 &速度, float 外偏移, int 次数 = c最大次数) const override;
	int f限制(t向量2 &坐标, float 外偏移, int 次数 = c最大次数) const override;
	void f显示(const S画边框参数 &) const override;
	//判断
	bool f左边判断(const t向量2 &, float 外偏移) const;
	bool f右边判断(const t向量2 &, float 外偏移) const;
	bool f上边判断(const t向量2 &, float 外偏移) const;
	bool f下边判断(const t向量2 &, float 外偏移) const;
	//限制
	bool f左边限制(t向量2 &, float 外偏移) const;
	bool f右边限制(t向量2 &, float 外偏移) const;
	bool f上边限制(t向量2 &, float 外偏移) const;
	bool f下边限制(t向量2 &, float 外偏移) const;
	bool f左右限制(t向量2 &, float 外偏移) const;
	bool f上下限制(t向量2 &, float 外偏移) const;
	//反弹
	bool f左边反弹(t向量2 &, t向量2 &, float 外偏移) const;
	bool f右边反弹(t向量2 &, t向量2 &, float 外偏移) const;
	bool f上边反弹(t向量2 &, t向量2 &, float 外偏移) const;
	bool f下边反弹(t向量2 &, t向量2 &, float 外偏移) const;
	bool f左右反弹(t向量2 &, t向量2 &, float 外偏移) const;
	bool f上下反弹(t向量2 &, t向量2 &, float 外偏移) const;
public:
	t矩形 m矩形;
};
//==============================================================================
// 圆形边框
//==============================================================================
class C圆形 : public I边框 {
public:
	static const C圆形 c标准;
	C圆形();
	C圆形(const t圆形 &);
	//边框
	bool f判断(const t向量2 &坐标, float 外偏移) const override;
	int f反弹(t向量2 &坐标, t向量2 &速度, float 外偏移, int 次数 = c最大次数) const override;
	int f限制(t向量2 &坐标, float 外偏移, int 次数 = c最大次数) const override;
	void f显示(const S画边框参数 &) const override;
public:
	t圆形 m圆形;
};
}	//namespace 东方山寨