module;
#include "关卡.h"
export module 东方山寨.关卡管理;
import 东方山寨.关卡工厂;
import cflw.工具.单例;
namespace 工具 = cflw::工具;
export namespace 东方山寨 {
class C关卡管理 : public 工具::C单例<C关卡管理> {
public:
	C关卡管理() = default;
	tp关卡 fc关卡(int a关卡标识);
	ta关卡 fc关卡组(int a关卡组标识);
	const I关卡工厂 &fg关卡工厂(int a关卡标识);
	ta关卡工厂 fg关卡工厂组(int a关卡组标识);	//传入关卡组标识,返回关卡工厂组
	ta关卡工厂 fg关卡工厂列表(const std::vector<int> &aa关卡标识);	//传入关卡标识数组,返回关卡工厂组
	void f注册关卡(int a关卡标识, const I关卡工厂 &a关卡工厂);
	void f注册关卡组(int a关卡组标识, const std::vector<int> &aa关卡标识);
	std::map<int, const I关卡工厂 *> ma关卡工厂;
	std::map<int, std::vector<int>> ma关卡组;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
void f注册关卡(int a关卡标识, const I关卡工厂 &a关卡工厂) {	//声明在 关卡工厂.ixx
	C关卡管理::fg实例().f注册关卡(a关卡标识, a关卡工厂);
}
tp关卡 C关卡管理::fc关卡(int a关卡标识) {
	return fg关卡工厂(a关卡标识).f接口_新建s();
}
ta关卡 C关卡管理::fc关卡组(int a关卡组标识) {
	ta关卡 va关卡;
	const ta关卡工厂 &va关卡工厂 = fg关卡工厂组(a关卡组标识);
	for (const auto &v关卡工厂 : va关卡工厂) {
		va关卡.push_back(v关卡工厂->f接口_新建s());
	}
	return va关卡;
}
const I关卡工厂 &C关卡管理::fg关卡工厂(int a关卡标识) {
	assert(a关卡标识);	//不能使用0
	return *ma关卡工厂.at(a关卡标识);
}
ta关卡工厂 C关卡管理::fg关卡工厂组(int a关卡组标识) {
	assert(a关卡组标识);	//不能使用0
	ta关卡工厂 va关卡工厂;
	for (int v关卡标识 : ma关卡组.at(a关卡组标识)) {
		va关卡工厂.push_back(ma关卡工厂.at(v关卡标识));
	}
	return va关卡工厂;
}
ta关卡工厂 C关卡管理::fg关卡工厂列表(const std::vector<int> &aa关卡标识) {
	ta关卡工厂 v关卡列表;
	v关卡列表.reserve(aa关卡标识.size());
	for (int v标识 : aa关卡标识) {
		v关卡列表.push_back(ma关卡工厂.at(v标识));
	}
	return v关卡列表;
}
void C关卡管理::f注册关卡(int a标识, const I关卡工厂 &a关卡工厂) {
	assert(a标识);	//不能使用0
	assert(ma关卡工厂.find(a标识) == ma关卡工厂.end());	//不能重复,必须空
	ma关卡工厂.emplace(a标识, &a关卡工厂);
}
void C关卡管理::f注册关卡组(int a关卡组标识, const std::vector<int> &aa关卡标识) {
	assert(a关卡组标识);	//不能使用0
	assert(ma关卡组.find(a关卡组标识) == ma关卡组.end());	//不能重复,必须空
	assert(aa关卡标识.size() > 0);
	ma关卡组.emplace(a关卡组标识, std::move(aa关卡标识));
}
}	//namespace 东方山寨