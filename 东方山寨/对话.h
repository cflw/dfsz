#pragma once
#include <map>
#include "基础.h"
#include "基础_对象工厂.h"
#include "输入.h"
#include "对话基础.h"
namespace 东方山寨 {
class C关卡控制;
class C对话框;
class I对话立绘;
class I图形建造机;
enum class E立绘表情;
class C对话控制 {
public:
	static constexpr float c跳过间隔 = 0.1f;
	static constexpr float c按住确定跳过的等待时间 = 1;
	~C对话控制();
	void f初始化_环境(C关卡控制 &);
	void f计算();
	void f输入按键(const 输入::C按键组 &);
	void f开始(tp对话脚本);
	void f结束();
	void f按键控制_下一个();	//按z时调用
	void f按键控制_跳过();	//按ctrl,或持续按z时调用
	bool fi对话中() const;
	bool fi结束() const;
	//控制
	void f控制_新对话框(const S对话参数_对话 &);
	void f控制_显示立绘(const S对话参数_显示立绘 &);
	void f控制_立绘状态(const S对话参数_立绘状态 &);
	void f控制_立绘表情(const S对话参数_立绘表情 &);
	void f控制_等待();	//等待按键才能执行下一个事件,和继续互斥
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
struct S对话立绘句柄 {
	I对话立绘 *m立绘 = nullptr;
};
class C对话脚本 {
public:
	operator tp对话脚本() const;
	C对话脚本 &f对话(const std::wstring &, E对话方向 = E对话方向::e从左向右);
	C对话脚本 &f显示立绘(const I图形建造机 &, int 标识, E对话方向 方向);	//不要传递临时对象
	C对话脚本 &f立绘聚焦(int 标识);
	C对话脚本 &f立绘消失(int 标识);
	C对话脚本 &f立绘表情(int 标识, E立绘表情);
public:
	std::shared_ptr<ta对话事件> ma对话事件 = std::make_shared<ta对话事件>();
};
namespace 对话事件 {
tf对话事件 F对话(S对话参数_对话);
tf对话事件 F显示立绘(S对话参数_显示立绘);
tf对话事件 F立绘状态(S对话参数_立绘状态);
tf对话事件 F立绘表情(S对话参数_立绘表情);
}	//namespace 对话事件
}	//namespace 东方山寨