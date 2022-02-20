#pragma once
#include <type_traits>
#include <concepts>
#include <compare>
#include "基础_游戏对象.h"
#include "图层.h"
namespace 东方山寨 {
//图形缓冲接口
class I图形缓冲 : public C简单游戏对象 {
public:
	virtual ~I图形缓冲() = default;
	void f初始化_图层(int a图层) {
		m图层 = a图层;
		m显示编号 = 计算::fg显示编号();
	}
	virtual void f显示() const = 0;
	std::strong_ordering operator <=>(const I图形缓冲 &a图形缓冲) const {
		if (m图层 != a图形缓冲.m图层) {
			return m图层 <=> a图形缓冲.m图层;
		} else {
			return m显示编号 <=> a图形缓冲.m显示编号;
		}
	}
	int m图层 = (int)E图层::e无;
	int m显示编号 = 0;
};
template<typename t> concept T图形缓冲 = std::derived_from<t, I图形缓冲>;
//判断是否有图形缓冲,当t中有 C图形缓冲 时为真
template<typename t> concept T有图形缓冲 = requires(t) {
	typename t::t图形缓冲;
};
//出于代码向前兼容的考虑写的兼容图形缓冲类，直接继承就行，不用对代码做太多修改，把“f接口_显示”改成“f兼容显示”即可。
//该兼容代码存在数据竞争，以后全部改掉删掉
template<typename t>
class C兼容图形缓冲 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		C图形缓冲(const t &a) {
			m = &a;
		}
		void f显示() const override {
			m->f兼容显示();
		}
		const t *m = nullptr;
	};
	using t图形缓冲 = C图形缓冲;
};
template<typename t> concept T兼容图形缓冲 = requires {
	typename t::t图形缓冲;
	requires std::derived_from<typename t::t图形缓冲, I图形缓冲>;
	requires std::is_constructible_v<typename t::t图形缓冲, const t &>;
};
}	//namespace 东方山寨