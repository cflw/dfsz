#pragma once
#include <vector>
#include <memory>
#include "关卡.h"
namespace 东方山寨 {
class C王战事件;
class C敌机;
class C总血条;
class C弹幕时间;
class C符卡文本;
class C王战时间控制 {
public:
	void f计算();
	bool fi时间到() const;
	void fs时间(float 秒, float 冻结 = 1);
	void f冻结(float 冻结);
	float fg倒计时() const;
	float fg正计时() const;
	float fg倒计时百分比() const;
	float fg显示倒计时() const;	//不会显示负数
private:
	float m总时间 = 0;
	float m倒计时 = 0;	//倒计时
	float m冻结 = 0;
	float m地板 = 0;	//floor(m时间)
};
class C符卡控制 {
public:
	enum E标志 {
		e发动,
		e时间符,
	};
	C符卡控制(const C王战时间控制 &);
	void f开始(const std::wstring &名称, int 分数, bool 时间符 = false);	//在关卡事件中调用
	void f结束();	//王战控制中调用
	void f分数减半();//每次死亡后减半
	//属性
	int fg当前分数() const;	//当前分数 = m分数 * 倒计时% / m除数
	const std::wstring &fg名称() const;
	bool fi发动() const;
	bool fi时间符() const;
private:
	const C王战时间控制 *m时间 = nullptr;
	std::wstring m名称;
	int m分数 = 0;
	int m除数 = 1;
	t标志 m标志;
};
class C王战控制 {
public:
	template<typename t, typename...t参数> std::shared_ptr<C关卡事件状态> f事件(const t参数 &...);
	std::shared_ptr<C关卡事件状态> f新事件_(const std::shared_ptr<C王战事件> &);
	void f初始化_环境(C关卡控制 &);	//在引擎中调用
	void f计算();
	void f王战_开始(int 事件数);	//血条数=事件数-1
	void f王战_结束();
	void f弹幕_s时间(float 时间, float 冻结 = 1);
	void f弹幕_s符卡(const std::wstring &名称, int 分数, bool 时间符 = false);	//开始流程,显示文字
	void f总血条减一();
	//属性
	t标志::reference fg王战标志();
	bool fi王战() const;
	void fs王(C敌机 *);
	void fs王(const std::shared_ptr<C敌机> &);
	C敌机 *fg击破的王();	//没有击破则返回空指针
	C敌机 *fg王(int = 0) const;
private:
	void f事件结束();
	C关卡控制 *m关卡控制 = nullptr;
	C王战时间控制 m时间控制;
	C符卡控制 m符卡控制 = {m时间控制};
	std::vector<C敌机 *> ma王;
	std::shared_ptr<C总血条> m总血条;	//图形
	std::shared_ptr<C弹幕时间> m弹幕时间;	//图形
	std::shared_ptr<C符卡文本> m符卡文本;	//图形
	C王战事件 *m事件 = nullptr;
	C敌机 *m击破 = nullptr;
	bool mi结束 = false;	//保证 王被击破,时间到 只能调用其中一个一次
};
class C王战事件 : public C关卡事件 {
public:
	virtual void f事件_王被击破(C敌机 &) {}
	virtual void f事件_时间到() {}
public:
	C王战控制 *m王战 = nullptr;
	C关卡控制 *m关卡 = nullptr;
};
template<typename t, typename...t参数> std::shared_ptr<C关卡事件状态> C王战控制::f事件(const t参数 &...a参数) {
	static_assert(std::is_base_of<C王战事件, t>::value, "必须继承自C王战事件");
	return f新事件_(std::make_shared<t>(a参数...));
}
}	//namespace 东方山寨