module;
#include <memory>
#include <cflw图形_d2d.h>
#include <cflw时间.h>
export module 东方山寨.图形_帧速率;
namespace 二维 = cflw::图形::d2d;
namespace 时间 = cflw::时间;
export namespace 东方山寨 {
//==============================================================================
// 画帧速率
//==============================================================================
class C画帧速率 {
public:
	std::shared_ptr<二维::C画文本> m画文本;
	时间::C计帧器 m计算, m显示;
	int m额定速率 = 0;
	C画帧速率(二维::C二维 &a二维):
		m画文本(a二维.fc画文本()) {
		m画文本->m矩形 = a二维.fg坐标计算().f矩形_窗口();
		m画文本->fs颜色({1, 1, 1, 1});
		二维::C文本工厂 v文本工厂;
		v文本工厂.f初始化();
		二维::S文本格式参数 v格式;
		v格式.fs字号(10);
		v格式.fs水平对齐(二维::E文本水平对齐::e右);
		v格式.fs垂直对齐(二维::E文本垂直对齐::e下);
		m画文本->m格式 = v文本工厂.fc文本格式(v格式);
		m计算.f重置();
		m显示.f重置();
	}
	void fs额定速率(int a额定) {
		m额定速率 = a额定;
	}
	void f计算() {
		m计算.f计算();
	}
	void f显示() {
		const double v计算帧数 = m计算.fg帧速率();
		const double v显示帧数 = m显示.f计算();
		const double v百分率 = v计算帧数 / m额定速率 * 100;
		std::wstringstream v文本流;
		v文本流 << std::to_wstring(lround(v显示帧数)) << L"fps\n";
		v文本流 << std::to_wstring(lround(v百分率)) << L"%";
		m画文本->f绘制文本(v文本流.str());
	}
};
}	//namespace 东方山寨