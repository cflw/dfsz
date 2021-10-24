#pragma once
#include "基础.h"
#include "基础_对象工厂.h"
#include "基础_对象数组.h"
#include "基础_缓冲数组.h"
#include "基础_数组指针.h"
#include "图形引擎.h"
#include "图形基础.h"
#include "图形缓冲.h"
#include "图形建造机.h"
namespace 东方山寨 {
//==============================================================================
// 图形工厂
//==============================================================================
struct S图形参数 {
	t向量2 m坐标;
	t向量2 m速度;
	float m寿命 = 1;
	float m透明度 = 1;
	int m图层 = 0;
	t属性指针<S纹理> m纹理;
	t属性指针<S顶点矩形> m顶点;
	t标志 m标志;	//自定义,与 I图形::E标志 无关
};
class C图形工厂 {
public:
	typedef std::function<void(C图形工厂 &)> tf产生;
	class C实现 {
	public:
		void f初始化_环境(const C游戏速度 &);
		void f初始化_数组(C对象数组<I图形> &, C缓冲数组<I图形缓冲> &);
		void f产生图形(const std::shared_ptr<I图形> &, S图形参数 &, I图形缓冲 * = nullptr);
		bool fi有空() const;
		C对象数组<I图形> *ma图形 = nullptr;
		C缓冲数组<I图形缓冲> *ma图形缓冲 = nullptr;
		const C游戏速度 *m游戏速度 = nullptr;
	};
	C图形工厂(C实现&);
	void f实现_产生图形(const std::shared_ptr<I图形> &, I图形缓冲 * = nullptr);
	template<typename t, typename...t参数> std::shared_ptr<t> f产生图形(const t参数 &...a参数);
	std::shared_ptr<I图形> f产生图形(const I图形建造机 &);
	template<T有图形缓冲 t> typename t::C图形缓冲 *fc图形缓冲(t &);
	template<typename t> I图形缓冲 *fc图形缓冲(t &);
public:
	S图形参数 m参数;
private:
	C实现 *m实现 = nullptr;
};
//==============================================================================
// 图形工厂模板实现
//==============================================================================
template<typename t, typename...t参数> std::shared_ptr<t> C图形工厂::f产生图形(const t参数 &...a参数) {
	static_assert(std::is_base_of<I图形, t>::value, "必须继承自I图形");
	if (m实现->fi有空()) {
		std::shared_ptr<t> v图形 = std::make_shared<t>(a参数...);
		auto *v图形缓冲 = fc图形缓冲<t>(*v图形);
		m实现->f产生图形(v图形, m参数, v图形缓冲);
		return v图形;
	}
	return nullptr;
}
template<T有图形缓冲 t> typename t::C图形缓冲 *C图形工厂::fc图形缓冲(t &a) {
	if constexpr (T兼容图形缓冲<t>) {	//以后改掉
		return m实现->ma图形缓冲->f新建<typename t::C图形缓冲>(a);
	} else {
		return m实现->ma图形缓冲->f新建<typename t::C图形缓冲>();
	}
}
template<typename t> I图形缓冲 *C图形工厂::fc图形缓冲(t &) {
	throw std::runtime_error("图形类未实现图形缓冲");
}
}	//namespace 东方山寨