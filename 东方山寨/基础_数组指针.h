#pragma once
#include <string>
#include <memory>
namespace 东方山寨 {
//映射指针
template<typename t值> class C映射指针 {
public:
	typedef C映射指针<t值> t这;
	C映射指针() = default;
	C映射指针(int a整数, t值 *a指针):
		m整数(a整数), m指针(a指针) {
	}
	C映射指针(int a整数):
		m整数(a整数), m指针(nullptr) {
	}
	C映射指针(t值 *a指针):
		m整数(0), m指针(a指针) {
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
	C缓存指针(int a数, t值 *a指针) :
		m整数(a数), m指针(a指针) {
	}
	t这 &operator =(int a整数) {
		m整数 = a整数;
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
}	//namespace 东方山寨