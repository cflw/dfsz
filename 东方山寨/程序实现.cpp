#include <boost/property_tree/json_parser.hpp>
#include "程序实现.h"
#include "程序常量.h"
#include "边框常量.h"
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
#include "界面音频.h"
#include "图形_背景.h"
import 东方山寨.图形_帧速率;
import 东方山寨.基础_计时器;
import 东方山寨.关卡标识;
import 东方山寨.关卡管理;
import 东方山寨.游戏状态控制;
import 东方山寨.游戏输入管理;
import 东方山寨.设置管理;
import 东方山寨.游戏录像管理;
import 东方山寨.录像_结构;
import 东方山寨.游戏输入_录像;
import 东方山寨.文本管理;
namespace 东方山寨 {
namespace 载入 {
void f载入();
}	//namespace 载入
C程序实现 *C程序实现::g这 = nullptr;
C程序实现::C程序实现(HINSTANCE a实例):
	m实例(a实例),
	m设置(std::make_unique<C设置管理>()),
	m文本(std::make_unique<C文本管理>()),
	m图形(std::make_unique<C图形引擎>()),
	m输入(std::make_unique<C输入引擎>()),
	m音频(std::make_unique<C音频引擎>()),
	m界面(std::make_unique<C界面引擎>()),
	m界面图形(std::make_unique<C界面图形控制>()),
	m界面音频(std::make_unique<C界面音频>()),
	m游戏(std::make_unique<C游戏>()),
	m游戏状态(std::make_unique<C游戏状态控制>(*this)),
	m录像管理(std::make_unique<C游戏录像管理>()),
	m游戏输入(std::make_unique<C游戏输入管理>(*this, *m输入)) {
	g这 = this;
	m游戏->f初始化_图形接口(*m图形);
	m游戏->f初始化_音频接口(*m音频);
}
C程序实现::~C程序实现() {
}
void C程序实现::f运行() {
	//消息循环
	MSG msg = {};
	while (msg.message != WM_QUIT) {	//消息循环
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {	//有消息时的处理,不要修改
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {	//没有消息时的处理
			if (m计时器.f滴答()) {
				f计算();
				//if (m计次器.f滴答()) {
				//	f更新();
				//	f显示();
				//}
				if (!mi显示就绪) {
					f更新();
					mi显示就绪 = true;
				}
				m游戏状态->f切换计算();
			}
		}
	}	//消息循环结束
}
LRESULT WINAPI C程序实现::f窗口过程(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	g这->m输入->m输入w.f窗口消息(msg, wParam, lParam);
	switch (msg) {
	case WM_CHAR:
		g这->m界面->f输入_接收字符((WCHAR)wParam);
		return 0;
	case WM_DESTROY:
		g这->f销毁();
		PostQuitMessage(0);
		return 0;
	}
	//使用默认处理
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//创建窗口
void C程序实现::f创建窗口() {
	//注册窗口
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);			//使用sizeof(WNDCLASSEX)
	wc.style = CS_CLASSDC;					//窗口类型
	wc.lpfnWndProc = f窗口过程;					//窗口过程
	wc.cbClsExtra = 0L;							//扩展:
	wc.cbWndExtra = 0L;							//扩展:
	wc.hInstance = m实例;						//实例句柄
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);	//载入默认图标
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//载入默认光标
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;				//使用窗口颜色
	wc.lpszMenuName = nullptr;							//不需要菜单
	wc.lpszClassName = L"窗口类";					//设置类名
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
	//计算窗口大小
	//RECT v窗口矩形 = {0, 0, 640, 480};
	constexpr int c窗口宽度 = 800;
	constexpr int c窗口高度 = 600;
	constexpr DWORD	c窗口样式 = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	constexpr DWORD	c窗口样式ex = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	const 视窗::S客户区尺寸 v窗口尺寸 = 视窗::S客户区尺寸::fc尺寸样式(c窗口宽度, c窗口高度, c窗口样式, c窗口样式ex);
	//创建窗口
	m窗口 = CreateWindowExW(
		c窗口样式ex,
		L"窗口类",	//窗口类名
		c游戏名称,					//窗口标题
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
	f计算窗口尺寸和缩放();
}
void C程序实现::f初始化() {
	m输入法开关.f初始化(m窗口);
	m输入法开关.f关闭();
	m图形->f初始化(m窗口, m缩放);
	m图形->f初始化_s渲染间隔(m渲染间隔);
	m输入->f初始化(m窗口, m缩放);
	m音频->f初始化();
	m图形->fg图形管理().f初始化_环境(m游戏->fg资源().fg游戏速度());
	载入::f载入();
	//m任务_载入 = std::async(f载入);
	m界面->f初始化0(*m图形, *m输入);
	m计时器.f重置(c帧秒<float>);
	m画帧速率 = std::make_unique<C画帧速率>(m图形->fg二维());
	m日志 = std::make_unique<C日志>(m图形->fg二维());
	fs渲染间隔(1);
	f日志(C日志::e调试, L"启动...............");
	m线程_显示 = std::thread(&C程序实现::f线程_显示, this);
}
void C程序实现::f初始化1() {	//重要资源载入完成时调用
	m游戏->f初始化_在载入结束();
	m界面->f初始化1(*m音频);
	f切换游戏状态(E游戏状态::e主菜单);
	//f日志(C日志::e调试, L"载入完成，按确定键继续");
}
void C程序实现::f初始化2() {	//所有资源载入完成时调用

}
void C程序实现::f销毁() {
	mi显示循环 = false;
	m线程_显示.join();
	m图形->f销毁();
	m画帧速率.reset();
	m音频->f销毁();
}
void C程序实现::f计算() {
	//状态切换
	if (m游戏状态->m状态 == E游戏状态::e载入中 && m标志[(int)E游戏标志::e载入0]) {
		//m任务_资源 = std::async(&C游戏::f初始化_在载入结束, std::ref(m游戏));
		f初始化1();
		f初始化2();
		//↓快速开始游戏，如果要进入标题画面则把下面注释掉
		f快速开始游戏();
		//↓快速进入录像回放
		//f快速回放录像();
	} else if (m游戏状态->m状态 == E游戏状态::e主菜单) {
		//const bool v确定 = m输入.m按键组.f按键((输入::t索引)E按键::e确定).f刚按下();
		//if (v确定) {
		//	f切换游戏状态(E游戏状态::e游戏中);
		//	f日志(C日志::e调试, L"游戏中");
		//}
	}
	//计算
	m游戏->f推进随机数();
	m输入->f更新();
	m音频->f计算();
	m界面->f计算();
	m画帧速率->f计算();
	m界面图形->f计算();
	if (m游戏状态->m状态 == E游戏状态::e游戏中) {
		if (m输入->fg按键组().fg按键((输入::t索引)E按键::e菜单).fi刚按下()) {
			f游戏中弹出菜单(E窗口::e游戏暂停);
		} else {
			try {
				m游戏->f计算();
			} catch (const X回放结束 &e) {
				f游戏中弹出菜单(E窗口::e游戏暂停);
			}
		}
	} else {
		//m图形.fg画背景().f计算();
		m图形->fg图形管理().f游戏外计算();
	}
	m日志->f计算();
}
void C程序实现::f更新() {
	m界面->f更新();
	if (m游戏状态->fi游戏中()) {
		m游戏->f更新();
		mi游戏显示就绪 = true;
	} else {
		m图形->fg图形管理().f游戏外更新();
	}
}
void C程序实现::f显示() {
	m图形->f渲染开始();
	if (m游戏状态->fi游戏中()) {
		if (mi游戏显示就绪) {
			m游戏->f显示();
			mi游戏显示就绪 = false;
		}
	} else {
		//m图形.fg画背景().f显示();
		m图形->fg图形管理().f游戏外显示();
		m图形->fs图形管线(nullptr);
	}
	m界面->f显示();
	m图形->f画黑屏(m游戏状态->m黑屏渐变);
	m画帧速率->f显示();
	m日志->f显示();
	const auto &v鼠标坐标 = m输入->m鼠标->fg坐标();
	m图形->f画十字({v鼠标坐标.x, v鼠标坐标.y});	//调试用
	m图形->f渲染结束();
}
void C程序实现::f线程_显示() {
	while (mi显示循环) {
		if (mi显示就绪) {
			f显示();
			mi显示就绪 = false;
		}
		std::this_thread::sleep_for(std::chrono::seconds(0));
	}
}
void C程序实现::f快速开始游戏() {	//调试用,载入完毕后马上进入游戏
	S游戏设置 &v设置 = C设置管理::fg实例().fg游戏设置();
	v设置.m自机标识 = (int)E自机::e灵梦;
	v设置.m子机标识 = (int)E子机::e灵梦诱导;
	v设置.m火力 = 0;
	v设置.m基础难度 = 5;
	//v设置.fs关卡((int)E关卡::e符卡);
	v设置.fs关卡组((int)E关卡::e测试);
	C游戏::fs游戏设置(v设置);
	auto &v录像 = m录像管理->f新建录像();
	C游戏::fs游戏输入(m游戏输入->fc录像(v录像));
	f切换游戏状态(E游戏状态::e游戏中);
}
void C程序实现::f快速回放录像() {
	C回放机 &v回放 = m录像管理->f回放录像(m录像管理->f打开录像(L"test.zip"));
	C游戏::fs游戏设置(v回放.fg游戏设置());
	C游戏::fs游戏输入(m游戏输入->fc回放(v回放));
	f切换游戏状态(E游戏状态::e游戏中);
}
void C程序实现::f切换游戏状态(E游戏状态 a状态) {
	m游戏状态->f切换游戏状态(a状态);
}
E游戏状态 C程序实现::fg游戏状态() {
	return m游戏状态->m状态;
}
void C程序实现::f游戏中弹出菜单(E窗口 a窗口) {
	m游戏状态->f切换游戏状态(E游戏状态::e游戏菜单, a窗口);
}
void C程序实现::fs渲染间隔(int a) {
	const float v渲染频率 = c计算频率<float> / a;
	m计次器.f重置(a);
	m画帧速率->fs额定速率((int)v渲染频率);
	m界面->fs时钟频率(c计算频率<float>, v渲染频率);
	m渲染间隔 = a;
}
void C程序实现::f输入法开关(bool a) {
	m输入法开关.f开关(a);
}
void C程序实现::f计算窗口尺寸和缩放() {
	const 视窗::S客户区尺寸 v客户区尺寸 = 视窗::S客户区尺寸::fc窗口(m窗口);
	m窗口大小[0] = v客户区尺寸.fg宽();
	m窗口大小[1] = v客户区尺寸.fg高();
	m缩放 = v客户区尺寸.f除以尺寸(c标准尺寸x, c标准尺寸y);
}
void C程序实现::f日志(int a级别, const std::wstring &a文本) {
	m日志->f添加((C日志::E级别)a级别, a文本);
}
void C程序实现::fs全屏(bool a) {
	m图形->m三维->fs全屏(a);
}
void C程序实现::fs窗口大小(int a宽, int a高) {
	m图形->m二维->fg上下文()->SetTarget(nullptr);
	m图形->m三维->fs窗口大小(a宽, a高);
	m图形->m三维->f重置屏幕资源();
	f计算窗口尺寸和缩放();
	m图形->f初始化_二维(m缩放);
	m图形->fs图形资源窗口大小();
	m界面->f初始化0_图形(*m图形);
	m输入->fs缩放(m缩放);
}
}	//namespace 东方山寨