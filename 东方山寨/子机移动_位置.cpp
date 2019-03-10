#include "子机移动_位置.h"
#include "子机.h"
namespace 东方山寨 {
namespace 子机移动 {
//属性
C位置::S属性::S属性(const t向量2 *p坐标) {
	const t向量2 *v正常坐标 = p坐标;
	const t向量2 *v低速坐标 = p坐标 + 10;
	for (int i = 0; i != c数量; ++i) {
		v正常[i] = v正常坐标[i];
		v低速[i] = v低速坐标[i];
	}
}
const t向量2 *C位置::S属性::fg正常(int p序号) const {
	return v正常 + f计算序号(p序号);
}
const t向量2 *C位置::S属性::fg低速(int p序号) const {
	return v低速 + f计算序号(p序号);
}
//取属性
C位置::C取属性::C取属性(const S属性 &a属性, int a数量) :
	v数量{a数量},
	v序号{f计算序号(a数量)},
	v正常{a属性.v正常 + v序号},
	v低速{a属性.v低速 + v序号} {
}
const t向量2 &C位置::C取属性::fg正常(int p序号) const {
	assert(p序号 < v数量);
	return v正常[p序号];
}
const t向量2 &C位置::C取属性::fg低速(int p序号) const {
	assert(p序号 < v数量);
	return v低速[p序号];
}
t向量2 C位置::C取属性::fg插值(int p序号, float p插值) const {
	assert(p序号 < v数量);
	return 数学::f插值<t向量2>(v正常[p序号], v低速[p序号], p插值);
}
//工厂
C位置::C工厂::C工厂(const std::initializer_list<t向量2> &p) :
	v属性(std::make_shared<S属性>(p.begin())) {
	assert(p.size() == c数量 * 2);
}
C位置::C工厂::C工厂(const std::shared_ptr<S属性> &p) :
	v属性(p) {
}
I子机移动 *C位置::C工厂::f接口_新建() const {
	return new C位置(v属性);
}
//主类
int C位置::f计算序号(int p) {
	assert(p >= 0 && p <= 4);
	static const int c序号[] = {0, 0, 1, 3, 6};
	return c序号[p];
}
C位置::C位置(const std::shared_ptr<S属性> &a属性) : 
	v属性{a属性} {
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
	return C取属性{*v属性, *v子机数量};
}
//命名空间结束
}
}