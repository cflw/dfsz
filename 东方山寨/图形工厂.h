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
struct S图形参数;
class C图形工厂;
using t图形参数 = S图形参数;
using t图形工厂 = C图形工厂;
//==============================================================================
// 图形工厂
//==============================================================================
struct S图形参数 {
	//常量
	static S图形参数 c默认;
	static S图形参数 c界面;
	static S图形参数 c游戏中;
	static S图形参数 c游戏抬显;
	//变量
	t向量2 m坐标;
	t向量2 m速度;
	float m寿命 = 1;
	float m透明度 = 1;
	int m图层 = 0;
	t属性指针<S纹理> m纹理;
	t属性指针<S顶点矩形> m顶点;
	t标志 m标志;	//图形标志
	//函数
	S图形参数(const S图形参数 &) = default;
	static S图形参数 fc自动();	//根据游戏阶段设置不同的初始值
private:
	S图形参数() = default;	//不能在外部使用默认构造函数,必需赋初始值
};
class C图形工厂 {
public:
	C图形工厂() = default;
	C图形工厂(const C图形工厂 &) = delete;
	void f初始化_环境(const C游戏速度 &);
	void f初始化_数组(C对象数组<I图形> &, C缓冲数组<I图形缓冲> &);
	void f产生图形0(const std::shared_ptr<I图形> &, S图形参数 &, I图形缓冲 * = nullptr) const;
	bool fi有空() const;
	template<typename t, typename...t参数> std::shared_ptr<t> f产生图形(S图形参数 &, const t参数 &...a参数) const;
	std::shared_ptr<I图形> f产生图形(S图形参数 &, const I图形建造机 &) const;
	template<T有图形缓冲 t> typename t::t图形缓冲 *fc图形缓冲(t &) const;
	template<typename t> I图形缓冲 *fc图形缓冲(t &) const;
private:
	C对象数组<I图形> *ma图形 = nullptr;
	C缓冲数组<I图形缓冲> *ma图形缓冲 = nullptr;
	const C游戏速度 *m游戏速度 = nullptr;
};
//==============================================================================
// 图形工厂模板实现
//==============================================================================
template<typename t, typename...t参数> std::shared_ptr<t> C图形工厂::f产生图形(S图形参数 &a图形参数, const t参数 &...a参数) const {
	static_assert(std::is_base_of<I图形, t>::value, "必须继承自I图形");
	if (fi有空()) {
		std::shared_ptr<t> v图形 = std::make_shared<t>(a参数...);
		auto *v图形缓冲 = fc图形缓冲<t>(*v图形);
		f产生图形0(v图形, a图形参数, v图形缓冲);
		return v图形;
	}
	return nullptr;
}
template<T有图形缓冲 t> typename t::t图形缓冲 *C图形工厂::fc图形缓冲(t &a) const {
	return ma图形缓冲->f新建<typename t::t图形缓冲>();
}
template<typename t> I图形缓冲 *C图形工厂::fc图形缓冲(t &) const {
	static_assert(T有图形缓冲<t>, "图形类未实现图形缓冲(没有t图形缓冲)");
}
}	//namespace 东方山寨