#pragma once
#include <memory>
#include <concepts>
#include <functional>
#include <utility>
namespace 东方山寨 {
//==============================================================================
// 工厂
//==============================================================================
template<typename t> 
class I工厂 {
public:
	virtual std::unique_ptr<t> f接口_新建u() const = 0;
	virtual std::shared_ptr<t> f接口_新建s() const = 0;	//共享所有权指针会创建控制块,建议重写,并调用std::make_shared<t>()
	
};
template<typename t基类, typename t派生类 = t基类> requires std::derived_from<t派生类, t基类>
class C简单工厂 : public I工厂<t基类> {
public:
	std::unique_ptr<t基类> f接口_新建u() const override {
		return std::make_unique<t派生类>();
	}
	std::shared_ptr<t基类> f接口_新建s() const override {
		return std::make_shared<t派生类>();
	}
};
//按模板生成代码的自动工厂类
template<typename t基类, typename t派生类, typename t派生工厂>	//不能在这加要求, 因为定义派生工厂过程中 t派生类 可能是不完整类型
class I自动工厂 : public I工厂<t基类>  {
	//派生工厂中应该实现2个函数:
	//std::tuple<> f工厂_g构造实参() const;
	//void f工厂_对象初始化(t派生类 &) const
	std::unique_ptr<t基类> f接口_新建u() const override {
		std::unique_ptr<t派生类> vp = f工厂_新建u(
			f工厂_g构造实参0(), 
			std::make_index_sequence<std::tuple_size_v<decltype(f工厂_g构造实参0())>>()
		);
		f工厂_对象初始化(*vp);
		return vp;
	}
	std::shared_ptr<t基类> f接口_新建s() const override {
		std::shared_ptr<t派生类> vp = f工厂_新建s(
			f工厂_g构造实参0(),
			std::make_index_sequence<std::tuple_size_v<decltype(f工厂_g构造实参0())>>()
		);
		f工厂_对象初始化(*vp);
		return vp;
	}
	template<typename t元组, std::size_t... i>
	std::unique_ptr<t派生类> f工厂_新建u(t元组 &&a元组, std::index_sequence<i...>) const {
		return std::make_unique<t派生类, typename std::tuple_element<i, t元组>::type...>(std::get<i>(a元组)...);
	}
	template<typename t元组, std::size_t... i>
	std::shared_ptr<t派生类> f工厂_新建s(t元组 &&a元组, std::index_sequence<i...>) const {
		return std::make_shared<t派生类, typename std::tuple_element<i, t元组>::type...>(std::get<i>(a元组)...);
	}
	auto f工厂_g构造实参0() const {
		return static_cast<const t派生工厂 *>(this)->f工厂_g构造实参();
	}
	void f工厂_对象初始化(t派生类 &) const {
		//什么都不做
	}
};
}