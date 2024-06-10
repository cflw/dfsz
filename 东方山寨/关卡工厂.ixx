module;
#include "关卡.h"
#include "基础_对象工厂.h"
export module 东方山寨.关卡工厂;
export namespace 东方山寨 {
void f注册关卡(int a标识, const I关卡工厂 &a关卡工厂);	//定义在 关卡管理.ixx
class I关卡工厂 : public I工厂<I关卡> {
public:
	I关卡工厂(int);
	void f注册(int);
	int fg标识() const;
	void f初始化关卡(I关卡 &) const;	//给关卡赋值
	int m标识 = 0;
};
template<typename t关卡>
class C关卡工厂 : public I关卡工厂 {
public:
	using I关卡工厂::I关卡工厂;
	std::unique_ptr<I关卡> f接口_新建u() const override {
		auto v = std::make_unique<t关卡>();
		f初始化关卡(*v);
		return v;
	}
	std::shared_ptr<I关卡> f接口_新建s() const override {
		auto v = std::make_shared<t关卡>();
		f初始化关卡(*v);
		return v;
	}
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
I关卡工厂::I关卡工厂(int a标识) {
	f注册(a标识);
}
void I关卡工厂::f注册(int a标识) {
	f注册关卡(a标识, *this);
	m标识 = a标识;
}
int I关卡工厂::fg标识() const {
	return m标识;
}
void I关卡工厂::f初始化关卡(I关卡 &a关卡) const {
	a关卡.m工厂 = this;
}
}	//namespace 东方山寨