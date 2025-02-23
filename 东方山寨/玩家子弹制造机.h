#pragma once
#include <optional>
#include <cflw工具_循环.h>
#include "基础.h"
#include "基础_对象数组.h"
#include "玩家子弹基础.h"
namespace 东方山寨 {
namespace 循环 = cflw::工具::循环;
typedef std::optional<float> t计算;
class C玩家;
struct S玩家子弹属性;
class I玩家发射环境;
class C玩家子弹;
class C玩家炸弹;
struct S玩家子弹参数;
class C玩家子弹循环;
//参数
struct S玩家子弹参数 {
	t向量2 m坐标, m速度;
	const I玩家发射环境 *m发射环境 = nullptr;
	const S玩家子弹属性 *m子弹属性 = nullptr;
	C玩家子弹循环 f循环(int);
};
//循环
class C玩家子弹循环 : public 循环::I循环<C玩家子弹循环> {
public:
	C玩家子弹循环(S玩家子弹参数 &, int 次数);
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
	void f变换_速度(float 大小, float 方向, float 计算 = 1);
	void f变换_坐标平移(const t向量2 &移动, float 计算);
	void f变换模板_发散(std::shared_ptr<I玩家发射环境>, const std::pair<float, float> &角度间隔, const std::pair<float, float> &坐标x间隔);
private:
	int m计数, m总数;
	S玩家子弹参数 m参数备份, *mp参数;
};
//工厂
class C玩家子弹制造机 {
public:
	C玩家子弹制造机() = default;
	C玩家子弹制造机(const C玩家子弹制造机 &) = delete;
	void f初始化_环境(const C游戏速度 &);
	void f初始化_数组(C对象数组<C玩家子弹> &, C缓冲数组<I图形缓冲> &);
	void f产生子弹0(const std::shared_ptr<C玩家子弹> &, const S玩家子弹参数 &) const;
	void f产生炸弹0(const std::shared_ptr<C玩家炸弹> &, const S玩家子弹参数 &) const;
	bool fi有空() const;
	template<typename t子弹, typename...t参数> std::shared_ptr<t子弹> f产生子弹(const S玩家子弹参数 &, const t参数 &...) const;
	template<typename t炸弹, typename...t参数> std::shared_ptr<t炸弹> f产生炸弹(const S玩家子弹参数 &, const t参数 &...) const;
private:
	const C游戏速度 *m游戏速度 = nullptr;
	C对象数组<C玩家子弹> *ma子弹 = nullptr;
	C缓冲数组<I图形缓冲> *ma图形缓冲 = nullptr;
};
//定义
template<typename t子弹, typename...t参数> std::shared_ptr<t子弹> C玩家子弹制造机::f产生子弹(const S玩家子弹参数 &a玩家子弹参数, const t参数 &...a构造参数) const {
	static_assert(std::is_base_of<C玩家子弹, t子弹>::value);
	if (fi有空()) {
		std::shared_ptr<t子弹> v新子弹 = std::make_shared<t子弹>(a构造参数...);
		f产生子弹0(v新子弹, a玩家子弹参数);
		return v新子弹;
	}
	return nullptr;
}
template<typename t炸弹, typename...t参数> std::shared_ptr<t炸弹> C玩家子弹制造机::f产生炸弹(const S玩家子弹参数 &a玩家子弹参数, const t参数 &...a构造参数) const {
	static_assert(std::is_base_of<C玩家炸弹, t炸弹>::value);
	std::shared_ptr<t炸弹> v新子弹 = std::make_shared<t炸弹>(a构造参数...);
	f产生炸弹0(v新子弹, a玩家子弹参数);
	return v新子弹;
}
}	//namespace 东方山寨