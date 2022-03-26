module;
#include "关卡.h"
#include "游戏.h"
#include "王战.h"
#include "程序.h"
#include "界面引擎.h"
export module 东方山寨.关卡练习;	//进入符卡关卡
export namespace 东方山寨 {
//符卡练习关卡类
template<typename t初始事件, typename t弹幕事件>	//关卡事件:执行一些初始化
class C符卡练习关卡 : public C关卡 {
public:
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m关卡->fc脚本();
		v脚本.f事件<t初始事件>();
		v脚本.f等待(1);
		v脚本.f事件([]() {
			auto &v王战 = C游戏::fg内容().fg王战控制();
			v王战.f王战_开始(1);
			v王战.f事件<t弹幕事件>();
		});
	}
	void f事件_结束() override {
		C程序::f游戏中弹出菜单(E窗口::e游戏通关);
	}
};
//创建符卡练习关卡
using tp关卡 = std::unique_ptr<C关卡>;
template<typename t初始事件, typename t弹幕事件>
tp关卡 f符卡练习关卡() {
	return std::make_unique<C符卡练习关卡<t初始事件, t弹幕事件>>();
}
//符卡练习关卡工厂
using tf关卡 = std::function<tp关卡()>;
template<typename t初始事件, typename t弹幕事件>
tf关卡 F符卡练习关卡() {
	return &f符卡练习关卡<t初始事件, t弹幕事件>;
}
}	//namespace 东方山寨