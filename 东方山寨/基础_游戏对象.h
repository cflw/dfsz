#pragma once
#include <concepts>
namespace 东方山寨 {
// 游戏对象不用继承,但是方法要自已实现.因为这涉及到静态/动态数组对游戏对象的管理
class I游戏对象 {
public:
	virtual void f对象_使用() = 0;
	virtual void f对象_销毁() = 0;
	virtual bool f对象_i使用() const = 0;
};
template<typename t对象> concept T游戏对象 = requires(t对象 a) {
	a.f对象_使用();
	a.f对象_销毁();
	{ a.f对象_i使用() }->std::same_as<bool>;
};
//简单游戏对象在偷懒时可以直接继承
class C简单游戏对象 {
public:
	C简单游戏对象() = default;
	void f对象_使用() {
		mi使用 = true;
	}
	void f对象_销毁() {
		mi使用 = false;
	}
	bool f对象_i使用() const {
		return mi使用;
	}
private:
	bool mi使用 = true;
};
}	//namespace 东方山寨