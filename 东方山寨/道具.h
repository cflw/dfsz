#pragma once
#include <cflw数学_随机.h>
#include "基础.h"
#include "基础_数组计数.h"
#include "标识.h"
#include "图形_图片.h"
#include "对象图形.h"
namespace 东方山寨 {
typedef uint16_t t道具数量;
class C玩家;
struct S道具属性;
//==============================================================================
// 道具
//==============================================================================
typedef std::function<void(const S道具属性 &, C玩家 &)> tf道具效果;
class C道具 {
public:
	enum E标志 {
		e使用
	};
	static constexpr float c下落加速度 = 64.f;
	static constexpr float c侧移加速度 = 10.f;
	static constexpr float c最大下落速度 = 64.f;
	static constexpr float c跟随加速度 = 254.f;
	static constexpr float c道具组半径 = 32.f;
	static constexpr float c初始上升速度 = 128.f;
	static constexpr float c动画渐变时间 = 0.2f;
	static constexpr float c初始速度渐变时间 = 1;
	C道具();
	~C道具();
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用();
	void f计算();
	void f更新();
	//属性
	t圆形 fg判定点() const;
	const S道具属性 &fg道具属性() const;
	void f效果(C玩家&);
	bool fi在窗口外() const;
	void fs跟随(C玩家 *玩家, float 时间);
	bool fi跟随() const;
	void f计算运动();
public:
	C数组计数 *m计数指针 = nullptr;
	const C游戏速度 *m游戏速度 = nullptr;
	t向量2 m坐标;
	t向量2 m速度;
	t向量2 m初始速度;
	float m速度插值 = 0;
	t标志 m标志;
	C玩家 *m跟随玩家 = nullptr;
	float m跟随进度 = 0;
	float m跟随速度 = 0;	//每次计算时直接加到进度上
	const S道具属性 *m道具属性 = nullptr;
	std::unique_ptr<I对象图形<C道具>> m图形;
};
struct S道具属性 : public S图片动画属性 {
	tf道具效果 mf效果;
	int m值;
	float m判定半径;
	float m最大透明度 = 1;
};
//==============================================================================
// 道具效果
//==============================================================================
namespace 道具效果 {
void f得分_固定(const S道具属性 &, C玩家 &);
void f得分_最大点(const S道具属性 &, C玩家 &);
void f残机_十分之一(const S道具属性 &, C玩家 &);
void f炸弹_十分之一(const S道具属性 &, C玩家 &);
void f火力_百分之一(const S道具属性 &, C玩家 &);
void f最大点(const S道具属性 &, C玩家 &);
}	//namespace 道具效果
}	//namespace 东方山寨
