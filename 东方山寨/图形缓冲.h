#pragma once
#include <type_traits>
#include <concepts>
#include "基础_游戏对象.h"
namespace 东方山寨 {
//图形缓冲接口
class I图形缓冲 : public C简单游戏对象 {
public:
	virtual void f显示() const = 0;
	int m图层 = 0;
	int m显示编号 = 0;
};
//判断是否有图形缓冲,当t中有 C图形缓冲 时为真
template<typename t> concept T有图形缓冲 = requires(t) {
	typename t::C图形缓冲;
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
};
template<typename t> concept T兼容图形缓冲 = requires {
	typename t::C图形缓冲;
	requires std::derived_from<typename t::C图形缓冲, I图形缓冲>;
	requires std::is_constructible_v<typename t::C图形缓冲, const t &>;
};
}	//namespace 东方山寨