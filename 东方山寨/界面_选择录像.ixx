module;
#include <format>
#include <cflw时间.h>
#include "界面包含.h"
#include "程序.h"
export module 东方山寨.界面_选择录像;
export import 用户界面.控件;
import 东方山寨.文本管理;
import 东方山寨.游戏录像管理;
import 东方山寨.游戏输入管理;
export import 东方山寨.界面语言;
namespace 时间 = cflw::时间;
export namespace 东方山寨 {
class W选择录像 : public 用户界面::W窗口框架, public I跟踪界面语言 {
public:
	static constexpr int c列数 = 7;	//序号,标题,玩家,时间,机型,难度,关卡
	static constexpr int c行数 = 10;
	static constexpr int c行标识 = 1206208901;	//随机,唯一
	W选择录像() = default;
	void f响应_载入() override;
	void f响应_初始化() override;
	void f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) override;
	void f事件_刷新文本() override;
	void f刷新列表();
	用户界面::W表格 w表格;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
void W选择录像::f响应_载入() {
	const 用户界面::W表格::S列属性 ca列[] = {
		{1}, {5}, {5}, {4}, {2}, {2}, {2}
	};
	w表格.f初始化_列(ca列, c列数);
	w表格.f初始化_行({}, c行数);
	w表格.f属性_s布局(t矩形::fc坐标半尺寸(t向量2(), t向量2(300, 200)));
	w表格.f属性_s标题行(true);
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	w表格.fg标题行().f流() << va界面文本[L"replay.title.number"]
		<< va界面文本[L"replay.title.title"]
		<< va界面文本[L"replay.title.player"]
		<< va界面文本[L"replay.title.time"]
		<< va界面文本[L"replay.title.role"]
		<< va界面文本[L"replay.title.difficult"]
		<< va界面文本[L"replay.title.stage"];
}
void W选择录像::f响应_初始化() {
	f动作_添加窗口(w表格, true);
	f动作_显示();
	f刷新列表();
}
void W选择录像::f事件_按键(用户界面::W窗口 &a窗口, const 用户界面::S按键参数 &a参数) {
	if (a窗口.m标识 == c行标识) {
		C游戏录像管理 &v录像管理 = *C游戏录像管理::g这;
		auto &vp录像 = v录像管理.ma摘要.at(a窗口.m值);
		if (!vp录像->fi完整数据()) {
			v录像管理.f完整打开录像(vp录像);	//没有异常处理,以后再写
		}
		//先实现点击录像直接播放录像
		C回放机 &v回放 = v录像管理.f回放录像(vp录像);
		C游戏::fs游戏设置(v回放.fg游戏设置());
		C游戏::fs游戏输入(C游戏输入管理::fg实例().fc回放(v回放));
		C程序::f切换游戏状态(E游戏状态::e游戏中);
	}
}
void W选择录像::f刷新列表() {
	C游戏录像管理 &v录像管理 = *C游戏录像管理::g这;
	v录像管理.f全量刷新();
	w表格.f清空行();
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (auto &[v序号, vp录像] : v录像管理.ma摘要) {
		w表格.f新行(c行标识, v序号).f流() << v序号
			<< vp录像->fg录像标题()
			<< vp录像->fg玩家名称()
			<< std::format(c标准时间格式, 时间::f本地秒(vp录像->fg结束时间()))
			<< va界面文本[vp录像->fg机型()]
			<< vp录像->fg难度()
			<< vp录像->fg关卡();
	}
}
void W选择录像::f事件_刷新文本() {
	//const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	//for (auto &vp按钮 : ma按钮) {
	//	vp按钮->f生成文本(va界面文本);
	//}
}
}	//namespace 东方山寨