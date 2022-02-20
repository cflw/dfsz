module;
#include "数学包含.h"
#include "基础.h"
export module 东方山寨.基础_结构;
export namespace 东方山寨 {
struct S运动 {
	t向量2 m坐标;
	t向量2 m速度;
	void f初始化_运动(const t向量2 &a坐标, const t向量2 &a速度) {
		m坐标 = a坐标;
		m速度 = a速度;
	}
	void f计算_运动(float a过秒) {
		m坐标 += m速度 * a过秒;
	}
};
struct S生命 {
	float m寿命;	//固定
	float m生命 = 0;	//存活的时间
	void f初始化_生命(float a寿命) {
		m寿命 = a寿命;
		m生命 = 0;
	}
	void f计算_生命(float a过秒) {
		m生命 += a过秒;
	}
	float fg生命百分比() const {
		return m生命 / m寿命;
	}
	float fg反生命百分比() const {
		return 1 - fg生命百分比();
	}
	bool fi死亡() const {
		return m生命 >= m寿命;
	}
};
}	//namespace 东方山寨