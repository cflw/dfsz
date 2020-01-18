#pragma once
#include "基础.h"
#include "图形_图片.h"
#include "动画接口.h"
#include "对象图形.h"
namespace 东方山寨 {
struct S顶点矩形;
class C游戏速度;
class C数组计数;
struct S敌机属性;
//==============================================================================
// 敌机类
//==============================================================================
class C敌机 : public I事件 {
public:
	static constexpr float c判定半径 = 16.f;
	using tf运动 = std::function<t向量2(const C敌机 &)>;
	enum E标志 {
		e使用,
		e无动作,
		e王,
	};
	C敌机();
	~C敌机();
	C敌机(int 生命值);
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用() const;
	void f初始化();
	void f计算();
	void f更新();
	void f中弹(int 伤害);
	//属性
	const t向量2 &fg坐标() const;
	const S图片动画属性 &fg图片动画属性() const;
	float fg判定半径() const;
	t圆形 fg判定点() const;
	bool fi在窗口外() const;
	bool fi死亡() const;
	bool fi王() const;
	float fg移动方向x() const;
	float fg移动方向y() const;
	void fs生命值(int = 1, float 无敌 = 1);
	bool fi运动时间内(float) const;
	float f剩余运动时间(float) const;
	//运动
	void fs速度(const t向量2 &);
	void fs运动(const tf运动 &);
	void f运动_速度(const t向量2 &速度, float 时间 = 0);
	void f运动_限时移动到(const t向量2 &, float 时间, float 平滑开始时间 = 0, float 平滑结束时间 = 0);
	void f运动_限速移动到(const t向量2 &, float 速度, float 平滑开始时间 = 0, float 平滑结束时间 = 0);
	void f运动_限时移动过(const t向量2 &, float 时间, float 平滑开始时间 = 0);
	void f运动_限速移动过(const t向量2 &, float 速度, float 平滑开始时间 = 0);
	void f运动_平滑移动到(const t向量2 &, float 总时间, float 平滑开始时间 = 0.5f, float 平滑结束时间 = 0.5f);
	void f运动_平滑移动过(const t向量2 &, float 总时间, float 平滑开始时间 = 0.5f);
	void f运动_相对横坐标随机移动(float 横坐标, float 横平均, float 横浮动, float 纵平均 = 100, float 纵浮动 = 5);
	//动作
	void f动作_结束();
	void f动作_死亡();	//强制死亡,无视其它因素,会调用击破事件
private:
	void f计算运动();
	void f直接移动(const t向量2 &a目标, float a时间);
public:
	t向量2 m坐标;
	t向量2 m速度;
	int m编号 = 0;
	t标志 m标志;
	float m运动时间 = 0;
	tf运动 mf运动;
	const C游戏速度 *m游戏速度 = nullptr;
	C数组计数 *m计数指针 = nullptr;
	const S敌机属性 *m敌机属性 = nullptr;
	数学::S有限值<int> m生命值 = {1};
	float m无敌时间 = 0;
	std::unique_ptr<I对象图形<C敌机>> m图形;
};
//==============================================================================
// 敌机使用的结构
//==============================================================================
struct S敌机属性 : public S图片动画属性 {
	float m判定半径;
};
//==============================================================================
// 敌机运动
//==============================================================================
C敌机::tf运动 F敌机运动_直线速度(const t向量2 &速度, float 时间);
C敌机::tf运动 F敌机运动_目标坐标(const t向量2 &目标, float 时间);
C敌机::tf运动 F敌机运动_平滑移动到(const t向量2 &最高速度, float 总时间, float 平滑开始, float 平滑结束);
C敌机::tf运动 F敌机运动_平滑移动过(const t向量2 &目标, float 总时间, float 平滑开始);
}