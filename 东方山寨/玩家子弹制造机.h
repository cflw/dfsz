#pragma once
#include <optional>
#include "基础.h"
#include "基础_数组.h"
#include "玩家子弹基础.h"
namespace 东方山寨 {
typedef std::optional<float> t计算;
class C玩家;
struct S玩家子弹属性;
class I玩家发射环境;
class C玩家子弹;
class C玩家炸弹;
struct S玩家子弹参数 {
	t向量2 m坐标, m速度;
	const I玩家发射环境 *m发射环境 = nullptr;
	const S玩家子弹属性 *m子弹属性 = nullptr;
};
class C玩家子弹制造机 {
public:
	static const int c层数 = 5;
	class C循环 : public 循环::I循环<C循环> {
	public:
		C循环(int 次数, S玩家子弹参数 *);
		//循环控制
		void f循环控制_自增();
		bool f循环控制_i继续();
		//循环基本属性
		int fg计数() const;
		int fg总数() const;
		float fg百分比() const;
		//计算
		float f计算(t标志) const;
		t向量2 f计算_速度变换(float 大小, float 方向, float 计算 = 1) const;
		//变换
		void f变换_备份(int = -1);
		void f变换_还原(int = -1);
		void f变换_速度(float 大小, float 方向, float 计算 = 1);
		void f变换_坐标平移(const t向量2 &移动, float 计算);
		void f变换模板_发散(std::shared_ptr<I玩家发射环境>, const std::pair<float, float> &角度间隔, const std::pair<float, float> &坐标x间隔);
	private:
		int m计数, m总数;
		S玩家子弹参数 m参数备份, *mp参数;
	};
	class C实现 {
	public:
		void f初始化_环境(const C游戏速度 &);
		void f初始化_数组(C对象数组<C玩家子弹> &);
		void f产生子弹(std::shared_ptr<C玩家子弹>, const S玩家子弹参数 &);
		void f产生炸弹(std::shared_ptr<C玩家炸弹>, const S玩家子弹参数 &);
		bool fi有空() const;
		const C游戏速度 *m游戏速度 = nullptr;
		C对象数组<C玩家子弹> *ma子弹;
	};
	C玩家子弹制造机(C实现 &);
	template<typename t, typename...t参数> std::shared_ptr<t> f产生子弹(const t参数 &...);
	template<typename t, typename...t参数> std::shared_ptr<t> f产生炸弹(const t参数 &...);
	C循环 f循环(int);
	S玩家子弹参数 m参数;
private:
	C实现 * m实现 = nullptr;
};
template<typename t, typename...t参数> std::shared_ptr<t> C玩家子弹制造机::f产生子弹(const t参数 &...a参数) {
	static_assert(std::is_base_of<C玩家子弹, t>::value);
	if (m实现->fi有空()) {
		std::shared_ptr<t> v新子弹 = std::make_shared<t>(a参数...);
		m实现->f产生子弹(v新子弹, m参数);
		return v新子弹;
	}
	return nullptr;
}
template<typename t, typename...t参数> std::shared_ptr<t> C玩家子弹制造机::f产生炸弹(const t参数 &...a参数) {
	static_assert(std::is_base_of<C玩家炸弹, t>::value);
	std::shared_ptr<t> v新子弹 = std::make_shared<t>(a参数...);
	m实现->f产生炸弹(v新子弹, m参数);
	return v新子弹;
}
}