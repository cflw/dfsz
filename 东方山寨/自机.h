#pragma once
#include "基础.h"
#include "基础_数组指针.h"
#include "图形引擎.h"
#include "图形_图片.h"
#include "玩家子弹发射基础.h"
#include "对象图形.h"
namespace 东方山寨 {
class C玩家;
struct S自机属性;
class C玩家子弹发射器;
class C自机 {
public:
	enum class E动画方向 {
		e中 = 0,
		e左 = -1,
		e右 = 1,
	};
	static constexpr float c判定半径 = 0.5f;
	static constexpr float c擦弹半径 = 32;
	static constexpr float c道具半径 = 32;
	static constexpr float c移动速度 = 360;
	static constexpr float c动画速度 = 8 / 120.f;
	static constexpr float c决死时间 = 0.2f;
	static constexpr float c无决死时间 = -9999;
	void f初始化_在关卡开始();
	void f初始化_图形(C缓冲数组<I图形缓冲> &);
	void f控制_移动(const t向量2 &方向键);	//0速度时也要调用
	void f发射_发射子弹();
	void f发射_停止发射子弹();
	void f计算();
	void f计算_移动范围限制();
	void f更新();
	void f绑定玩家(C玩家 &);
	//属性
	void fs自机属性(const S自机属性 *);
	const t向量2 &fg坐标() const;
	t圆形 fg判定点() const;
	t圆形 fg擦弹点() const;
	t圆形 fg吸道具点() const;
	t圆形 fg吃道具点() const;
	t向量2 fg移动预判(float a时间 = 1) const;
	float fg透明度() const;
	bool fi无敌() const;
	bool fi死亡() const;
	//状态
	void f中弹();	//在自机与子弹判定中调用
	void f复活();	//在玩家计算中调用
	void f出现();
	//其它
public:
	t向量2 m坐标;
	t向量2 m移动;
	const S自机属性 *m自机属性 = nullptr;
	float m无敌时间 = 0;
	float m决死时间 = c无决死时间;
	float m出生时间 = 0;
	const C游戏速度 *m游戏速度 = nullptr;
	std::unique_ptr<C玩家子弹发射器> m发射子弹;
	std::unique_ptr<I对象图形<C自机>> m图形;
};
struct S自机属性 : public S图片动画属性 {
	float m判定半径;
	float m擦弹半径;
	float m道具半径;
	float m移动速度;
	t扩展指针<I工厂<C玩家子弹发射器>> m发射子弹;
	t属性指针<S玩家子弹属性> m子弹属性;
};
}