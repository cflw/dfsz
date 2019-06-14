#pragma once
#include <assert.h>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <atomic>
#include <mutex>
#include <execution>
#include <wrl.h>
#include <cflw工具_循环.h>
#include "游戏_名称标识.h"
namespace 东方山寨 {
using Microsoft::WRL::ComPtr;
namespace 循环 = cflw::工具::循环;
//==============================================================================
// 静态/动态数组,数组元素必需是游戏对象
//==============================================================================
class C数组计数 {
public:
	C数组计数(size_t a数量): m数量(a数量) {
		m计数 = 0;
	}
	void f加计数() {
		//assert(m计数 < m数量);
		++m计数;
		m加变化 = true;
	}
	void f减计数() {
		assert(m计数 > 0);
		--m计数;
		m减变化 = true;
	}
	size_t fg计数() const {
		return m计数;
	}
	bool fi变化() const {
		return m加变化 || m减变化;
	}
	bool fi加变化() const {
		return m加变化;
	}
	bool fi减变化() const {
		return m减变化;
	}
	void f无变化() {
		m加变化 = false;
		m减变化 = false;
	}
	void f无加变化() {
		m加变化 = false;
	}
	void f无减变化() {
		m减变化 = false;
	}
	operator size_t() {
		return m计数;
	}
private:
	const size_t m数量;
	std::atomic<size_t> m计数;
	bool m加变化 = false, m减变化 = false;
};
//对象数组
template<typename t> class C对象数组 {
public:
	using value_type = t;
	using reference = t & ;
	using const_reference = const t&;
	typedef std::shared_ptr<t> t指针;
	C对象数组(size_t a数量): m计数(a数量), m数量上限(a数量) {
		ma对象.reserve(a数量);
	}
	~C对象数组() {
	}
	void f清空() {
		ma对象.clear();
		ma新建.clear();
	}
	void f添加(t指针 ap) {
		std::lock_guard<std::mutex> m保护锁(m互斥锁);
		ma新建.push_back(ap);
	}
	bool fi有空(size_t a数量 = 1) const {
		return m当前数量 + a数量 <= fg上限();
	}
	bool fi无空() const {
		return m当前数量 >= fg上限();
	}
	size_t fg计数() const {
		return m当前数量;
	}
	size_t fg上限() const {
		return m数量上限;
	}
	bool fi变化() const {
		return m计数.fi变化();
	}
	void fe使用(std::function<void(t&)> af) {
		std::for_each(std::execution::seq, ma对象.begin(), ma对象.end(), [&af](const t指针 &ap对象) {
			if (ap对象->f对象_i使用()) {
				af(*ap对象);
			}
		});
	}
	void fe使用p(std::function<void(t指针)> af) {
		std::for_each(std::execution::seq, ma对象.begin(), ma对象.end(), [&af](const t指针 &ap对象) {
			if (ap对象->f对象_i使用()) {
				af(ap对象);
			}
		});
	}
	void fe使用_并行(std::function<void(t&)> af) {
		std::for_each(std::execution::par, ma对象.begin(), ma对象.end(), [&af](const t指针 &ap对象) {
			if (ap对象->f对象_i使用()) {
				af(*ap对象);
			}
		});
	}
	void f更新() {
		f更新_删除不使用对象();
		f更新_合并新对象();
		f更新数量();
		assert(m当前数量 == ma对象.size());
	}
	void f更新_删除不使用对象() {
		if (m计数.fi减变化()) {
			ma对象.erase(std::remove_if(ma对象.begin(), ma对象.end(), [](const t指针 &a指针)->bool {
				return !a指针->f对象_i使用();
			}), ma对象.end());
			m计数.f无减变化();
		}
	}
	void f更新_合并新对象() {
		if (m计数.fi加变化()) {
			assert(!ma新建.empty());
			std::copy(ma新建.begin(), ma新建.end(), std::back_inserter(ma对象));
			ma新建.clear();
			m计数.f无加变化();
		}
	}
	void f更新数量() {
		m当前数量 = m计数.fg计数();
	}
	std::vector<t指针> ma对象;
	std::vector<t指针> ma新建;
	const size_t m数量上限;
	size_t m当前数量 = 0;
	C数组计数 m计数;
	std::mutex m互斥锁;
};
//动态数组
template<typename t> class C动态数组 : public std::vector<t> {
public:
	using value_type = t;
	using reference = t & ;
	using const_reference = const t&;
	using t基 = std::vector<t>;
	C动态数组() = default;
	void f清空() {
		for (auto v = t基::begin(); v != t基::end(); ++v) {
			if (v->f对象_i使用()) {
				v->f对象_销毁();
			}
		}
	};
	void f新建(int a数量, std::function<void(t &, int)> p新建) {
		int v数量 = 0;
		for (int i = 0; i < t基::size(); ++i) {
			t &v = t基::operator[](i);
			if (!v.f对象_i使用()) {
				p新建(v, i);
				++v数量;
				if (v数量 >= a数量) {
					return;
				}
			}
		}
		for (;v数量 < a数量; ++v数量) {
			t v;
			p新建(v, t基::size());
			t基::push_back(v);
		}
	}
	int f连续新建(int a数量, std::function<void(t &)> p新建) {
		int v位置 = 0;
		int v数量 = 0;
		for (int i = 0; i < t基::size(); ++i) {
			t &v = t基::operator[](i);
			if (v.f对象_i使用()) {
				v位置 = i + 1;
			} else {
				++v数量;
				if (v数量 >= a数量) {
					break;
				}
			}
		}
		v数量 = 0;
		while (v数量 < a数量) {
			const int v当前位置 = v位置 + v数量;
			if (v当前位置 < t基::size()) {
				p新建(t基::operator[](v当前位置));
			} else {
				t v;
				p新建(v);
				t基::push_back(v);
			}
			++v数量;
		}
		return v位置;
	}
};
//==============================================================================
// 映射数组
//==============================================================================
//映射指针
template<typename t值> class C映射指针 {
public:
	typedef C映射指针<t值> t这;
	C映射指针() = default;
	C映射指针(int a整数, t值 *a指针) :
		m整数(a整数), m指针(a指针) {
	}
	t这 &operator =(int a整数) {
		if (a整数 == 0) {
			f清空();
		} else if (m整数 != a整数) {
			m名称.clear();
			m整数 = a整数;
			m指针 = nullptr;
		}
		return *this;
	}
	t这 &operator =(t值 *a指针) {
		m名称.clear();
		m整数 = 0;
		m指针 = a指针;
		return *this;
	}
	t这 &operator =(const std::wstring &a名称) {
		if (a名称.empty()) {
			f清空();
		} else if (a名称 != m名称) {
			m名称 = a名称;
			m整数 = 0;
			m指针 = nullptr;
		}
		return *this;
	}
	t这 &operator =(t值 &a值) {
		m指针 = std::addressof(a值);
		m整数 = 0;
		m名称.clear();
		return *this;
	}
	t值 *operator ->() const {
		return m指针;
	}
	t值 &operator *() const {
		return *m指针;
	}
	t值 &operator [](int a) const {
		return m指针[a];
	}
	operator bool() const {
		return m指针 != nullptr;
	}
	bool fi需编译() const {
		return m指针 == nullptr;
	}
	bool fi需解析名称() const {
		if (m名称.empty()) {	//没名称
			return false;
		} else if (m整数 == 0) {	//有名称没解析过
			return true;
		} else {	//解析过了
			return false;
		}
	}
	void f编译赋值(t值 *a指针) {
		m指针 = a指针;
	}
	void f清空() {
		m名称.clear();
		m整数 = 0;
		m指针 = nullptr;
	}
	std::wstring m名称;
	int m整数 = 0;	//值在数组中的序号
	t值 *m指针 = nullptr;	//指向值
};
//缓存指针,指的地址经常发生变化时使用
template<typename t值> class C缓存指针 {
public:
	using t这 = C缓存指针<t值>;
	C缓存指针() = default;
	C缓存指针(int p数, t值 *a指针) :
		m整数(p数), m指针(a指针) {
	}
	t这 &operator =(int p整数) {
		m整数 = p整数;
		return *this;
	}
	t这 &operator =(t值 *a指针) {
		m整数 = 0;
		m指针 = a指针;
		return *this;
	}
	t值 *operator ->() const {
		return m指针;
	}
	t值 &operator *() const {
		return *m指针;
	}
	t值 &operator [](int a) const {
		return m指针[a];
	}
	operator bool() const {
		return m指针 != nullptr;
	}
	bool fi需编译() const {
		return m整数 != m缓存 || m指针 == nullptr;
	}
	void f编译赋值(t值 *a指针) {
		m缓存 = m整数;
		m指针 = a指针;
	}
	int m整数 = 0;	//值在数组中的序号
	int m缓存 = -1;	//编译时赋值
	t值 *m指针 = nullptr;	//指向值
};
//别名
template<typename t> using t属性指针 = C映射指针<const t>;
template<typename t> using t扩展指针 = C映射指针<t>;
//属性数组
template<typename t值> class C属性数组;
template<typename t> const ComPtr<t> &f取属性数组数据指针(const C属性数组<ComPtr<t>> &, int);
template<typename t> const std::shared_ptr<t> &f取属性数组数据指针(const C属性数组<std::shared_ptr<t>> &, int);
template<typename t> const t *f取属性数组数据指针(const C属性数组<t> &, int);
template<typename t值> class C属性数组 {
public:
	using value_type = t值;
	using reference = t值&;
	using const_reference = const t值&;
	using t指针 = t属性指针<t值>;
	C属性数组() = default;
	auto operator [](const std::wstring &) const->decltype(f取属性数组数据指针(std::declval<C属性数组<t值>>(), 0));
	void f添加(int a键, const t值 &a值) {
		assert(fi不存在(a键));
		ma映射.emplace(a键, ma数据.size());
		ma数据.push_back(a值);
	}
	void f添加(int a键, const std::initializer_list<t值> &aa值) {
		assert(fi不存在(a键));
		int i = 0;
		for (const auto &v值 : aa值) {
			ma映射.emplace(计算::f键(a键, i++), ma数据.size());
			ma数据.push_back(v值);
		}
	}
	template<typename...t参数>
	void f构造(int a键, t参数 &&...a参数) {
		assert(fi不存在(a键));
		ma映射.emplace(a键, ma数据.size());
		ma数据.emplace_back(a参数...);
	}
	void f引用(int a键0, int a键1) {
		assert(fi不存在(a键0));
		ma映射.emplace(a键0, ma映射.at(a键1));
	}
	t值 &f取空(int a键) {
		assert(fi不存在(a键));
		ma映射[a键] = ma数据.size();
		ma数据.emplace_back();
		return ma数据.back();
	}
	t指针 f找(int a键) const {
		if (a键) {
			assert(fi存在(a键));
			return t指针(a键, fg指针(a键));
		} else {
			return t指针{};
		}
	}
	const t值 &fg数据(int a键) const {
		assert(fi存在(a键));
		const int v位置 = ma映射.at(a键);
		return ma数据[v位置];
	}
	const t值 *fg指针(int a键) const {
		if (a键) {
			assert(fi存在(a键));
			const int v位置 = ma映射.at(a键);
			return ma数据.data() + v位置;
		} else {
			return nullptr;
		}
	}
	bool fi存在(int a键) const {
		return ma映射.find(a键) != ma映射.end();
	};
	bool fi不存在(int a键) const {
		return ma映射.find(a键) == ma映射.end();
	}
	void f编译(t指针 &a指针) const {
		if (a指针.fi需解析名称()) {
			a指针.m整数 = C名称标识::f解析名称(a指针.m名称);
		}
		if (a指针.m整数) {
			a指针.m指针 = fg指针(a指针.m整数);
		} else {
			a指针.m指针 = nullptr;
		}
	}
	void f清空() {
		ma映射.clear();
		ma数据.clear();
	}
public:
	std::map<int, int> ma映射;	//标识到序号
	std::vector<t值> ma数据;
};
template<typename t> 
const ComPtr<t> &f取属性数组数据指针(const C属性数组<ComPtr<t>> &a数组, int a标识) {
	if (auto v指针 = a数组.f找(a标识)) {
		return *v指针;
	} else {
		return nullptr;
	}
}
template<typename t> 
const std::shared_ptr<t> &f取属性数组数据指针(const C属性数组<std::shared_ptr<t>> &a数组, int a标识) {
	if (auto v指针 = a数组.f找(a标识)) {
		return *v指针;
	} else {
		return nullptr;
	}
}
template<typename t> 
const t *f取属性数组数据指针(const C属性数组<t> &a数组, int a标识) {
	return a数组.fg指针(a标识);
}
template<typename t值>
auto C属性数组<t值>::operator [](const std::wstring &a) const
	->decltype(f取属性数组数据指针(std::declval<C属性数组<t值>>(), 0)) {
	return f取属性数组数据指针(*this, C游戏::fg资源().fg标识(a));
}
//扩展数组
template<typename t值> class C扩展数组 : public std::map<int, std::unique_ptr<t值>> {
public:
	using value_type = t值;
	using reference = t值 & ;
	using const_reference = const t值&;

	typedef std::map<int, std::unique_ptr<t值>> t基类;
	typedef t扩展指针<t值> t指针;
	typedef C缓存指针<const t值> t缓存指针;
	C扩展数组() {
		f添加(0, nullptr);
	}
	void f添加(int a键, t值 *a值) {
		if (a键 == 0) {
			assert(t基类::operator[](a键) == nullptr);
		} else {
			assert(!fi存在(a键));
		}
		t基类::operator[](a键).reset(a值);
	}
	template<typename t派生, typename...t参数>
	void f构造(int a键, t参数 &&...a参数) {
		static_assert(std::is_base_of<t值, t派生>::value, "t派生 必须是 t值 的基类");
		f添加(a键, new t派生(a参数...));
	}
	std::unique_ptr<t值> &f取空(int a键) {
		assert(t基类::find(a键) == t基类::end());
		return t基类::operator[](a键);
	}
	t指针 f找(int a键) const {
		assert(fi存在(a键));
		return t指针(a键, fg扩展(a键));
	}
	t值 *fg扩展(int a键) const {
		assert(fi存在(a键));
		return t基类::at(a键).get();
	}
	bool fi存在(int a键) const {
		return t基类::find(a键) != t基类::end();
	}
	void f编译(t指针 &a指针) {
		if (a指针.fi需解析名称()) {
			a指针.m整数 = C名称标识::f解析名称(a指针.m名称);
		}
		a指针.m指针 = fg扩展(a指针.m整数);
	}
};
}