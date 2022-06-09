module;
#include <memory>
#include <chrono>
#include <format>
#include <filesystem>
#include "程序.h"
#include "游戏.h"
#include "程序设置.h"
#include "游戏设置.h"
export module 东方山寨.游戏录像管理;
import 东方山寨.录像_结构;
export import 东方山寨.录像_功能;
import 东方山寨.录像_文件;
import 东方山寨.设置管理;
import 东方山寨.文件系统;
export namespace 东方山寨 {
inline const std::filesystem::path c录像目录 = 文件系统::fg临时目录();
class C游戏录像管理 {	//管理录像文件和正在录制的录像
public:
	static C游戏录像管理 *g这;
	C游戏录像管理() {
		g这 = this;
	}
	C录像机 &f新建录像() {	//在进入游戏前调用
		m录像.f新建录像(C设置管理::fg程序设置(), C设置管理::fg游戏设置());
		return m录像;
	}
	void f保存录像() {	//保存当前录制的录像
		C录像文件::f保存(c录像目录 / f自动录像文件名(), *m录像.m录像);
	}
	static std::wstring f自动录像文件名() {
		auto v现在 = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
		auto v本地 = std::chrono::zoned_time(std::chrono::current_zone(), v现在);
		return std::format(L"自动保存{:%Y%m%d%H%M%S}.录像", v本地);
	}
	C回放机 &f读取录像(const std::wstring &) {
		return m回放;
	}
	C录像机 m录像;	//正在录制的录像
	C回放机 m回放;	//正在回放的录像
};
C游戏录像管理 *C游戏录像管理::g这 = nullptr;
}	//namespace 东方山寨