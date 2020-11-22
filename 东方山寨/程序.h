#pragma once
#include <map>
#include <memory>
#include <string>
#include <filesystem>
#include <utility>
#include <Windows.h>
namespace 东方山寨 {
enum class E游戏状态 {
	e无,
	e载入中,
	e主菜单,
	e游戏中,
	e游戏菜单,
	e退出,
};
enum class E游戏标志 {
	e载入0,
	e载入1,
	e编译,
};
class C游戏;
class C输入引擎;
class C图形引擎;
class C音频引擎;
class C界面图形控制;
class C程序 {
public:
	static void f初始化(HINSTANCE);
	static void f运行();
	static void f销毁();
	static C游戏 &fg游戏();
	static C输入引擎 &fg输入();
	static C图形引擎 &fg图形();
	static C音频引擎 &fg音频();
	static C界面图形控制 &fg界面图形();
	static std::filesystem::path f计算路径(const std::filesystem::path &目标, const std::filesystem::path & 当前文件 = L"");
	static const std::filesystem::path &fg数据目录();
	static void f输入法开关(bool);
	static int fg渲染间隔();
	static void f切换游戏状态(E游戏状态);
	static void fs游戏标志(int 标志, bool 值 = true);
	static void f日志(int 级别, const std::wstring &);
	static void fs全屏(bool);
	static void fs窗口大小(int, int);
	static std::pair<int, int> fg窗口大小();
	static std::pair<float, float> fg标准窗口大小();
private:
	class C实现;
	static std::unique_ptr<C实现> m实现;
};
}	//namespace 东方山寨