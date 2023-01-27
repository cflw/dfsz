module;
#include "关卡.h"
export module 东方山寨.关卡管理;
import cflw.工具.单例;
namespace 工具 = cflw::工具;
export namespace 东方山寨 {
class C关卡管理 : public 工具::C单例<C关卡管理> {
public:
	C关卡管理() = default;
	C关卡 &fg关卡(int a标识) {	//传入标识,返回关卡
		assert(a标识);	//不能使用0
		return *ma关卡.at(a标识);
	}
	const t关卡组 &fg关卡组(int a标识) {
		assert(a标识);	//不能使用0
		return ma关卡组.at(a标识);
	}
	std::vector<C关卡 *> fg关卡列表(const std::vector<int> &aa标识) {	//传入标识,返回关卡
		std::vector<C关卡 *> v关卡列表;
		v关卡列表.reserve(aa标识.size());
		for (int v标识 : aa标识) {
			v关卡列表.push_back(ma关卡.at(v标识));
		}
		return v关卡列表;
	}
	void f注册关卡(int a标识, C关卡 &a关卡) {
		assert(a标识);	//不能使用0
		assert(ma关卡.find(a标识) == ma关卡.end());	//不能重复,必须空
		ma关卡.emplace(a标识, &a关卡);
		a关卡.m标识 = a标识;
	}
	void f注册关卡组(int a标识, t关卡组 &&a关卡组) {
		assert(a标识);	//不能使用0
		assert(ma关卡组.find(a标识) == ma关卡组.end());	//不能重复,必须空
		assert(a关卡组.size() > 0);
		ma关卡组.emplace(a标识, std::move(a关卡组));
	}
	std::map<int, C关卡 *> ma关卡;
	std::map<int, t关卡组> ma关卡组;
};
}	//namespace 东方山寨