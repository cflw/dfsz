module;
#include "界面包含.h"
export module 东方山寨.界面_选项.语言设置;
import 用户界面.控件;
export import 东方山寨.界面_选项.选项列表;
import 东方山寨.设置管理;
import 东方山寨.文本管理;
export namespace 东方山寨 {
class W语言设置 : public W选项列表 {
public:
	enum E标识 {
		e界面语言,
		e文本语言,
	};
	W语言设置() = default;
	void f响应_载入() override;
	void f响应_初始化() override;
	void f事件_窗口值变化(用户界面::W窗口 &a窗口, const int &a前, int &a后) override;
	void f事件_确定() override;
	void f事件_取消() override;
	void f事件_应用() override;
	static void f设置下拉列表(用户界面::W下拉列表 &a下拉列表, const std::vector<const S文本表 *> &a语言列表);
	static int f语言序号(const std::vector<const S文本表 *> &a语言列表, const std::wstring &a语言);
	std::vector<const S文本表 *> m界面文本列表;
	std::vector<const S文本表 *> m普通文本列表;
	struct S设置 {
		auto operator <=>(const S设置 &) const = default;
		int m界面语言 = -1;
		int m文本语言 = -1;
	} m当前, m修改, m备份;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
void W语言设置::f响应_载入() {
	auto &v程序管理 = C设置管理::fg实例().fg程序设置();
	auto &v文本管理 = C文本管理::fg实例();
	m界面文本列表 = v文本管理.fg界面文本列表();
	m普通文本列表 = v文本管理.fg普通文本列表();
	m当前.m界面语言 = f语言序号(m界面文本列表, v程序管理.m界面语言);
	m当前.m文本语言 = f语言序号(m普通文本列表, v程序管理.m文本语言);
	//界面语言
	auto wp界面语言 = std::make_unique<用户界面::W下拉列表>(e界面语言);
	f设置下拉列表(*wp界面语言, m界面文本列表);
	wp界面语言->f属性_s选择0(m当前.m界面语言);
	f添加行(L"{option.uilanguage}", std::move(wp界面语言));
	//文本语言
	auto wp文本语言 = std::make_unique<用户界面::W下拉列表>(e文本语言);
	f设置下拉列表(*wp文本语言, m普通文本列表);
	wp文本语言->f属性_s选择0(m当前.m文本语言);
	f添加行(L"{option.textlanguage}", std::move(wp文本语言));
}
void W语言设置::f响应_初始化() {
	W选项列表::f响应_初始化();
	m修改 = m备份 = m当前;
}
void W语言设置::f事件_窗口值变化(用户界面::W窗口 &a窗口, const int &a前, int &a后)  {
	switch (a窗口.m标识) {
	case e界面语言:
		m修改.m界面语言 = a后;
		break;
	case e文本语言:
		m修改.m文本语言 = a后;
		break;
	}
}
void W语言设置::f事件_确定() {
	f事件_应用();
}
void W语言设置::f事件_取消() {
	m修改 = m备份;
	f事件_应用();
}
void W语言设置::f事件_应用() {
	if (m当前 == m修改) {
		return;
	}
	auto &v程序管理 = C设置管理::fg实例().fg程序设置();
	auto &v界面 = C界面引擎::fg实例();
	//语言
	const std::wstring &v界面语言 = m界面文本列表[m修改.m界面语言]->m语言;
	if (v程序管理.m界面语言 != v界面语言) {
		v程序管理.m界面语言 = v界面语言;
		v界面.f更新界面语言();
	}
	const std::wstring &v文本语言 = m普通文本列表[m修改.m界面语言]->m语言;
	v程序管理.m文本语言 = v文本语言;
	m当前 = m修改;
}
void W语言设置::f设置下拉列表(用户界面::W下拉列表 &a下拉列表, const std::vector<const S文本表 *> &a语言列表) {	//使用语言列表对下拉列表进行赋值
	std::transform(a语言列表.begin(), a语言列表.end(), std::back_inserter(a下拉列表.ma文本),
		[](const S文本表 *a)->std::wstring {return a->fg显示语言(); });
}
int W语言设置::f语言序号(const std::vector<const S文本表 *> &a语言列表, const std::wstring &a语言) {	//查找语言名称在语言列表中的位置
	int i = 0;
	for (auto iter = a语言列表.begin(); iter != a语言列表.end(); ++iter) {
		if ((*iter)->m语言 == a语言) {
			return i;
		}
		++i;
	}
	return -1;
}
}	//namespace 东方山寨