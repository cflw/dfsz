#pragma once
#include "子弹基础.h"
namespace 东方山寨 {
class C连续子弹 : public C子弹, public std::enable_shared_from_this<C连续子弹> {
private:
	typedef void (*tf两点操作)(C连续子弹 &, C连续子弹 &);
	using tp连续子弹 = std::shared_ptr<C连续子弹>;
	enum E标志 {
		e窗口外 = C子弹::e自定义,	//在"f接口_计算"中,子弹在窗口外时加标志.在"f接口_在窗口外"用于判断
		e环形头部,
		e细分,	//这是通过细分子弹产生的子弹
	};
public:	//连接工具
	class C连接工具 {	//两点连接
	public:
		C连接工具();
		C连接工具(tf两点操作);
		C连接工具 &operator +=(const std::shared_ptr<C连续子弹> &);
		void f重置();
	private:
		std::shared_ptr<C连续子弹> m这;
		tf两点操作 mf连接;
	};
	class C环形工具 {
	public:
		C环形工具();
		C环形工具(tf两点操作);
		~C环形工具();
		C环形工具 &operator +=(const std::shared_ptr<C连续子弹> &);
		void f重置();
	private:
		std::shared_ptr<C连续子弹> m头, m这;
		tf两点操作 mf连接;
	};
public:	//细分工具
	template<typename t, bool ti构造函数 = std::is_constructible<t, const t &, const t &, float>::value> class C细分工具 {
	public:	//ti构造函数=true时,调用派生类的细分构造函数
		static_assert(std::is_base_of<C连续子弹, t>::value, "");
		static void f处理(const std::shared_ptr<t> &);	//给"C连续子弹::mf细分"赋值
	};
public:	//重写的接口函数
	C连续子弹() = default;
	C连续子弹(const C连续子弹 &, const C连续子弹 &, float);
	template<typename t> static void f接口_具体类型初始化(const std::shared_ptr<t> &);
	void f接口_初始化() override;
	void f接口_销毁() override;
	void f接口_计算() override;
	void f接口_结算() override;
	void f接口_更新() override;
	void f接口_自机判定(C自机与子弹判定 &) override;
	bool f接口_i在窗口外() override;
	bool f接口_i可显示() const override;
	bool f接口_炸弹判定(C子弹与玩家炸弹判定 &) override;
public:		//初始化
public:		//动作
	void f动作_消失(bool 动画 = true);
private:	//扩展
	bool f扩展_i环() const;
	void f扩展_自动细分();
	float f扩展_g细分间隔() const;
	static std::shared_ptr<C连续子弹> f连续子弹_c细分(C连续子弹 &, C连续子弹 &, float);	//新建子弹对象
	static void f连续子弹_连接(C连续子弹 &, C连续子弹 &);	//有断言
	static void f连续子弹_断开(C连续子弹 &, C连续子弹 &);	//有断言
	static void f连续子弹_细分(C连续子弹 &, C连续子弹 &, int);	//调用子弹制造机产生细分子弹
	static void f连续子弹_连接1(C连续子弹 &, C连续子弹 &);	//危险函数
	static void f连续子弹_断开1(C连续子弹 &, C连续子弹 &);	//危险函数
private:	//属性
	static std::mutex m连接互斥;
	std::shared_ptr<C连续子弹> m前, m后;
	S子弹出现 m出现;
	S子弹消失 m消失;
	std::shared_ptr<C连续子弹> (*mf细分)(C连续子弹 &, C连续子弹 &, float) = nullptr;
};
//==============================================================================
// 连续子弹细分工具的实现
//==============================================================================
template<typename t> class C连续子弹::C细分工具<t, true> {
public:
	static void f处理(const std::shared_ptr<t> &a这) {
		C连续子弹 *const v这 = a这.get();
		v这->mf细分 = [](C连续子弹 &a前, C连续子弹 &a后, float a插值)->std::shared_ptr<C连续子弹> {
			return std::make_shared<t>(a前, a后, a插值);
		};
	}
};
template<typename t> class C连续子弹::C细分工具<t, false> {
public:
	static void f处理(const std::shared_ptr<t> &a这) {
		C连续子弹 *const v这 = a这.get();
		v这->mf细分 = f连续子弹_c细分;
	}
};
template<typename t> void C连续子弹::f接口_具体类型初始化(const std::shared_ptr<t> &a这) {
	static_assert(std::is_base_of<C连续子弹, t>::value, "");
	C细分工具<t>::f处理(a这);
}
}