#pragma once
#include <future>
#include <thread>
#include <Windows.h>
#include <cflw时间.h>
#include <cflw视窗.h>
#include <cflw工具.h>
#include "程序.h"
#include "基础.h"
#include "界面常量.h"
namespace 东方山寨 {
namespace 时间 = cflw::时间;
namespace 视窗 = cflw::视窗;
namespace 工具 = cflw::工具;
enum class E窗口;	//位于 界面常量.h
class C设置管理;
class C文本管理;
class C图形引擎;
class C输入引擎;
class C音频引擎;
class C界面引擎;
class C界面图形控制;
class C界面音频;
class C游戏;
class C游戏状态控制;
class C游戏输入管理;
class C游戏录像管理;
class C画帧速率;
class C日志;
//程序实现
class C程序实现 {
public:
	static C程序实现 *g这;
	HINSTANCE m实例 = nullptr;
	HWND m窗口 = nullptr;
	int m窗口大小[2] = {};
	float m缩放 = 0;
	时间::C计时器 m计时器;
	工具::C计次器 m计次器;
	std::unique_ptr<C设置管理> m设置;
	std::unique_ptr<C文本管理> m文本;
	std::unique_ptr<C图形引擎> m图形;
	std::unique_ptr<C输入引擎> m输入;
	std::unique_ptr<C音频引擎> m音频;
	std::unique_ptr<C界面引擎> m界面;
	std::unique_ptr<C界面图形控制> m界面图形;
	std::unique_ptr<C界面音频> m界面音频;
	std::unique_ptr<C游戏> m游戏;
	std::unique_ptr<C游戏状态控制> m游戏状态;
	std::unique_ptr<C游戏录像管理> m录像管理;
	std::unique_ptr<C游戏输入管理> m游戏输入;
	std::unique_ptr<C画帧速率> m画帧速率;
	std::unique_ptr<C日志> m日志;
	视窗::C输入法开关 m输入法开关;
	int m渲染间隔 = 1;
	t标志 m标志;
	//异步任务
	//std::future<void> m任务_载入;
	//std::future<void> m任务_资源;
	std::thread m线程_显示;
	std::atomic<bool> mi显示循环 = true;
	std::atomic<bool> mi显示就绪 = false;
	bool mi游戏显示就绪 = false;
public:
	C程序实现(HINSTANCE);
	~C程序实现();
	void f运行();
	static LRESULT WINAPI f窗口过程(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void f创建窗口();
	void f初始化();
	void f初始化1();	//重要资源载入完成时调用
	void f初始化2();	//所有资源载入完成时调用
	void f销毁();
	void f计算();
	void f更新();
	void f显示();
	void f线程_显示();
	void f快速开始游戏();	//调试用,载入完毕后马上进入游戏
	void f快速回放录像();	//调试用,载入完毕后马上回放
	void f切换游戏状态(E游戏状态);
	void f游戏中弹出菜单(E窗口);
	void fs渲染间隔(int);
	void f输入法开关(bool);
	void f计算窗口尺寸和缩放();
	void f日志(int 级别, const std::wstring &);
	void fs全屏(bool);
	void fs窗口大小(int, int);
};
}	//namespace 东方山寨