#include <future>
#include <cflw时间.h>
#include "常量.h"
#include "游戏.h"
#include "输入.h"
#include "道具.h"
#include "游戏设置.h"
#include "程序设置.h"
#include "取文本.h"
//关卡
#include "关卡.h"
#include "王战.h"
#include "场景.h"
#include "对话.h"
//图形
#include "图形引擎.h"
#include "图形引擎_资源工厂.h"
#include "图形工厂.h"
//判定处理
#include "判定处理_敌机与玩家子弹.h"
#include "判定处理_子弹与玩家炸弹.h"
#include "判定处理_自机与子弹.h"
//子弹头文件
#include "子弹基础.h"
#include "子弹制造机.h"
#include "子弹图形接口.h"
//敌机头文件
#include "敌机基础.h"
#include "敌机制造机.h"
//玩家子弹头文件
#include "玩家子弹基础.h"
#include "玩家炸弹基础.h"
#include "玩家子弹制造机.h"
#include "玩家炸弹扩展.h"
//玩家 自机 子机
#include "玩家.h"
#include "标识.h"
namespace 东方山寨 {
namespace 时间 = cflw::时间;
using t任务 = std::future<void>;
//==============================================================================
// 游戏静态变量
//==============================================================================
std::unique_ptr<C游戏::C资源> C游戏::mp资源;
std::unique_ptr<C游戏::C实现> C游戏::mp实现;
C游戏::C内容 C游戏::g内容;
C游戏::C取资源 C游戏::g资源;
//==============================================================================
// 负载统计
//==============================================================================
class C负载统计 {
public:
	void f开始() {
		++n;
		m秒表.f重置();
	}
	void f重置() {
		n = 0;
		m数组.clear();
	}
	void f统计(const std::wstring &a名称) {
		double v时间 = m秒表.f上次到现在();
		m数组[a名称] = v时间;
	}
	时间::C秒表 m秒表;
	std::map<std::wstring, double> m数组;
	size_t n = 0;
} g负载统计;
//==============================================================================
// 资源
//==============================================================================
class C游戏::C资源 {
public:
	C游戏速度 m游戏速度;
	bool m编译 = false;
	C图形引擎 *mp图形;
	C输入引擎 *mp输入;
	C音频引擎 *mp音频;
	std::map<std::wstring, int> ma名称标识;
	t随机数引擎 m随机数引擎;
	S游戏设置 m游戏设置;
	//属性
	C属性数组<S子弹属性> ma子弹属性;
	C属性数组<S自机属性> ma自机属性;	//需要编译
	C属性数组<S子机属性> ma子机属性;	//需要编译
	C属性数组<S道具属性> ma道具属性;
	C属性数组<S玩家子弹属性> ma玩家子弹属性;
	C属性数组<S敌机属性> ma敌机属性;
	struct S文本数组属性 {
		std::wstring m语言;
		std::wstring m名称;
		std::unique_ptr<C属性数组<std::wstring>> mp数组;
	};
	std::vector<S文本数组属性> ma文本数组;
	//扩展
	C扩展数组<I工厂<C玩家子弹发射器>> ma玩家发射;
	C扩展数组<I画子弹> ma画子弹接口;
	C扩展数组<I工厂<I子机移动>> ma子机移动;
	C扩展数组<I工厂<I动画>> ma动画;
	//
	C资源() {
		g资源.m资源 = this;
		m随机数引擎.seed((unsigned int)time(nullptr));
	}
	//编译
	void f编译() {
		assert(m编译 == false);
		auto &va纹理 = mp图形->fg纹理();
		auto &va顶点 = mp图形->fg顶点矩形();
		auto f编译纹理顶点属性 = [&](auto &a) {
			va纹理.f编译(a.m纹理);
			va顶点.f编译(a.m顶点);
		};
		auto f编译纹理顶点动画属性 = [&](S图片动画属性 &a) {
			ma动画.f编译(a.m动画);
			f编译纹理顶点属性(a);
		};
		for (auto &v子弹属性 : ma子弹属性.ma数据) {
			f编译纹理顶点属性(v子弹属性);
		}
		for (auto &v自机属性 : ma自机属性.ma数据) {
			ma玩家发射.f编译(v自机属性.m发射子弹);
			ma玩家子弹属性.f编译(v自机属性.m子弹属性);
			f编译纹理顶点动画属性(v自机属性);
		}
		for (auto &v子机属性 : ma子机属性.ma数据) {
			ma玩家发射.f编译(v子机属性.m发射);
			ma子机移动.f编译(v子机属性.m移动);
			ma玩家子弹属性.f编译(v子机属性.m子弹属性);
			f编译纹理顶点动画属性(v子机属性);
		}
		for (auto &v玩家子弹属性 : ma玩家子弹属性.ma数据) {
			f编译纹理顶点属性(v玩家子弹属性);
			va纹理.f编译(v玩家子弹属性.m消失纹理);
			va顶点.f编译(v玩家子弹属性.m消失顶点);
		}
		for (auto &v敌机属性 : ma敌机属性.ma数据) {
			f编译纹理顶点动画属性(v敌机属性);
		}
		for (auto &v道具属性 : ma道具属性.ma数据) {
			f编译纹理顶点动画属性(v道具属性);
		}
		m编译 = true;
	}
	t向量2 f输入_方向键() {
		const auto &v方向键 = mp输入->fg方向();
		return t向量2(v方向键.x, v方向键.y);
	}
	const 输入::C按键组 &f输入_按键() {
		return mp输入->fg按键组();
	}
};
//==============================================================================
// 实现
//==============================================================================
class C游戏::C实现 {
public:
	//游戏状态
	C游戏速度 m游戏速度;
	//游戏控制
	C关卡控制 m关卡;
	C王战控制 m王战;
	C场景控制 m场景;
	C对话控制 m对话;
	C子弹制造机::C实现 m子弹制造机实现;
	C道具制造机::C实现 m道具制造机实现;
	C敌机制造机::C实现 m敌机制造机实现;
	C玩家子弹制造机::C实现 m玩家子弹制造机实现;
	//更新
	t任务 m更新图形;
	t任务 m更新敌机;
	t任务 m更新子弹;
	t任务 m更新场景;
	t任务 m更新玩家;
	//游戏变量
	C对象数组<C子弹> ma子弹{c子弹上限};
	C对象数组<C玩家子弹> ma玩家子弹{c玩家子弹上限};
	C对象数组<C道具> ma道具{c道具上限};
	C对象数组<C敌机> ma敌机{c敌机上限};
	C玩家 m玩家;
	C难度 m难度;
	t随机数引擎 m随机数引擎;
	C关卡 *m新关卡 = nullptr;
	//函数
	C实现();
	void f游戏初始化(const S游戏设置 &);
	void f进入关卡(C关卡 &a关卡);
	void f计算();
	void f实现_进入关卡();
	void f更新();
	void f显示();
};
C游戏::C实现::C实现() {
	g内容.m实现 = this;
	//子弹制造机实现
	m子弹制造机实现.f初始化_环境(m游戏速度);
	m子弹制造机实现.f初始化_数组(ma子弹);
	m子弹制造机实现.f初始化_资源(mp资源->ma子弹属性, mp资源->ma画子弹接口);
	//敌机制造机实现
	m敌机制造机实现.f初始化_环境(m游戏速度);
	m敌机制造机实现.f初始化_数组(ma敌机);
	m敌机制造机实现.f初始化_资源(mp资源->ma敌机属性);
	//道具制造机实现
	m道具制造机实现.f初始化_环境(m游戏速度);
	m道具制造机实现.f初始化_数组(ma道具);
	m道具制造机实现.f初始化_资源(mp资源->ma道具属性);
	//玩家子弹制造机实现
	m玩家子弹制造机实现.f初始化_环境(m游戏速度);
	m玩家子弹制造机实现.f初始化_数组(ma玩家子弹);
	//玩家
	m玩家.f初始化_环境(m游戏速度);
	//关卡
	m关卡.f初始化_环境(m场景, m对话);
	m王战.f初始化_环境(m关卡);
	m对话.f初始化_环境(m关卡);
	m场景.f初始化_图形(mp资源->mp图形->fg画三维());
}
void C游戏::C实现::f游戏初始化(const S游戏设置 &a设置) {
	m玩家.fs自机(a设置.m自机标识);
	m玩家.fs子机(a设置.m子机标识);
	m玩家.fs炸弹(a设置.m炸弹标识);
	m玩家.f游戏初始化(a设置);
	m难度.m基础难度 = a设置.m基础难度;
	m难度.m增加难度 = a设置.m增加难度;
}
void C游戏::C实现::f进入关卡(C关卡 &a关卡) {
	m新关卡 = &a关卡;
}
void C游戏::C实现::f计算() {
	//初始化
	g负载统计.f开始();
	m随机数引擎.discard(100);
	//更新对象数组
	std::vector<std::future<void>> va更新线程;
	const auto f变化则更新 = [&va更新线程](auto &a容器) {
		if (a容器.fi变化()) {
			auto f = [&a容器]() {
				a容器.f更新();
			};
			va更新线程.emplace_back(std::async(f));
		}
	};
	//关卡
	if (m新关卡 != m关卡.m关卡) {
		f实现_进入关卡();
	}
	m关卡.f计算();
	m王战.f计算();
	if (m对话.fi对话中()) {
		m对话.f输入按键(mp资源->f输入_按键());
		m对话.f计算();
	}
	//玩家
	m玩家.f输入按键(mp资源->f输入_方向键(), mp资源->f输入_按键());
	m玩家.f计算();
	g负载统计.f统计(L"综合");
	//计算玩家子弹
	ma玩家子弹.fe使用_并行([](C玩家子弹 &a玩家子弹) {
		a玩家子弹.f接口_计算();
		if (a玩家子弹.f接口_在窗口外()) {
			a玩家子弹.f对象_销毁();
			return;
		} else if (a玩家子弹.m标志[C玩家子弹::e命中可销毁]) {
			a玩家子弹.f对象_销毁();
			return;
		}
	});
	g负载统计.f统计(L"玩家子弹");
	//计算敌机
	ma敌机.fe使用_并行([&](C敌机 &a当前敌机) {
		if (!a当前敌机.m标志[C敌机::e无动作]) {
			a当前敌机.f事件_执行();
		}
		if (!a当前敌机.f对象_i使用()) {	//调用了f动作_死亡会置于不使用状态
			return;
		}
		a当前敌机.f计算();
		if (a当前敌机.fi在窗口外()) {
			a当前敌机.f对象_销毁();
			return;
		}
		//敌机与玩家子弹相交判定
		C敌机与玩家子弹判定 v判定0;
		v判定0.f绑定敌机(a当前敌机);
		ma玩家子弹.fe使用_并行([&](C玩家子弹 &a玩家子弹) {
			C敌机与玩家子弹判定 v判定1 = v判定0;
			v判定1.f绑定玩家子弹(a玩家子弹);
			a玩家子弹.f接口_敌机判定(v判定1);
		});
		if (a当前敌机.fi死亡() && !a当前敌机.fi王()) {
			a当前敌机.f事件_击破();
			a当前敌机.f对象_销毁();
			return;
		}
	});
	f变化则更新(ma敌机);
	g负载统计.f统计(L"敌机");
	//道具
	const t圆形 v自机吸道具点 = m玩家.m自机.fg吸道具点();
	const t圆形 v自机吃道具点 = m玩家.m自机.fg吃道具点();
	ma道具.fe使用_并行([&](C道具 &a当前道具) {
		const t圆形 v道具判定点 = a当前道具.fg判定点();
		if (!a当前道具.fw跟随()) {
			if (数学::f圆形相交判定(v道具判定点, v自机吸道具点)) {
				a当前道具.fs跟随(&m玩家, 4.f);
			}
		}
		a当前道具.f计算();
		if (a当前道具.fi在窗口外()) {
			a当前道具.f对象_销毁();
			return;
		}
		if (数学::f圆形相交判定(v道具判定点, v自机吃道具点)) {
			a当前道具.f效果(m玩家);
			a当前道具.f对象_销毁();
			return;
		}
	});
	g负载统计.f统计(L"道具");
	//计算子弹
	C自机与子弹判定 v自机判定0;
	v自机判定0.f绑定自机(&m玩家.m自机);
	ma子弹.fe使用_并行([&](C子弹 &a当前子弹) {
		a当前子弹.f事件_执行();
		a当前子弹.f接口_计算();
		if (!a当前子弹.f对象_i使用()) {
			return;
		}
		if (a当前子弹.f接口_i在窗口外()) {
			a当前子弹.f对象_销毁();
			return;
		}
		//与炸弹相交判定
		if (!a当前子弹.f接口_i停止炸弹判定()) {
			C子弹与玩家炸弹判定 v炸弹判定;
			C道具制造机 v产生道具(m道具制造机实现);
			v炸弹判定.f绑定道具(&v产生道具);
			v炸弹判定.f绑定子弹(&a当前子弹);
			for (const auto &v当前炸弹 : ma玩家子弹.ma对象) {
				if (v当前炸弹->f对象_i使用() && v当前炸弹->f基础_i炸弹()) {
					v炸弹判定.f绑定炸弹((C玩家炸弹*)v当前炸弹.get());
					v炸弹判定.f计算判定();
					if (a当前子弹.f接口_i停止炸弹判定()) {
						break;
					}
				}
			}
		}
		if (!a当前子弹.f对象_i使用()) {
			return;
		}
		//与自机相交判定
		C自机与子弹判定 v自机判定1 = v自机判定0;
		a当前子弹.f接口_自机判定(v自机判定1);
	});
	f变化则更新(ma子弹);
	f变化则更新(ma道具);
	f变化则更新(ma玩家子弹);
	g负载统计.f统计(L"子弹");
	//图形
	auto &va图形 = fg图形().fg图形数组();
	m场景.f计算();
	va图形.fe使用_并行([](I图形 &a当前图形) {
		a当前图形.f接口_计算();
		if (a当前图形.f接口_i可销毁()) {
			a当前图形.f对象_销毁();
		}
	});
	f变化则更新(va图形);
	g负载统计.f统计(L"图形");
	//合并线程
	for (auto &v线程 : va更新线程) {
		v线程.wait();
	}
	g负载统计.f统计(L"更新数组");
}
void C游戏::C实现::f实现_进入关卡() {
	m随机数引擎.seed((unsigned int)time(nullptr));
	m玩家.f关卡初始化();
	ma子弹.f清空();
	m关卡.f结束();
	m关卡.f初始化(*m新关卡);
	m游戏速度.fs速度(1);
}
void C游戏::C实现::f更新() {
	const auto f简单更新 = [](t任务 &a任务, auto &a对象, auto af更新) {
		a任务 = std::async([&a对象, af更新]() {
			(a对象.*af更新)();
		});
	};
	const auto f并行更新 = [](t任务 &a任务, auto &a容器, auto af更新) {
		a任务 = std::async([&a容器, af更新]() {
			a容器.fe使用_并行([=](auto &a当前) {
				(a当前.*af更新)();
			});
		});
	};
	auto &va图形 = fg图形().fg图形数组();
	f并行更新(m更新图形, va图形, &I图形::f接口_更新);
	f并行更新(m更新敌机, ma敌机, &C敌机::f更新);
	f并行更新(m更新子弹, ma子弹, &C子弹::f接口_更新);
	f简单更新(m更新场景, m场景, &C场景控制::f更新);
	f简单更新(m更新玩家, m玩家, &C玩家::f更新);
}
void C游戏::C实现::f显示() {
	//各种初始化
	//v资源->v图形->v三维->f设置深度模板(v资源->v图形->v渲染状态.v深度模板.v正常深度, 1);
	C图形引擎 *const v图形引擎 = mp资源->mp图形;
	//图层
	std::map<int, std::vector<const I图形 *>> va图层;
	auto &va图形 = fg图形().fg图形数组();
	va图形.fe使用([&](I图形 &a当前图形) {
		va图层[a当前图形.m图层].push_back(&a当前图形);
	});
	auto f显示图形 = [&va图层](int p层) {
		for (const auto &v图形 : va图层[p层]) {
			v图形->f接口_显示();
		}
	};
	m更新图形.wait();
	f显示图形((int)E图层::e底层);
	m更新场景.wait();
	m场景.f显示();
	//敌机
	m更新敌机.wait();
	ma敌机.fe使用([](C敌机 &a当前敌机) {
		a当前敌机.f显示();
	});
	f显示图形((int)E图层::e敌机);
	//玩家
	m更新玩家.wait();
	m玩家.f显示();
	ma玩家子弹.fe使用([](C玩家子弹 &a玩家子弹) {
		a玩家子弹.f接口_显示();
	});
	f显示图形((int)E图层::e玩家);
	//道具
	ma道具.fe使用([](C道具 &a当前道具) {
		a当前道具.f显示();
	});
	f显示图形((int)E图层::e道具);
	f显示图形((int)E图层::e图形);
	//子弹
	std::vector<const C子弹 *> v子弹数组;
	m更新子弹.wait();
	ma子弹.fe使用([&](C子弹 &a当前子弹) {
		if (a当前子弹.f接口_可显示()) {
			v子弹数组.push_back(&a当前子弹);
		}
	});
	std::sort(v子弹数组.begin(), v子弹数组.end(), [](const C子弹 *a0, const C子弹 *a1)->bool {
		return a0->m显示编号 < a1->m显示编号;
	});
	for (const auto &v当前子弹 : v子弹数组) {
		v图形引擎->fs图形管线(v当前子弹->m绘制);
		v当前子弹->f接口_显示();
	}
	f显示图形((int)E图层::e子弹);
	//三维结束
	v图形引擎->fs图形管线(nullptr);
	//边框
	f显示图形((int)E图层::e抬显);
	v图形引擎->f画边框();
	if constexpr (c调试_调试信息) {
		std::wostringstream v调试信息;
		v调试信息 << L"自机坐标: x=" << m玩家.m自机.m坐标.x << L" y=" << m玩家.m自机.m坐标.y << L"\n";
		v调试信息 << L"子弹:" << ma子弹.fg计数() << L"\n";
		v调试信息 << L"玩家子弹:" << ma玩家子弹.fg计数() << L"\n";
		v调试信息 << L"敌机:" << ma敌机.fg计数() << L"\n";
		v调试信息 << L"道具:" << ma道具.fg计数() << L"\n";
		v调试信息 << L"图形:" << va图形.fg计数() << L"\n";
		v调试信息 << L"关卡经过时间:" << m关卡.fg经过时间() << L"\n";
		v调试信息 << L"\n负载:\n";
		for (const auto &[v名称, v时间] : g负载统计.m数组) {
			v调试信息 << v名称 << L":" << (v时间 / g负载统计.n * c计算频率) << L"\n";
		}
		v图形引擎->f画调试信息(v调试信息.str());
	}
	g负载统计.f重置();
	f显示图形((int)E图层::e顶层);
}
//==============================================================================
// 游戏
//==============================================================================
C游戏::C游戏() {}
C游戏::~C游戏() {}
C游戏::C资源 &C游戏::fg内部资源() {
	if (mp资源 == nullptr) {
		mp资源 = std::make_unique<C资源>();
	}
	return *mp资源;
}
void C游戏::f初始化_图形接口(C图形引擎 &a图形) {
	fg内部资源().mp图形 = &a图形;
}
void C游戏::f初始化_输入接口(C输入引擎 &a输入) {
	fg内部资源().mp输入 = &a输入;
}
void C游戏::f初始化_音频接口(C音频引擎 &a音频) {
	fg内部资源().mp音频 = &a音频;
}
void C游戏::f资源初始化() {
	if (mp实现 == nullptr) {
		mp实现 = std::make_unique<C实现>();
		mp资源->f编译();
	}
}
void C游戏::f游戏初始化() {
	mp实现->f游戏初始化(mp资源->m游戏设置);
}
void C游戏::f进入关卡(C关卡 &a关卡) {
	mp实现->f进入关卡(a关卡);
}
void C游戏::f计算() {
	mp实现->f计算();
}
void C游戏::f更新() {
	mp实现->f更新();
}
void C游戏::f显示() const {
	mp实现->f显示();
}
C游戏::C内容 &C游戏::fg内容() {
	return g内容;
}
C游戏::C取资源 &C游戏::fg资源() {
	return g资源;
}
S游戏设置 &C游戏::fg设置() {
	return mp资源->m游戏设置;
}
C图形引擎 &C游戏::fg图形() {
	return *mp资源->mp图形;
}
C音频引擎 &C游戏::fg音频() {
	return *mp资源->mp音频;
}
//==============================================================================
// 控制
//==============================================================================
//游戏变量
C游戏速度 &C游戏::C内容::fg游戏速度() const {
	return m实现->m游戏速度;
}
C对象数组<C子弹> &C游戏::C内容::fg子弹数组() const {
	return m实现->ma子弹;
}
C对象数组<C敌机> &C游戏::C内容::fg敌机数组() const {
	return m实现->ma敌机;
}
t随机数引擎 &C游戏::C内容::fg随机数引擎() const {
	return m实现->m随机数引擎;
}
C自机 &C游戏::C内容::fg自机() const {
	return m实现->m玩家.m自机;
}
C关卡控制 &C游戏::C内容::fg关卡控制() const {
	return m实现->m关卡;
}
C王战控制 &C游戏::C内容::fg王战控制() const {
	return m实现->m王战;
}
C难度 &C游戏::C内容::fg难度() const {
	return m实现->m难度;
}
C玩家 &C游戏::C内容::fg玩家() const {
	return m实现->m玩家;
}
//工厂
C子弹制造机 C游戏::C内容::f工厂_子弹() const {
	return C子弹制造机{m实现->m子弹制造机实现};
}
C敌机制造机 C游戏::C内容::f工厂_敌机() const {
	return C敌机制造机{m实现->m敌机制造机实现};
}
C玩家子弹制造机 C游戏::C内容::f工厂_玩家子弹() const {
	return C玩家子弹制造机{m实现->m玩家子弹制造机实现};
}
C道具制造机 C游戏::C内容::f工厂_道具() const {
	return C道具制造机{m实现->m道具制造机实现};
}
std::shared_ptr<C子弹制造机> C游戏::C内容::f工厂_子弹p() const {
	return std::make_shared<C子弹制造机>(m实现->m子弹制造机实现);
}
std::shared_ptr<C敌机制造机> C游戏::C内容::f工厂_敌机p() const {
	return std::make_shared<C敌机制造机>(m实现->m敌机制造机实现);
}
std::shared_ptr<C玩家子弹制造机> C游戏::C内容::f工厂_玩家子弹p() const {
	return std::make_shared<C玩家子弹制造机>(m实现->m玩家子弹制造机实现);
}
std::shared_ptr<C道具制造机> C游戏::C内容::f工厂_道具p() const {
	return std::make_shared<C道具制造机>(m实现->m道具制造机实现);
}
t随机数引擎 C游戏::C内容::f工厂_随机数引擎(int a推进) const {
	auto v引擎 = m实现->m随机数引擎;
	v引擎.discard(a推进);
	return v引擎;
}
//游戏中
void C游戏::C内容::f游戏_全屏清弹(const t向量2 &a坐标, float a半径, bool a道具) {
	class C全屏清弹 {
	public:
		C全屏清弹() {
			m子弹制造机.m参数.m发射环境 = &m发射环境;
		}
		void f全屏清弹(const t向量2 &a坐标, float a半径, bool a道具) {
			m子弹制造机.m参数.m坐标 = a坐标;
			m子弹制造机.f产生炸弹<玩家炸弹::C全屏清弹>(a半径, a道具);
		}
		C玩家子弹制造机 m子弹制造机 = C游戏::fg内容().f工厂_玩家子弹();
		C玩家发射环境 m发射环境{C游戏::fg内容().fg玩家()};
	};
	static C全屏清弹 v全屏清弹;
	v全屏清弹.f全屏清弹(a坐标, a半径, a道具);
}
void C游戏::C内容::f游戏_进入关卡(C关卡 &a关卡) {
	mp实现->f进入关卡(a关卡);
}
//==============================================================================
// 取资源
//==============================================================================
C游戏速度 &C游戏::C取资源::fg游戏速度() const {
	return m资源->m游戏速度;
}
C属性数组<std::wstring> &C游戏::C取资源::f新文本数组(const std::wstring &a名称, const std::wstring &a语言) {
	//语言和名称都不匹配才新建
	for (auto &v文本数组 : m资源->ma文本数组) {
		if (v文本数组.m语言 == a语言 && v文本数组.m名称 == a名称) {
			return *v文本数组.mp数组;
		}
	}
	C游戏::C资源::S文本数组属性 v文本数组{a语言, a名称, std::make_unique<C属性数组<std::wstring>>()};
	m资源->ma文本数组.push_back(std::move(v文本数组));
	return *m资源->ma文本数组.back().mp数组;
}
const C属性数组<std::wstring> &C游戏::C取资源::f找文本数组(const std::wstring &a名称, const std::wstring &a语言) const {
	//先找名称再找语言，如果语言不存在则从匹配的名称中随便选一个
	C属性数组<std::wstring> *v找 = nullptr;
	for (auto &v文本数组 : m资源->ma文本数组) {
		if (v文本数组.m名称 == a名称) {
			if (v文本数组.m语言 == a语言) {
				return *v文本数组.mp数组;
			} else {
				v找 = v文本数组.mp数组.get();
			}
		}
	}
	return *v找;
}
C取文本 C游戏::C取资源::f取文本数组(const std::wstring &a名称, const std::wstring &a语言) const {
	return C取文本(f找文本数组(a名称, a语言), a名称);
}
C取文本 C游戏::C取资源::fg普通文本() const {
	return f取文本数组(L"文本", C程序设置::fg这().fg文本语言());
}
C取文本 C游戏::C取资源::fg界面文本() const {
	return f取文本数组(L"用户界面", C程序设置::fg这().fg界面语言());
}
C属性数组<S子弹属性> &C游戏::C取资源::fg子弹属性() const {
	return m资源->ma子弹属性;
}
C属性数组<S自机属性> &C游戏::C取资源::fg自机属性() const {
	return m资源->ma自机属性;
}
C属性数组<S子机属性> &C游戏::C取资源::fg子机属性() const {
	return m资源->ma子机属性;
}
C属性数组<S道具属性> &C游戏::C取资源::fg道具属性() const {
	return m资源->ma道具属性;
}
C属性数组<S玩家子弹属性> &C游戏::C取资源::fg玩家子弹属性() const {
	return m资源->ma玩家子弹属性;
}
C属性数组<S敌机属性> &C游戏::C取资源::fg敌机属性() const {
	return m资源->ma敌机属性;
}
C扩展数组<I工厂<C玩家子弹发射器>> &C游戏::C取资源::fg玩家发射() const {
	return m资源->ma玩家发射;
}
C扩展数组<I画子弹> &C游戏::C取资源::fg画子弹() const {
	return m资源->ma画子弹接口;
}
C扩展数组<I工厂<I子机移动>> &C游戏::C取资源::fg子机移动() const {
	return m资源->ma子机移动;
}
C扩展数组<I工厂<I动画>> &C游戏::C取资源::fg动画() const {
	return m资源->ma动画;
}
C纹理工厂 &C游戏::C取资源::fg纹理工厂() const {
	return m资源->mp图形->fg纹理工厂();
}
C顶点工厂 &C游戏::C取资源::fg顶点工厂() const {
	return m资源->mp图形->fg顶点工厂();
}
std::map<std::wstring, int> &C游戏::C取资源::fg名称标识() const {
	return m资源->ma名称标识;
}
int C游戏::C取资源::fc随机标识() const {
	return 计算::fc随机标识();
}
int C游戏::C取资源::fg标识(const std::wstring &a) const {
	auto &v名称标识 = fg名称标识();
	return v名称标识.at(a);
}
C对象数组<I图形> &C游戏::C取资源::fg图形数组() const {
	return fg图形().fg图形数组();
}
C图形工厂 C游戏::C取资源::f工厂_图形() {
	return fg图形().f工厂_图形();
}
std::shared_ptr<C图形工厂> C游戏::C取资源::f工厂_图形p() {
	return fg图形().f工厂_图形p();
}
t随机数引擎 C游戏::C取资源::f工厂_随机数引擎(int a推进) const {
	auto v引擎 = m资源->m随机数引擎;
	v引擎.discard(a推进);
	return v引擎;
}

}	//namespace 东方山寨