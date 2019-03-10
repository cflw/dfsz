#pragma once
#include "基础.h"
#include "基础_数组.h"
#include "敌机基础.h"
namespace 东方山寨 {
class C敌机;
class C游戏速度;
//==============================================================================
// 敌机制造机
//==============================================================================
class C敌机制造机 {
public:
	struct S参数 {
		t向量2 m坐标;
		t向量2 m速度;
		t向量2 m目标;
		int m生命值 = 100;
		float m移动时间;
		t属性指针<S敌机属性> m样式;
		void fs坐标(const t向量2 &);
		void fs速度(const t向量2 &, float = -1);
		void fs目标(const t向量2 &, float);
	};
	class C实现 {
	public:
		void f初始化_环境(const C游戏速度 &);
		void f初始化_数组(C对象数组<C敌机> &);
		void f初始化_资源(const C属性数组<S敌机属性> &);
		void f产生敌机(std::shared_ptr<C敌机>, S参数 &);
		bool fi有空() const;
		C对象数组<C敌机> *ma敌机 = nullptr;
		const C游戏速度 *m游戏速度 = nullptr;
		const C属性数组<S敌机属性> *ma敌机属性 = nullptr;
	};
	C敌机制造机(C实现 &);
	template<typename t, typename...t参数> std::shared_ptr<t> f产生敌机(t参数 &&...);
	std::shared_ptr<C敌机> f产生王();
	S参数 m参数;
private:
	C实现 *m实现 = nullptr;
};
//产生敌机函数实现
template<typename t, typename...t参数> std::shared_ptr<t> C敌机制造机::f产生敌机(t参数 &&...a参数) {
	static_assert(std::is_base_of<C敌机, t>::value, "错误:t必需继承自敌机");
	if (m实现->fi有空()) {
		std::shared_ptr<t> v指针 = std::make_shared<t>(a参数...);
		m实现->f产生敌机(v指针, m参数);
		return v指针;
	}
	return nullptr;
}
}	//namespace 东方山寨