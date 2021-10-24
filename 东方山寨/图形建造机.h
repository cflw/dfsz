#pragma once
#include "图形基础.h"
#include "图形缓冲.h"
namespace 东方山寨 {
//==============================================================================
// 建造者模式,分别创建图形和图形缓冲
//==============================================================================
class C图形建造过程 {
public:
	C图形建造过程() = default;
	template<T图形 t图形, typename...t参数> void f建造图形(t参数 &&...a参数) {
		m图形 = std::make_shared<t图形>(std::forward<t参数>(a参数)...);
	}
	template<T图形缓冲 t图形缓冲, typename...t参数> void f建造图形缓冲(t参数 &&...a参数) {
		m图形缓冲 = std::make_unique<t图形缓冲>(std::forward<t参数>(a参数)...);
	}
	I图形 &fg图形() const {
		return *m图形;
	}
	I图形缓冲 &fg图形缓冲() const {
		return *m图形缓冲;
	}
	std::shared_ptr<I图形> m图形;
	std::unique_ptr<I图形缓冲> m图形缓冲;
};
//接口
class I图形建造机 {
public:
	using t过程 = C图形建造过程;
	virtual void f接口_建造图形(t过程 &a过程) const = 0;
	virtual void f接口_建造图形缓冲(t过程 &a过程) const = 0;
};
//默认
template<T图形 t图形, T图形缓冲 t图形缓冲>
class C图形建造机 : public I图形建造机 {
public:
	static constexpr bool c图形默认构造函数 = std::is_default_constructible<t图形>::value;
	static constexpr bool c图形缓冲默认构造函数 = std::is_default_constructible<t图形缓冲>::value;
	C图形建造机() = default;
	void f接口_建造图形(t过程 &a过程) const override {
		if constexpr (c图形默认构造函数) {
			a过程.f建造图形<t图形>();
		} else {
			throw;	//没有默认构造函数,不实现
		}
	}
	void f接口_建造图形缓冲(t过程 &a过程) const override {
		if constexpr (c图形缓冲默认构造函数) {
			a过程.f建造图形缓冲<t图形缓冲>();
		} else {
			throw;	//没有默认构造函数,不实现
		}
	}
};
}	//namespace 东方山寨