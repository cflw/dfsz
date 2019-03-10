#include <future>
#include <Windows.h>
#include <cflw图形_d3d11.h>
#include <cflw图形_d2d.h>
#include <cflw时间.h>
#include <cflw视窗.h>
#include "常量.h"
#include "程序.h"
#include "界面引擎.h"
#include "图形引擎.h"
#include "音频引擎.h"
#include "输入.h"
#include "游戏.h"
#include "关卡.h"
#include "日志.h"
#include "游戏设置.h"
#include "图形管理.h"
#include "界面图形.h"
namespace 东方山寨 {
namespace 时间 = cflw::时间;
namespace 视窗 = cflw::视窗;
void f载入();
//==============================================================================
// 画帧速率
//==============================================================================
class C画帧速率 {
public:
	std::shared_ptr<二维::C画文本> m画文本;
	时间::C计帧器 m计帧器;
	int m额定速率;
	C画帧速率(二维::C二维 &a二维):
		m画文本(a二维.fc画文本()) {
		m画文本->m矩形 = a二维.fg坐标计算().f矩形_窗口();
		m画文本->fs颜色({1,1,1,1});
		二维::C文本工厂 v文本工厂;
		v文本工厂.f初始化();
		二维::S文本格式参数 v格式;
		v格式.fs字号(10);
		v格式.fs水平对齐(二维::E文本水平对齐::e右);
		v格式.fs垂直对齐(二维::E文本垂直对齐::e下);
		m画文本->m格式 = v文本工厂.fc文本格式(v格式);
		m计帧器.f重置();
	}
	void fs额定速率(int p额定) {
		m额定速率 = p额定;
	}
	void f显示() {
		const double v帧速率0 = m计帧器.f计算();	//转整数，四舍五入
		const double v百分率 = v帧速率0 / m额定速率 * 100;
		std::wstring v文本0 = std::to_wstring(lround(v帧速率0));
		v文本0 += L"fps\n(";
		v文本0 += std::to_wstring(lround(v百分率));
		v文本0 += L"%)";
		m画文本->f绘制文本(v文本0);
	}
};
//==============================================================================
// 程序实现
//==============================================================================
class C程序::C实现 {
public:
	HINSTANCE m实例;
	HWND m窗口;
	int m窗口大小[2];
	float m缩放 = 0;
	时间::C计时器 m计时器;
	工具::C计次器 m计次器;
	C图形引擎 m图形;
	C输入引擎 m输入;
	C音频引擎 m音频;
	C界面引擎 m界面;
	C界面图形控制 m界面图形;
	C游戏 m游戏;
	std::unique_ptr<C画帧速率> m画帧速率;
	std::unique_ptr<C日志> m日志;
	视窗::C输入法开关 m输入法开关;
	int m渲染间隔 = 1;
	E游戏状态 m状态 = E游戏状态::e载入中;
	E游戏状态 m新状态 = E游戏状态::e无;
	t标志 m标志;
	//异步任务
	std::future<void> m任务_载入;
	std::future<void> m任务_资源;
public:
	C实现(HINSTANCE a实例): m实例{a实例} {
		m游戏.f初始化_图形接口(m图形);
		m游戏.f初始化_输入接口(m输入);
		m游戏.f初始化_音频接口(m音频);
	}
	void f运行() {
		//消息循环
		MSG msg = {};
		while (msg.message != WM_QUIT) {	//消息循环
			if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//有消息时的处理,不要修改
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			} else {	//没有消息时的处理
				if (m计时器.f滴答()) {
					f计算();
					if (m计次器.f滴答()) {
						f更新();
						f显示();
					}
				}
				f切换计算();
			}
		}	//消息循环结束
	}
	static LRESULT WINAPI f窗口过程(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		m实现->m输入.m输入w.f窗口消息(msg, wParam, lParam);
		switch(msg) {
		case WM_DESTROY:
			m实现->f销毁();
			PostQuitMessage(0);
			return 0;
		}
		//使用默认处理
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	//创建窗口
	void f创建窗口() {
		//注册窗口
		WNDCLASSEX wc;
		wc.cbSize			= sizeof(WNDCLASSEX);			//使用sizeof(WNDCLASSEX)
		wc.style			= CS_CLASSDC;					//窗口类型
		wc.lpfnWndProc		= f窗口过程;					//窗口过程
		wc.cbClsExtra		= 0L;							//扩展:
		wc.cbWndExtra		= 0L;							//扩展:
		wc.hInstance		= m实例;						//实例句柄
		wc.hIcon			= LoadIcon(nullptr, IDI_WINLOGO);	//载入默认图标
		wc.hCursor			= LoadCursor(nullptr, IDC_ARROW);	//载入默认光标
		wc.hbrBackground	= (HBRUSH)COLOR_WINDOW;				//使用窗口颜色
		wc.lpszMenuName		= nullptr;							//不需要菜单
		wc.lpszClassName	= L"窗口类";					//设置类名
		wc.hIconSm			= nullptr;
		RegisterClassEx(&wc);
		//计算窗口大小
		//RECT v窗口矩形 = {0, 0, 640, 480};
		const DWORD	c窗口样式 = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
		const DWORD	c窗口样式ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		const 视窗::S客户区尺寸 v窗口尺寸 = 视窗::S客户区尺寸::fc尺寸样式(800, 600, c窗口样式, c窗口样式ex);
		//创建窗口
		m窗口 = CreateWindowExW(
			c窗口样式ex,
			L"窗口类",	//窗口类名
			c窗口标题,					//窗口标题
			c窗口样式,					//窗口样式
			CW_USEDEFAULT, CW_USEDEFAULT,	//坐标
			v窗口尺寸.fg宽(), v窗口尺寸.fg高(),		//窗口尺寸
			GetDesktopWindow(),				//窗口句柄参数
			nullptr,							//菜单句柄
			wc.hInstance,					//实例句柄
			nullptr);							//参数
		//显示窗口
		ShowWindow(m窗口, SW_SHOWDEFAULT);
		UpdateWindow(m窗口);
		//取窗口客户区大小
		const 视窗::S客户区尺寸 v客户区尺寸 = 视窗::S客户区尺寸::fc窗口(m窗口);
		m窗口大小[0] = v客户区尺寸.fg宽();
		m窗口大小[1] = v客户区尺寸.fg高();
		m缩放 = v客户区尺寸.f除以尺寸(c标准尺寸x, c标准尺寸y);
	}
	void f初始化() {
		m输入法开关.f初始化(m窗口);
		m输入法开关.f关闭();
		m图形.f初始化(m窗口, m缩放);
		m图形.f初始化_s渲染间隔(m渲染间隔);
		m输入.f初始化(m窗口, m缩放);
		m音频.f初始化();
		m界面.f初始化(m图形.fg二维(), m输入);
		m图形.fg图形管理().f初始化_环境(m游戏.fg资源().fg游戏速度());
		//m任务_载入 = std::async(f载入);
		f载入();
		m计时器.f重置(c帧秒);
		m画帧速率 = std::make_unique<C画帧速率>(m图形.fg二维());
		m日志 = std::make_unique<C日志>(m图形.fg二维());
		fs渲染间隔(4);
		f日志(C日志::e调试, L"启动...............");
	}
	void f销毁() {
		m图形.f销毁();
		m画帧速率.reset();
		m音频.f销毁();
	}
	void f计算() {
		//状态切换
		if (m状态 == E游戏状态::e载入中 && m标志[(int)E游戏标志::e载入0]) {
			//m任务_资源 = std::async(&C游戏::f资源初始化, std::ref(m游戏));
			m游戏.f资源初始化();
			f切换游戏状态(E游戏状态::e主菜单);
			f日志(C日志::e调试, L"载入完成，按确定键继续");
			//↓快速开始游戏，如果要进入标题画面则把下面注释掉
			//S游戏设置 &v设置 = C游戏::fg设置();
			//v设置.m自机标识 = (int)E自机::e魔理沙;
			//v设置.m子机标识 = (int)E子机::e魔理沙贯穿;
			//v设置.m火力 = 4;
			//f切换游戏状态(E游戏状态::e游戏中);
		} else if (m状态 == E游戏状态::e主菜单) {
			const bool v确定 = m输入.m按键组.f按键((输入::t索引)E按键::e确定).f刚按下();
			if (v确定) {
				f切换游戏状态(E游戏状态::e游戏中);
				f日志(C日志::e调试, L"游戏中");
			}
		}
		//计算
		m输入.f更新();
		m音频.f计算();
		m界面.f计算();
		m界面图形.f计算();
		if (m状态 == E游戏状态::e游戏中) {
			m游戏.f计算();
		} else {
			m图形.fg图形管理().f游戏外计算();
		}
		m日志->f计算();
	}
	void f更新() {
		m界面.f更新();
		if (m状态 == E游戏状态::e游戏中) {
			m游戏.f更新();
		} else {
			m图形.fg图形管理().f游戏外更新();
		}
	}
	void f显示() {
		m图形.f渲染开始();
		if (m状态 == E游戏状态::e游戏中 || m状态 == E游戏状态::e游戏菜单) {
			m游戏.f显示();
		} else {
			m图形.fg图形管理().f游戏外显示();
			m图形.fs图形管线(nullptr);
		}
		m界面.f显示();
		m画帧速率->f显示();
		m日志->f显示();
		const auto &v鼠标坐标 = m输入.m鼠标->f坐标();
		m图形.f画十字({v鼠标坐标.x, v鼠标坐标.y});
		m图形.f渲染结束();
	}
	void f切换计算() {
		if (m新状态 != E游戏状态::e无) {
			switch (m新状态) {
			case E游戏状态::e主菜单:
				m界面.f切换窗口(E窗口::e主菜单);
				break;
			case E游戏状态::e游戏中:
				//m任务_资源.wait();
				m游戏.f游戏初始化();
				m游戏.f进入关卡(C关卡::fg注册关卡(L"东方月亮船1"));
				m界面.f关闭窗口();
				break;
			case E游戏状态::e退出:
				SendMessageW(m窗口, WM_CLOSE, 0, 0);
				break;
			}
			m状态 = m新状态;
			m新状态 = E游戏状态::e无;
		}
	}
	void fs渲染间隔(int a) {
		const float v渲染频率 = c计算频率 / a;
		m计次器.f重置(a);
		m画帧速率->fs额定速率(v渲染频率);
		m界面.fs时钟频率(c计算频率, v渲染频率);
		m渲染间隔 = a;
	}
	void f切换游戏状态(E游戏状态 a) {
		m新状态 = a;
	}
	void f输入法开关(bool a) {
		m输入法开关.f开关(a);
	}
};
//==============================================================================
// 程序
//==============================================================================
std::unique_ptr<C程序::C实现> C程序::m实现;
void C程序::f初始化(HINSTANCE p) {
	m实现 = std::make_unique<C实现>(p);
	m实现->f创建窗口();
	m实现->f初始化();
}
void C程序::f运行() {
	m实现->f运行();
}
void C程序::f销毁() {
	m实现.reset();
}
C游戏 &C程序::fg游戏() {
	return m实现->m游戏;
}
C输入引擎 &C程序::fg输入() {
	return m实现->m输入;
}
C图形引擎 &C程序::fg图形() {
	return m实现->m图形;
}
C音频引擎 &C程序::fg音频() {
	return m实现->m音频;
}
C界面图形控制 &C程序::fg界面图形() {
	return m实现->m界面图形;
}
std::filesystem::path C程序::f计算路径(const std::filesystem::path &a目标路径, const std::filesystem::path &a当前文件) {
	using std::filesystem::path;
	const path v数据路径 = path(a目标路径).make_preferred();
	const std::wstring v数据字符串 = v数据路径.native();
	if (a当前文件.empty()) {
		return (std::filesystem::current_path() / v数据路径).lexically_normal();
	} else if (const size_t v位置 = v数据字符串.find(std::wstring(L"~") + path::preferred_separator); v位置 == 0) {
		return (fg数据目录() / v数据字符串.substr(2)).lexically_normal();
	} else {
		const path v当前目录 = a当前文件.parent_path();
		return (v当前目录 / v数据路径).lexically_normal();
	}
}
const std::filesystem::path &C程序::fg数据目录() {
	using std::filesystem::path;
	static const path v数据目录 = []()->path {
		const path v当前目录 = std::filesystem::current_path();
		const path v上级目录 = v当前目录.parent_path();
		if (const path v目录名 = v上级目录.filename(); v目录名 == L"~") {
			return v上级目录;
		}
		return v当前目录 / L"~";
	}();
	assert(std::filesystem::exists(v数据目录));
	return v数据目录;
}
void C程序::f输入法开关(bool p) {
	m实现->f输入法开关(p);
}
int C程序::fg渲染间隔() {
	return m实现->m渲染间隔;
}
void C程序::f切换游戏状态(E游戏状态 a状态) {
	m实现->f切换游戏状态(a状态);
}
void C程序::fs游戏标志(int a标志, bool a值) {
	m实现->m标志[a标志] = a值;
}
void C程序::f日志(int a级别, const std::wstring &a文本) {
	m实现->m日志->f添加((C日志::E级别)a级别, a文本);
}
}	//namespace 东方山寨
//==============================================================================
// 主函数
//==============================================================================
using 东方山寨::C程序;
int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, int) {
	C程序::f初始化(hInst);
	C程序::f运行();
	C程序::f销毁();
}