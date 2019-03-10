#pragma once
#include <map>
#include "基础.h"
#include "输入.h"
#include "对话基础.h"
namespace 东方山寨 {
class C关卡控制;
class C对话框;
class I对话立绘;
class C对话控制 {
public:
	static constexpr float c跳过间隔 = 0.1f;
	static constexpr float c按住确定跳过的等待时间 = 1;
	void f初始化_环境(C关卡控制 &);
	void f计算();
	void f输入按键(const 输入::C按键组 &);
	void f开始(tp对话脚本);
	void f结束();
	void f按键控制_下一个();	//按z时调用
	void f按键控制_跳过();	//按ctrl,或持续按z时调用
	t标志::reference fg对话标记();
	bool fg对话标记() const;
	bool fi对话中() const;
	bool fw结束() const;
	//控制
	void f控制_新对话框(const S对话参数_对话 &);
	void f控制_显示立绘(const S对话参数_显示立绘 &);
	void f控制_立绘状态(const S对话参数_立绘状态 &);
	void f控制_等待();	//和继续互斥
	void f控制_继续();	//继续执行下一个事件,和等待互斥
private:
	void f内部_执行对话事件();
	void f内部_结束对话框();
	void f内部_立绘焦点(I对话立绘 *);
	tp对话脚本 m对话脚本;
	ta对话事件::const_iterator m当前对话;
	std::shared_ptr<C对话框> m当前对话框;
	std::map<int, std::shared_ptr<I对话立绘>> ma对话立绘;
	I对话立绘 *m当前立绘 = nullptr;
	C关卡控制 *m关卡;
	float m跳过等待 = 0;	//减
	float m自动等待 = 0;	//加,没有操作时等一段时间自动下一个对话
	float m自动间隔 = 10;	//时间根据字符数调整
	float m输入_确定时间 = 0;	//按住z的时间
	bool m等待 = false;
};
class C对话脚本 {
public:
	operator tp对话脚本() const;
	C对话脚本 &f对话(const std::wstring &, bool = false);
	C对话脚本 &f显示立绘(const I工厂<I对话立绘> &, int 标识, bool 方向);	//不要传递临时工厂对象
	C对话脚本 &f立绘聚焦(int 标识);
	C对话脚本 &f立绘消失(int 标识);
	std::shared_ptr<ta对话事件> ma对话事件 = std::make_shared<ta对话事件>();
};
class I对话事件 {
public:
	virtual void f接口_触发(C对话控制 &) = 0;
};
namespace 对话事件 {
class C对话 : public I对话事件 {
public:
	C对话(S对话参数_对话 &&);
	void f接口_触发(C对话控制 &) override;
	S对话参数_对话 m参数;
};
class C显示立绘 : public I对话事件 {
public:
	C显示立绘(S对话参数_显示立绘 &&);
	void f接口_触发(C对话控制 &) override;
	S对话参数_显示立绘 m参数;
};
class C立绘状态 : public I对话事件 {
public:
	C立绘状态(S对话参数_立绘状态 &&);
	void f接口_触发(C对话控制 &) override;
	S对话参数_立绘状态 m参数;
};
}	//namespace 对话事件
}	//namespace 东方山寨