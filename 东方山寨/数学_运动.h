#pragma once
#include "数学包含.h"
namespace 东方山寨 {
class C复杂运动;
using tf复杂运动 = std::function<t向量2(const C复杂运动 &)>;	//复杂运动函数,参数1是当前运动状态
class C复杂运动 {
public:	//静态函数
	static tf复杂运动 F直线速度(const t向量2 &速度, float 时间);
	static tf复杂运动 F目标坐标(const t向量2 &目标, float 时间);
	static tf复杂运动 F平滑移动到(const t向量2 &最高速度, float 总时间, float 平滑开始, float 平滑结束);
	static tf复杂运动 F平滑移动过(const t向量2 &目标, float 总时间, float 平滑开始);
public:	//属性
	const t向量2 &fg坐标() const;
	const t向量2 &fg速度() const;
	float fg移动方向x() const;
	float fg移动方向y() const;
	bool fi运动时间内(float) const;
	float f剩余运动时间(float) const;
public:	//运动
	void fs速度(const t向量2 &);
	void fs运动(const tf复杂运动 &);
	void f运动_速度(const t向量2 &速度, float 时间 = 0);
	void f运动_限时移动到(const t向量2 &, float 时间, float 平滑开始时间 = 0, float 平滑结束时间 = 0);
	void f运动_限速移动到(const t向量2 &, float 速度, float 平滑开始时间 = 0, float 平滑结束时间 = 0);
	void f运动_限时移动过(const t向量2 &, float 时间, float 平滑开始时间 = 0);
	void f运动_限速移动过(const t向量2 &, float 速度, float 平滑开始时间 = 0);
	void f运动_平滑移动到(const t向量2 &, float 总时间, float 平滑开始时间 = 0.5f, float 平滑结束时间 = 0.5f);
	void f运动_平滑移动过(const t向量2 &, float 总时间, float 平滑开始时间 = 0.5f);
	void f运动_相对横坐标随机移动(float 横坐标, float 横平均, float 横浮动, float 纵平均 = 100, float 纵浮动 = 5);
protected:
	void f计算运动(float 过秒);
	void f直接移动(const t向量2 &a目标, float a时间);
public:	//变量
	t向量2 m坐标;
	t向量2 m速度;
	float m运动时间 = 0;
	tf复杂运动 mf运动;
};

}	//namespace 东方山寨