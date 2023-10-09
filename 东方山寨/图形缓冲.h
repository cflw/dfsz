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
}	//namespace 东方山寨