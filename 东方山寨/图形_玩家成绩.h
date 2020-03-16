#pragma once
#include "游戏常量.h"
#include "图形基础.h"
#include "图形工厂.h"
#include "图形缓冲.h"
namespace 东方山寨 {
class C玩家成绩图形实现;
class C画玩家成绩 {
public:
	static constexpr float c字号 = 二维::ca中文字号[二维::e三号];
	static constexpr float c小数字号 = c字号 * 0.6f;
	static constexpr float c行距 = c字号;
	static constexpr float c坐标x = -c边框范围x + 2;
	C画玩家成绩(二维::C二维 &);
	二维::tp画文本 fc画文本() const;
	二维::tp文本效果 fc文本效果(const 数学::S颜色 &) const;
	二维::tp文本布局 fc文本布局(const std::wstring &, 二维::tp文本格式) const;
	二维::tp文本布局 fc文本布局_小数(double, int, 二维::tp文本格式) const;
	二维::C二维 *m二维 = nullptr;
	二维::C文本工厂 *m文本工厂 = nullptr;
};
class C玩家成绩图形实现 {
public:
	void f实现_初始化环境(const C画玩家成绩 &);
	void f实现_初始化(float 位置, 二维::tp文本格式 格式, const t颜色 &颜色);
	void f实现_计算();
	void f实现_值变化了();
	void f实现_更新();
	void f实现_显示() const;
	float f实现_g透明度() const;
	float m变化 = 1;
	float m坐标y = 0;
	bool m文本变化 = true;
	二维::tp画文本 m画文本;
	二维::tp文本布局 m文本布局;
	二维::tp文本格式 m文本格式;
	const C画玩家成绩 *m画成绩 = nullptr;
};
template<typename t值> class C玩家成绩图形 : public I图形, public C玩家成绩图形实现, public C兼容图形缓冲<C玩家成绩图形<t值>> {
public:
	static_assert(std::is_arithmetic<t值>::value);
	using tf跟踪 = std::function<t值()>;
	using tf计算 = std::function<t值(t值, t值)>;	//返回值(原值, 跟踪值)
	using tf更新 = std::function<void(C玩家成绩图形<t值> &, const C画玩家成绩 &)>;
	//构造
	C玩家成绩图形(const tf跟踪 &af跟踪, const tf计算 &af计算, const tf更新 &af更新):
		mf跟踪(af跟踪), mf计算(af计算), mf更新(af更新) {
	}
	//重写
	void f接口_计算() override {
		const t值 v目标 = mf计算(m值, mf跟踪());
		if (m值 != v目标) {
			m值 = v目标;
			f实现_值变化了();
		}
		f实现_计算();
	}
	void f接口_更新() override {
		if (m文本变化) {
			mf更新(*this, *m画成绩);
			m文本变化 = false;
		}
		f实现_更新();
	}
	void f兼容显示() const {
		f实现_显示();
	}
	//跟踪
	template<typename t1> static tf跟踪 F跟踪_值(const t1 &a) {
		return [&a]()->t值 {
			return (t值)a;
		};
	}
	static tf跟踪 F跟踪_值(const t值 &a) {
		return [&a]()->t值 {
			return a;
		};
	}
	static tf跟踪 F跟踪_分数(const boost::rational<int> &a) {
		return [&a]()->t值 {
			return boost::rational_cast<t值>(a);
		};
	}
	//计算
	static t值 f计算_直接(t值, t值 a) {
		return a;
	}
	static tf计算 F计算_渐变(float a渐变, t值 a最小, t值 a最大) {
		return [=](t值 a0, t值 a1)->t值 {
			return 数学::f倍数渐变<t值>(a0, a1, a渐变, a最小, a最大);
		};
	}
	//更新
	void f更新_直接(const C画玩家成绩 &a) {
		m文本布局 = a.fc文本布局(std::to_wstring(m值), m文本格式);
	}
	static tf更新 F更新_转换(std::function<std::wstring(t值)> af) {
		return [=](C玩家成绩图形<t值> &a这, const C画玩家成绩 &a) {
			a这.m文本布局 = a.fc文本布局(af(a这.m值), a这.m文本格式);
		};
	}
	static tf更新 F更新_小数(int a小数位数) {
		return [=](C玩家成绩图形<t值> &a这, const C画玩家成绩 &a) {
			a这.m文本布局 = a.fc文本布局_小数(a这.m值, a小数位数, a这.m文本格式);
		};
	}
	//变量
	t值 m值 = 0;
	tf跟踪 mf跟踪;
	tf计算 mf计算;
	tf更新 mf更新;
};
//==============================================================================
// 玩家成绩图形工厂
//==============================================================================
class C玩家成绩图形工厂 {
public:
	C玩家成绩图形工厂(const C图形工厂 &, const C画玩家成绩 &, std::vector<std::shared_ptr<I图形>> &);
	template<typename t值> std::shared_ptr<C玩家成绩图形<t值>> f产生图形(float 位置, 二维::tp文本格式 格式, const t颜色 &颜色, const typename C玩家成绩图形<t值>::tf跟踪 &, const typename C玩家成绩图形<t值>::tf计算 &, const typename C玩家成绩图形<t值>::tf更新 &);
	C图形工厂 m图形工厂;
	const C画玩家成绩 *m画玩家成绩 = nullptr;
	std::vector<std::shared_ptr<I图形>> *ma玩家成绩 = nullptr;
};
template<typename t值> std::shared_ptr<C玩家成绩图形<t值>>
C玩家成绩图形工厂::f产生图形(
	float a位置, 
	二维::tp文本格式 a格式, 
	const t颜色 &a颜色, 
	const typename C玩家成绩图形<t值>::tf跟踪 &af跟踪, 
	const typename C玩家成绩图形<t值>::tf计算 &af计算, 
	const typename C玩家成绩图形<t值>::tf更新 &af更新) {
	std::shared_ptr<C玩家成绩图形<t值>> v图形 = std::make_shared<C玩家成绩图形<t值>>(af跟踪, af计算, af更新);
	v图形->f实现_初始化环境(*m画玩家成绩);
	v图形->f实现_初始化(a位置, a格式, a颜色);
	auto v缓冲 = m图形工厂.fc图形缓冲<C玩家成绩图形<t值>>(*v图形);
	m图形工厂.f实现_产生图形(v图形, v缓冲);
	ma玩家成绩->push_back(v图形);
	return v图形;
}
}	//namespace 东方山寨