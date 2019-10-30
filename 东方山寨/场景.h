#pragma once
#include "图形_三维.h"
namespace 东方山寨 {
class I场景 {
public:
	virtual void f接口_初始化();
	virtual void f接口_计算();
	virtual void f接口_更新();
	virtual void f接口_显示(C画三维 &) const;
};
class C场景控制 {
public:
	void f初始化_图形(C画三维 &);
	void f设置场景(std::shared_ptr<I场景>);
	void f计算();
	void f更新();
	void f显示() const;
private:
	std::shared_ptr<I场景> m场景, m新场景;
	C画三维 *m画三维 = nullptr;
};
}