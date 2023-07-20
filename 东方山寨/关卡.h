#pragma once
#include <map>
#include "数学包含.h"
#include "基础.h"
#include "对话基础.h"
namespace 东方山寨 {
class C关卡事件;
class C关卡脚本;
class C场景控制;
class I场景;
class C关卡;
using tp关卡 = std::shared_ptr<C关卡>;	//关卡指针
using ta关卡 = std::vector<tp关卡>;
class I关卡工厂;
using tp关卡工厂 = const I关卡工厂 *;
using ta关卡工厂 = std::vector<const I关卡工厂 *>;
//==============================================================================
// 关卡控制
//==============================================================================
enum class E关卡事件状态 {
	e初始化,
	e结束,
};
class C关卡事件状态 {
public:
	C关卡事件状态(const std::shared_ptr<C关卡事件> &);
	C关卡事件 &fg事件() const;
	bool fi存在() const;
	bool fi结束() const;	//与存在相反
	void f结束();
public:
	std::shared_ptr<C关卡事件> m事件;
	t标志 m标志;
	float m开始时间 = 0;
	float m等待 = 0;
};
class C关卡控制 {
public:
	enum E标志 {
		e使用,	//关卡进行中,如果事件都执行完毕则置0
		e王战,
		e对话,
	};
	typedef std::vector<std::shared_ptr<C关卡事件状态>> ta事件;
	void f对象_使用();
	void f对象_销毁();
	bool f对象_i使用() const;
	void f初始化_环境(C场景控制 &, C对话控制 &);
	void f切换_关卡(const tp关卡 &);	//记录即将切换的关卡,在游戏下次计算时切换
	void f切换_关卡组(const ta关卡工厂 &);
	bool f切换_计算();	//成功切换返回true
	void f开始关卡组(const ta关卡工厂 &);	//只设置关卡组状态,不含开始关卡
	void f开始关卡(const tp关卡 &);	//初始化控制状态,如果有关卡要先结束关卡
	void f结束关卡();	//清空控制状态
	void f切换关卡(const tp关卡 &, float 等待时间 = 0);	//切换到别的关卡
	C关卡脚本 fc脚本();
	void f计算();
	//关卡设置
	void f添加事件(std::shared_ptr<C关卡事件状态>);
	void f设置场景(std::shared_ptr<I场景>);
	void f事件_开始对话();	//由对话控制调用
	void f事件_结束对话();	//由对话控制调用
	//在关卡中调用
	void f动作_开始对话(tp对话脚本);	//开始对话,同时暂停经过时间
	std::shared_ptr<C关卡事件状态> fg事件(int);
	void f动作_增加难度();
	void f动作_增加难度(const boost::rational<int> &);
	void f动作_结束关卡(float 等待时间 = 0);	//当前关卡已经结束,从关卡列表中获取下一关卡并切换,如果没有则回到游戏标题画面
	float fg经过时间() const;
	bool fi对话() const;
private:
	void f合并事件();
public:
	ta事件 ma事件;
	ta事件 ma新事件;
	C场景控制 *m场景 = nullptr;
	C对话控制 *m对话 = nullptr;
	t标志 m标志;
	float m经过时间 = 0;
	tp关卡 m切换_关卡 = nullptr;	//下一关卡
	ta关卡工厂 m切换_关卡组;
	tp关卡 mp关卡 = nullptr;	//当前关卡
	ta关卡工厂 ma关卡工厂;
	unsigned char m当前关卡序号 = 0;
	unsigned char m关卡数量 = 1;
	unsigned int m随机数种子 = 0;	//当前关卡的随机数种子,每次初始化关卡时重新设置
};
class C关卡脚本 {	//用来增加关卡内容的类
public:
	C关卡脚本(C关卡控制 *);
	//脚本事件
	std::shared_ptr<C关卡事件状态> operator ()(const std::function<void()> &);	//和 f事件 一样
	template<typename t, typename...t参数> std::shared_ptr<C关卡事件状态> f事件(t参数 &&...);
	std::shared_ptr<C关卡事件状态> f事件(const std::function<void()> &);
	template<typename t, typename...t参数> std::shared_ptr<C关卡事件状态> f场景(t参数 &&...);
	std::shared_ptr<C关卡事件状态> f对话(tp对话脚本);
	//脚本时间
	void f时间点(float);
	void f等待(float);
private:
	std::shared_ptr<C关卡事件状态> f新事件_(const std::shared_ptr<C关卡事件> &);
private:
	C关卡控制 *m关卡控制 = nullptr;
	float m开始时间 = 0;
	float m经过时间 = 0;
};
//==============================================================================
// 关卡接口
//==============================================================================
class C关卡 : public I事件 {
	friend C关卡控制;
	friend I关卡工厂;
public:
	int fg标识() const;
protected:
	C关卡控制 *m控制 = nullptr;
	const I关卡工厂 *m工厂 = nullptr;	//工厂对象是全局变量,不用担心生命周期问题
};
//关卡事件
class C关卡事件 : public I事件 {
public:
	void f事件_执行() override;	//什么都不做,直接结束
	void f动作_暂停(float);	//暂停执行任何事件
	void f动作_结束();	//标记为结束,不会立即调用 f事件_结束
	float fg暂停时间() const;
public:
	C关卡事件状态 *m状态 = nullptr;
	C关卡控制 *m关卡 = nullptr;
};
//特殊关卡事件
class C关卡效果事件 : public C关卡事件 {
public:
	C关卡效果事件(const std::function<void()> &);
	void f事件_执行() override;
	std::function<void()> mf;
};
class C关卡场景事件 : public C关卡事件 {
public:
	C关卡场景事件(const std::shared_ptr<I场景> &);
	void f事件_执行() override;
	std::shared_ptr<I场景> m场景;
};
class C切换关卡事件 : public C关卡事件 {
public:
	C切换关卡事件(C关卡控制 &, const tp关卡 &);
	void f事件_执行() override;
	C关卡控制 *m关卡控制 = nullptr;
	const tp关卡 mp关卡 = nullptr;
};
//==============================================================================
// 关卡脚本实现
//==============================================================================
template<typename t, typename...t参数> std::shared_ptr<C关卡事件状态> C关卡脚本::f事件(t参数 &&...a参数) {
	static_assert(std::is_base_of<C关卡事件, t>::value, "必须继承自C关卡事件");
	return f新事件_(std::make_shared<t>(a参数...));
}
template<typename t, typename...t参数> std::shared_ptr<C关卡事件状态> C关卡脚本::f场景(t参数 &&...a参数) {
	static_assert(std::is_base_of<I场景, t>::value, "必须继承自I场景");
	return f新事件_(std::make_shared<C关卡场景事件>(std::make_shared<t>(a参数...)));
}
}	//namespace 东方山寨