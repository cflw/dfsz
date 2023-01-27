module;
#include "载入.h"
#include "关卡.h"
module 东方山寨.载入.关卡组;
import 东方山寨.关卡标识;
import 东方山寨.关卡管理;
namespace 东方山寨::载入 {
void C内部载入::f关卡组() {
	std::pair<E关卡, std::vector<int>> va关卡组[] = {
		{E关卡::e测试, {(int)E关卡::e测试, (int)E关卡::e测试+1}},
		{E关卡::e正式, {(int)E关卡::e正式+1, (int)E关卡::e正式+2}},
	};
	C关卡管理 &v关卡管理 = C关卡管理::fg实例();
	for (const auto &[v标识, va关卡] : va关卡组) {
		std::vector<C关卡 *> v关卡组 = v关卡管理.fg关卡列表(va关卡);
		v关卡管理.f注册关卡组((int)v标识, std::move(v关卡组));
	}
}
}	//namespace 东方山寨::载入