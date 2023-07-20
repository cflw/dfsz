module;
#include "关卡.h"
#include "游戏.h"
#include "王战.h"
export module 东方山寨.关卡练习;	//进入符卡关卡
export import 东方山寨.关卡工厂;
export namespace 东方山寨 {
//符卡练习关卡类
template<typename t初始事件, typename t弹幕事件>	//关卡事件:执行一些初始化
class C符卡练习关卡 : public C关卡 {
public:
	static tp关卡 f创建() {
		return std::make_unique<C符卡练习关卡<t初始事件, t弹幕事件>>();
	}
	void f事件_初始化() override {
		C关卡脚本 v脚本 = m控制->fc脚本();
		v脚本.f事件<t初始事件>();
		v脚本.f等待(1);
		v脚本.f事件([]() {
			auto &v王战 = C游戏::fg内容().fg王战控制();
			v王战.f王战_开始(1);
			v王战.f事件<t弹幕事件>();
		});
	}
	void f事件_结束() override {
		C游戏::fg内容().f游戏_通关菜单();
	}
};
//符卡练习关卡工厂
template<typename t初始事件, typename t弹幕事件>
using C符卡练习关卡工厂 = C关卡工厂<C符卡练习关卡<t初始事件, t弹幕事件>>;
}	//namespace 东方山寨