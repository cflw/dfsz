module;
#include "界面包含.h"
export module 东方山寨.界面_选项.选项列表;
export import 东方山寨.界面语言;
import 东方山寨.文本管理;
export namespace 东方山寨 {
//==============================================================================
// 模板
//==============================================================================
class W选项列表 : public 用户界面::W窗口框架, public 东方山寨::I跟踪界面语言 {
public:
	static constexpr float c行高 = 20;
	static constexpr float c行距 = c行高 * 0.5f;
	static const 用户界面::S文本样式 c标签文本样式;
	struct S行 {
		std::unique_ptr<用户界面::W标签> w标签;
		std::unique_ptr<用户界面::W窗口> w控制;
	};
	W选项列表() = default;
	void f响应_初始化();
	virtual void f事件_确定();
	virtual void f事件_取消();
	virtual void f事件_应用();	//生效返回true,无需修改返回false
	void f事件_刷新文本() override;	//刷新左边标签,派生类负责刷新右边控件
	void f属性_s布局(const 用户界面::S布局参数 &a参数) override;
	virtual bool f状态_i修改();	//修改设置但是未应用
	void f添加行(const std::wstring &a标签, std::unique_ptr<用户界面::W窗口> &&a控制);	//在 f响应_加载 中调用
	std::vector<S行> ma行;
	用户界面::C表格排行布局 m行布局;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
const 用户界面::S文本样式 W选项列表::c标签文本样式 = {16, 用户界面::E对齐::e居左};
void W选项列表::f响应_初始化() {
	int i = 0;
	for (const auto &[vp名称, vp控制] : ma行) {
		用户界面::C表格排列布局 v列布局 = m行布局.fc生成排列布局(i++);
		const float v标签宽 = m尺寸.x * 0.5f;
		const float v控制宽 = m尺寸.x * 0.5f;
		vp名称->f属性_s布局(v列布局.f移动生成(v标签宽));
		vp控制->f属性_s布局(v列布局.f移动生成(v控制宽));
		f动作_添加窗口(*vp名称);
		f动作_添加窗口(*vp控制);
		vp名称->f动作_显示();
		vp控制->f动作_显示();
	}
	this->f事件_刷新文本();
}
void W选项列表::f事件_确定() {
	this->f事件_应用();
}
void W选项列表::f事件_取消() {
}
void W选项列表::f事件_应用() {
}
bool W选项列表::f状态_i修改() {
	return false;
}
void W选项列表::f事件_刷新文本() {
	const C取文本 &va界面文本 = C文本管理::fg实例().fg界面文本();
	for (auto &v行 : ma行) {
		v行.w标签->f生成文本(va界面文本);
	}
}
void W选项列表::f属性_s布局(const 用户界面::S布局参数 &a参数) {
	W窗口::f属性_s布局(a参数);
	m行布局.f属性_s行布局(t向量2::c零, a参数.m尺寸, c行高);
	m行布局.f属性_s行距(c行距);
}
void W选项列表::f添加行(const std::wstring &a标签模板, std::unique_ptr<用户界面::W窗口> &&a控制) {
	std::unique_ptr<用户界面::W标签> v标签 = std::make_unique<用户界面::W标签>();
	v标签->f属性_s文本模板(a标签模板);
	v标签->f属性_s文本样式(c标签文本样式);
	auto &v行 = ma行.emplace_back();
	v行.w标签 = std::move(v标签);
	v行.w控制 = std::move(a控制);
}
}	//namespace 东方山寨