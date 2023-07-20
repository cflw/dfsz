module;
#include <cflw视窗.h>
#include "程序.h"
#include "界面包含.h"
export module 东方山寨.界面_选项.图形设置;
export import 东方山寨.界面_选项.选项列表;
import 用户界面.控件;
namespace 视窗 = cflw::视窗;
export namespace 东方山寨 {
struct S分辨率 {
	int m宽, m高;
	int m比例宽, m比例高;
	std::wstring fg显示名称() const;	//宽x高(宽:高)
};
class W图形设置 : public W选项列表 {
public:
	enum E标识 {
		e分辨率,
	};
	W图形设置() = default;
	void f响应_载入() override;
	void f事件_窗口值变化(用户界面::W窗口 &a窗口, const int &a前, int &a后) override;
	void f事件_确定() override;
	void f事件_取消() override;
	void f事件_应用() override;
	const S分辨率 &fg分辨率() const;	//当前选择的分辨率
	std::map<int, S分辨率> ma分辨率;	//载入的分辨率
	int m分辨率 = 0;	//当前选择的分辨率
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
std::wstring S分辨率::fg显示名称() const {
	return std::format(L"{}x{}({}:{})", m宽, m高, m比例宽, m比例高);
}
void W图形设置::f响应_载入() {
	static const S分辨率 ca分辨率[] = {	//所有分辨率
		//4:3
		S分辨率(800, 600, 4, 3),
		S分辨率(960, 720, 4, 3),
		S分辨率(1024, 768, 4, 3),
		S分辨率(1280, 960, 4, 3),
		//16:9
		S分辨率(1280, 720, 16, 9),
		S分辨率(1366, 768, 16, 9),
		S分辨率(1600, 900, 16, 9),
		S分辨率(1920, 1080, 16, 9),	//1080p
		S分辨率(2560, 1440, 16, 9),	//2k
		S分辨率(3840, 2160, 16, 9),	//4k
		S分辨率(7680, 4320, 16, 9),	//8k
		//3:2
		S分辨率(1800, 1200, 3, 2),	//surface go
		S分辨率(2160, 1440, 3, 2),	//surface pro3
		S分辨率(2736, 1824, 3, 2),	//surface pro4
		S分辨率(3000, 2000, 3, 2),	//surface book 13.5英寸
		S分辨率(3240, 2160, 3, 2),	//surface book 15英寸
	};
	auto w分辨率 = std::make_unique<用户界面::W下拉列表>(e分辨率);
	const auto [v显示器宽, v显示器高] = 视窗::C环境::fg分辨率();
	for (const S分辨率 &v分辨率 : ca分辨率) {
		if (v分辨率.m宽 > v显示器宽 || v分辨率.m高 > v显示器高) {
			continue;
		}
		const int v序号 = (int)w分辨率->ma文本.size();
		w分辨率->ma文本.push_back(v分辨率.fg显示名称());
		ma分辨率.emplace(v序号, v分辨率);
	}
	f添加行(L"{option.resolution}", std::move(w分辨率));
}
void W图形设置::f事件_窗口值变化(用户界面::W窗口 &a窗口, const int &a前, int &a后) {
	switch (a窗口.m标识) {
	case e分辨率:
		m分辨率 = a后;
		break;
	}
}
void W图形设置::f事件_确定() {
	const S分辨率 &v分辨率 = fg分辨率();
	C程序::fs窗口大小(v分辨率.m宽, v分辨率.m高);
}
void W图形设置::f事件_取消() {

}
void W图形设置::f事件_应用() {

}
const S分辨率 &W图形设置::fg分辨率() const {
	return ma分辨率.at(m分辨率);
}
}	//namespace 东方山寨