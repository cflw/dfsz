module;
#include <string>
#include <vector>
#include <functional>
#include <boost/logic/tribool.hpp>
#include "取文本.h"
#include "基础_属性数组.h"
export module 东方山寨.文本管理;
export import cflw.工具.单例;
import 东方山寨.设置管理;
namespace 工具 = cflw::工具;
export namespace 东方山寨 {
boost::tribool f匹配语言(std::wstring_view a文本, std::wstring_view a查找) {
	assert(a文本.size() >= 5 && a查找.size() >= 5);
	if (a文本.substr(0, 2) == a查找.substr(0, 2)) {	//匹配语言
		if (a文本.substr(3, 2) == a查找.substr(3, 2)) {	//匹配地区
			return true;	//完全匹配
		} else {
			return boost::indeterminate;	//部分匹配
		}
	}
	return false;	//不匹配
}
template<typename t迭代器>
t迭代器 f找语言(t迭代器 a开始, t迭代器 a结束, const std::function<std::wstring_view(t迭代器)> &af取语言, std::wstring_view a查找) {
	t迭代器 v暂存找 = a开始;	//没有任何匹配时返回首个
	bool vi中等暂存 = false;
	for (t迭代器 v找 = a开始; v找 != a结束; ++v找) {
		const std::wstring_view v语言 = af取语言(v找);
		if (v语言.empty()) {
			continue;
		}
		const boost::tribool v匹配结果 = f匹配语言(v语言, a查找);
		if (v匹配结果) {	//完全匹配
			return v找;
		} else if (boost::indeterminate(v匹配结果)) {	//部分匹配
			if (!vi中等暂存) {
				v暂存找 = v找;
				vi中等暂存 = true;
			}
		} else {	//不匹配
			if (v暂存找 == a开始) {
				v暂存找 = v找;
			}
		}
	}
	return v暂存找;
}
struct S文本表 {	//包含文本用途,语言,键值对
	std::wstring m名称;	//文本用途
	std::wstring m语言;	//语言地区代码
	std::wstring m显示语言;	//在设置中显示的名称
	std::unique_ptr<C属性数组<std::wstring>> mp数组;	//保存文本键值对
	const std::wstring &fg显示语言() const {	//格式:地区(显示名称), 例如: Engligh, 简体中文
		return m显示语言;
	}
};
class C文本管理 : public 工具::C弱单例<C文本管理> {
public:
	C文本管理() = default;
	C属性数组<std::wstring> &f新文本数组(const std::wstring &a名称, const std::wstring &a语言, const std::wstring &a显示);
	const C属性数组<std::wstring> &f找文本数组(const std::wstring &a名称, const std::wstring &a语言) const;
	C取文本 f取文本数组(const std::wstring &a名称, const std::wstring &a语言) const;
	C取文本 fg普通文本() const;
	C取文本 fg界面文本() const;
	const std::vector<const S文本表 *> &fg普通文本列表() const;	//载入完毕才能调用
	const std::vector<const S文本表 *> &fg界面文本列表() const;	//载入完毕才能调用
	std::vector<const S文本表 *> f生成文本列表(const std::wstring &a名称) const;
private:
	std::vector<S文本表> ma文本表;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
C属性数组<std::wstring> &C文本管理::f新文本数组(const std::wstring &a名称, const std::wstring &a语言, const std::wstring &a显示) {
	assert(!a名称.empty());	//不能空
	assert(!a语言.empty());
	//语言和名称都不匹配才新建
	for (auto &v文本表 : ma文本表) {
		if (v文本表.m语言 == a语言 && v文本表.m名称 == a名称) {
			return *v文本表.mp数组;
		}
	}
	S文本表 v文本数组{ a名称, a语言, a显示, std::make_unique<C属性数组<std::wstring>>() };
	ma文本表.push_back(std::move(v文本数组));
	return *ma文本表.back().mp数组;
}
const C属性数组<std::wstring> &C文本管理::f找文本数组(const std::wstring &a名称, const std::wstring &a语言) const {
	assert(!a名称.empty());	//不能空
	assert(!a语言.empty());
	//先找名称再找语言，如果语言不存在则从匹配的名称中随便选一个
	using t迭代器 = std::vector<S文本表>::const_iterator;
	const auto f取语言 = [&](t迭代器 a当前)->std::wstring_view {
		return a当前->m名称 == a名称 ? a当前->m语言 : std::wstring_view();
	};
	t迭代器 v找 = f找语言<t迭代器>(ma文本表.begin(), ma文本表.end(), f取语言, a语言);
	return *v找->mp数组;
}
C取文本 C文本管理::f取文本数组(const std::wstring &a名称, const std::wstring &a语言) const {
	return C取文本(f找文本数组(a名称, a语言), 计算::f文本语言前缀(a名称, a语言));
}
C取文本 C文本管理::fg普通文本() const {
	return f取文本数组(L"文本", C设置管理::fg实例().fg程序设置().m文本语言);
}
C取文本 C文本管理::fg界面文本() const {
	return f取文本数组(L"用户界面", C设置管理::fg实例().fg程序设置().m界面语言);
}
const std::vector<const S文本表 *> &C文本管理::fg普通文本列表() const {
	static std::vector<const S文本表 *> v列表 = f生成文本列表(L"文本");
	return v列表;
}
const std::vector<const S文本表 *> &C文本管理::fg界面文本列表() const {
	static std::vector<const S文本表 *> v列表 = f生成文本列表(L"用户界面");
	return v列表;
}
std::vector<const S文本表 *> C文本管理::f生成文本列表(const std::wstring &a名称) const {
	std::vector<const S文本表 *> v列表;
	for (const auto &v文本表 : ma文本表) {
		if (v文本表.m名称 == a名称) {
			v列表.push_back(&v文本表);
		}
	}
	return v列表;
}
}	//namespace 东方山寨