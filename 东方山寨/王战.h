#pragma once
#include <vector>
#include <memory>
#include "关卡.h"
namespace 东方山寨 {
class C王战事件;
class C敌机;
class C总血条;
class C弹幕时间;
class C王战控制 {
public:
	template<typename t, typename...t参数> std::shared_ptr<C关卡事件状态> f事件(const t参数 &...);
	std::shared_ptr<C关卡事件状态> f新事件_(const std::shared_ptr<C王战事件> &);
	void f初始化_环境(C关卡控制 &);	//在引擎中调用
	void f计算();
	void f王战开始(int 事件总数);
	void f王战结束();
	void f符卡开始(const std::wstring &名称, int 分数);
	void f符卡结束();
	void fs时间(float 秒, float 冻结 = 1);
	void f时间冻结(float 冻结);
	void f总血条减一();
	t标志::reference fg王战标志();
	bool fg王战标志() const;
	void fs王(C敌机 *);
	void fs王(std::shared_ptr<C敌机>);
	C敌机 *fg击破();
	C敌机 *fg王(int = 0) const;
private:
	void f事件结束();
	C关卡控制 *m关卡控制 = nullptr;
	std::vector<C敌机 *> ma王;
	std::shared_ptr<C总血条> m总血条;
	std::shared_ptr<C弹幕时间> m弹幕时间;
	C王战事件 *m事件 = nullptr;
	float m时间 = 0, m冻结 = 0, m地板 = 0;
	C敌机 *m击破 = nullptr;
	bool mi结束 = false;	//保证 王被击破,时间到 只能调用其中一个一次
};
class C王战事件 : public C关卡事件 {
public:
	virtual void f事件_王被击破(C敌机 &) {}
	virtual void f事件_时间到() {}
public:
	C王战控制 *m王战;
	C关卡控制 *m关卡;
};
template<typename t, typename...t参数> std::shared_ptr<C关卡事件状态> C王战控制::f事件(const t参数 &...a参数) {
	static_assert(std::is_base_of<C王战事件, t>::value, "必须继承自C王战事件");
	return f新事件_(std::make_shared<t>(a参数...));
}

}