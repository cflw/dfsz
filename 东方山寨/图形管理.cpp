#include "图形管理.h"
namespace 东方山寨 {
C图形管理::C图形管理() {
	m图形工厂实现.f初始化_数组(ma图形);
}
void C图形管理::f初始化_环境(const C游戏速度 &a游戏速度) {
	m图形工厂实现.f初始化_环境(a游戏速度);
}
void C图形管理::f游戏外计算() {
	ma图形.fe使用_并行([](I图形 & a当前图形) {
		a当前图形.f接口_计算();
		if (a当前图形.f接口_i可销毁()) {
			a当前图形.f对象_销毁();
		}
	});
	if (ma图形.fi变化()) {
		ma图形.f更新();
	}
}
void C图形管理::f游戏外更新() {
	ma图形.fe使用_并行([](I图形 & a当前图形) {
		a当前图形.f接口_更新();
	});
}
void C图形管理::f游戏外显示() {
	std::vector<I图形*> va图形;
	ma图形.fe使用([&](I图形 &a) {
		va图形.push_back(&a);
	});
	std::sort(va图形.begin(), va图形.end(), [](const I图形 *a0, const I图形 *a1)->bool {
		if (a0->m图层 != a1->m图层) {
			return a0->m图层 < a1->m图层;
		} else {
			return a0->m显示编号 < a1->m显示编号;
		}
	});
	for (const I图形* vp图形 : va图形) {
		vp图形->f接口_显示();
	}
}
C对象数组<I图形> &C图形管理::fg图形数组() {
	return ma图形;
}
C图形工厂 C图形管理::f工厂_图形() {
	return C图形工厂(m图形工厂实现);
}
std::shared_ptr<C图形工厂> C图形管理::f工厂_图形p() {
	return std::make_shared<C图形工厂>(m图形工厂实现);
}

}