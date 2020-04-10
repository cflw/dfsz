#include "子机移动_位置.h"
#include "子机.h"
namespace 东方山寨 {
namespace 子机移动 {
//属性
C位置::S属性::S属性(const t向量2 *a坐标) {
	const t向量2 *v正常坐标 = a坐标;
	const t向量2 *v低速坐标 = a坐标 + 10;
	for (int i = 0; i != c数量; ++i) {
		m正常[i] = v正常坐标[i];
		m低速[i] = v低速坐标[i];
	}
}
const t向量2 *C位置::S属性::fg正常(int a序号) const {
	return m正常 + f计算序号(a序号);
}
const t向量2 *C位置::S属性::fg低速(int a序号) const {
	return m低速 + f计算序号(a序号);
}
//取属性
C位置::C取属性::C取属性(const S属性 &a属性, int a数量) :
	m数量{a数量},
	m序号{f计算序号(a数量)},
	m正常{a属性.m正常 + m序号},
	m低速{a属性.m低速 + m序号} {
}
const t向量2 &C位置::C取属性::fg正常(int a序号) const {
	assert(a序号 < m数量);
	return m正常[a序号];
}
const t向量2 &C位置::C取属性::fg低速(int a序号) const {
	assert(a序号 < m数量);
	return m低速[a序号];
}
t向量2 C位置::C取属性::fg插值(int a序号, float a插值) const {
	assert(a序号 < m数量);
	return 数学::f插值<t向量2>(m正常[a序号], m低速[a序号], a插值);
}
//工厂
C位置::C工厂::C工厂(const std::initializer_list<t向量2> &a) :
	m属性(std::make_shared<S属性>(a.begin())) {
	assert(a.size() == c数量 * 2);
}
C位置::C工厂::C工厂(const std::shared_ptr<S属性> &a) :
	m属性(a) {
}
std::tuple<const std::shared_ptr<C位置::S属性> &> C位置::C工厂::f工厂_g构造实参() const {
	return std::forward_as_tuple(m属性);
}
//主类
int C位置::f计算序号(int a) {
	assert(a >= 0 && a <= 4);
	static const int c序号[] = {0, 0, 1, 3, 6};
	return c序号[a];
}
C位置::C位置(const std::shared_ptr<S属性> &a属性) : 
	m属性{a属性} {
}
void C位置::f接口_计算() {
	C取属性 v取属性 = f取属性();
	for (int i = 0; i < *v子机数量; ++i) {
		C子机 &v子机 = va子机->at(i);
		const t向量2 v渐变伸缩 = t向量2::fc方向r(5.f * (0.5f - abs(0.5f - *v低速渐变)), v自机坐标->f到点方向r(v子机.fg坐标()));
		const t向量2 v位移 = v取属性.fg插值(i, *v低速渐变);
		const t向量2 v目标坐标 = *v自机坐标 + v位移 + v渐变伸缩;
		v子机.f坐标_移动(v目标坐标);
	}
}
void C位置::f接口_复位(int a) {
	a -= 1;
	auto f重置 = [
		this,
		v取属性 = f取属性()
	](int i) {
		C子机 &v子机 = va子机->at(i);
		v子机.f坐标_重置(*v自机坐标 + v取属性.fg插值(i, *v低速渐变));
	};
	if (a >= 0) {
		if (a <= *v子机数量) {
			f重置(a);
		}
	} else {
		for (int i = 0; i < *v子机数量; ++i) {
			f重置(i);
		}
	}
}
C位置::C取属性 C位置::f取属性() const {
	return C取属性{*m属性, *v子机数量};
}
//命名空间结束
}
}