#pragma once
#include <optional>
#include <experimental/generator>
#include <cflw工具_循环.h>
#include "数学包含.h"
#include "基础.h"
#include "基础_属性数组.h"
#include "基础_扩展数组.h"
#include "基础_对象数组.h"
#include "基础_缓冲数组.h"
namespace 东方山寨 {
namespace 循环 = cflw::工具::循环;
typedef std::optional<float> t计算;
class C子弹;
struct S子弹属性;
class I图形管线;
class I画子弹;
class C子弹图形缓冲;
struct S子弹参数;
class C子弹变换;
class C子弹循环;
class C子弹制造机;
using t子弹参数 = S子弹参数;
using t子弹工厂 = C子弹制造机;
using te子弹循环 = std::experimental::generator<C子弹变换>;
using tf子弹循环 = std::function<te子弹循环(S子弹参数 &)>;
//==============================================================================
// 子弹制造机
//==============================================================================
//参数
struct S子弹参数 {	//产生子弹所需的参数
	t向量2 m坐标;
	t向量2 m速度;
	t向量2 m缩放;
	t向量2 m长宽;	//缩放和长宽只能同时存在一个,长宽会覆盖缩放
	t颜色 m颜色[2];
	float m出现 = 0;
	C属性数组<S子弹属性>::t指针 m样式;
	C扩展数组<I画子弹>::t指针 m绘制;
	C属性数组<S子弹属性>::t指针 m缓存_样式;
	C扩展数组<I画子弹>::t指针 m缓存_绘制;
	S子弹参数();	//设置默认值
	void fs坐标(const t向量2 &);
	void fs速度(const t向量2 &);
	void fs速度_到自机(float 大小);
	void fs顶色(const t颜色 &);
	void fs底色(const t颜色 &);
	void fs长度(float);
	void fs宽度(float);
	void fs样式(int);
	void fs绘制(int);
	void fs子弹基础(const C子弹 &);
	void fs立即出现(bool);
	C子弹循环 f循环(int);
	te子弹循环 f循环(const tf子弹循环 &);
};
//变换
class C子弹变换 {
public:
	C子弹变换(C子弹循环 &a循环);
	operator S子弹参数 &();
	//循环基本属性
	int fg计数() const;
	int fg总数() const;
	float fg百分比() const;
	//循环计算函数
	float f计算(t标志) const;
	float f计算_正弦波(float 振幅, float 频率, t计算 计算 = std::nullopt) const;
	t向量2 f计算_速度变换(float 大小, float 方向, t计算 计算 = std::nullopt) const;
	t向量2 f计算_速度线性插值(const t向量2 &, t计算 计算 = std::nullopt) const;
	t向量2 f计算_速度平滑插值(const t向量2 &, t计算 计算 = std::nullopt) const;
	//循环变换函数
	void f变换_备份();
	void f变换_还原();
	void f变换_圆形(int = 1, t计算 计算 = std::nullopt);	//方向按圆形变化
	void f变换_椭圆(float 短轴变化);
	void f变换_扇形(float 间隔, t计算 计算 = std::nullopt);
	void f变换_速度(float 大小, float 方向, t计算 计算 = std::nullopt);	//速度大小方向直接变化
	void f变换_速度线性插值(const t向量2 &, t计算 计算 = std::nullopt);	//xy分量的插值
	void f变换_速度平滑插值(const t向量2 &, t计算 计算 = std::nullopt);	//大小方向分量的插值
	void f变换_颜色(int, const t颜色 &, t计算 计算 = std::nullopt);	//颜色插值
	void f变换_坐标插值(const t向量2 &, t计算 计算 = std::nullopt);
	void f变换_坐标前移(float, t计算 计算 = std::nullopt);
	void f变换_坐标平移(const t向量2 &移动, t计算 计算 = std::nullopt);	//绝对移动
public:
	S子弹参数 *m参数 = nullptr, *m备份 = nullptr;
	int m计数 = 0, m总数 = 0;
};
//循环
class C子弹循环 : public 循环::I循环<C子弹循环> {
public:
	C子弹循环(S子弹参数 &, int 次数);
	//循环控制
	void f循环控制_自增();
	bool f循环控制_i继续();
	C子弹变换 f循环控制_解引用();
public:
	S子弹参数 *m参数, m参数备份;
	int m总数 = 0, m计数 = 0;
};
class C子弹制造机 {
public:
	C子弹制造机() = default;
	C子弹制造机(const C子弹制造机 &) = delete;
	void f初始化_环境(const C游戏速度 &);
	void f初始化_数组(C对象数组<C子弹> &, C缓冲数组<C子弹图形缓冲> &);
	void f初始化_资源(const C属性数组<S子弹属性> &, const C扩展数组<I图形管线> &);
	void f编译参数(S子弹参数 &) const;
	bool fi有空() const;
	void f产生子弹0(const std::shared_ptr<C子弹> &, const S子弹参数 &) const;//调用"f产生子弹"前需要调用"f分配"
	std::shared_ptr<C子弹> f产生子弹(S子弹参数 &) const;	//产生普通子弹
	template<typename t, typename...t参数> std::shared_ptr<t> f产生子弹(S子弹参数 &, t参数 &&...) const;
private:
	C对象数组<C子弹> *ma子弹 = nullptr;
	C缓冲数组<C子弹图形缓冲> *ma子弹图形缓冲 = nullptr;
	const C游戏速度 *m游戏速度 = nullptr;
	const C属性数组<S子弹属性> *ma子弹属性 = nullptr;
	const C扩展数组<I图形管线> *ma画子弹 = nullptr;
};
template<typename t, typename...t参数> std::shared_ptr<t> C子弹制造机::f产生子弹(S子弹参数 &a子弹参数, t参数 &&...a构造参数) const {
	static_assert(std::is_base_of<C子弹, t>::value);
	f编译参数(a子弹参数);
	if (fi有空()) {
		std::shared_ptr<t> v子弹 = std::make_shared<t>(a构造参数...);
		f产生子弹0(v子弹, a子弹参数);
		t::f接口_具体类型初始化(v子弹);
		return v子弹;
	}
	return nullptr;
}
//==============================================================================
// 循环模板
//==============================================================================
tf子弹循环 F循环模板_旋转(float 旋转角, int 次数, int 边细分, float 坐标前移倍数 = 1, float 速度插值 = 1);
tf子弹循环 F循环模板_正多边形(int 角数, int 边细分, float 坐标前移倍数 = 1, float 速度插值 = 1);
tf子弹循环 F循环模板_锐多角星(int 角数, int 边细分, float 坐标前移倍数 = 1, float 速度插值 = 1);
tf子弹循环 F循环模板_钝多角星(int 角数, int 边细分, float 坐标前移倍数 = 1, float 速度插值 = 1);
}	//namespace 东方山寨