module;
#include <vector>
#include "取文本.h"
#include "基础_属性数组.h"
export module 东方山寨.文本管理;
export import cflw.工具.单例;
import 东方山寨.设置管理;
namespace 工具 = cflw::工具;
export namespace 东方山寨 {
struct C文本数组 {
	std::wstring m语言;
	std::wstring m名称;
	std::unique_ptr<C属性数组<std::wstring>> mp数组;
};
class C文本管理 : public 工具::C弱单例<C文本管理> {
public:
	C文本管理() = default;
	C属性数组<std::wstring> &f新文本数组(const std::wstring &a名称, const std::wstring &a语言) {
		assert(!a名称.empty());	//不能空
		assert(!a语言.empty());
		//语言和名称都不匹配才新建
		for (auto &v文本数组 : ma文本数组) {
			if (v文本数组.m语言 == a语言 && v文本数组.m名称 == a名称) {
				return *v文本数组.mp数组;
			}
		}
		C文本数组 v文本数组{a语言, a名称, std::make_unique<C属性数组<std::wstring>>()};
		ma文本数组.push_back(std::move(v文本数组));
		return *ma文本数组.back().mp数组;
	}
	const C属性数组<std::wstring> &f找文本数组(const std::wstring &a名称, const std::wstring &a语言) const {
		assert(!a名称.empty());	//不能空
		assert(!a语言.empty());
		//先找名称再找语言，如果语言不存在则从匹配的名称中随便选一个
		C属性数组<std::wstring> *v找 = nullptr;
		for (auto &v文本数组 : ma文本数组) {
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
	C取文本 f取文本数组(const std::wstring &a名称, const std::wstring &a语言) const {
		return C取文本(f找文本数组(a名称, a语言), 计算::f文本语言前缀(a名称, a语言));
	}
	C取文本 fg普通文本() const {
		return f取文本数组(L"文本", C设置管理::fg实例().fg程序设置().m文本语言);
	}
	C取文本 fg界面文本() const {
		return f取文本数组(L"用户界面", C设置管理::fg实例().fg程序设置().m界面语言);
	}
private:
	std::vector<C文本数组> ma文本数组;
};
}	//namespace 东方山寨