#include "玩家子弹发射_发散.h"
#include "计算.h"
namespace 东方山寨 {
namespace 玩家子弹发射 {
C发散::S属性 C发散::S属性::fc间隔(int a数量, float a发散0, float a发散1, float a并列0, float a并列1) {
	return S属性(a数量, std::pair<float, float>(a发散0, a发散1), std::pair<float, float>(a并列0, a并列1));
}
C发散::S属性 C发散::S属性::fc总(int a数量, float a发散0, float a发散1, float a并列0, float a并列1) {
	const float v数量 = static_cast<float>(a数量);
	return S属性(
		a数量, 
		std::pair<float, float>(a发散0 / v数量, a发散1 / v数量), 
		std::pair<float, float>(a并列0 / v数量, a并列1 / v数量)
	);
}
C发散::S属性::S属性(int a数量, std::pair<float, float> a发散, std::pair<float, float> a间隔) :
	m数量(a数量),
	m向外张开角度(a发散),
	m水平坐标间隔(a间隔) {
}
C发散::C工厂::C工厂(const S属性 &a属性) :
	m属性(std::make_shared<S属性>(a属性)) {
}
C玩家子弹发射器 *C发散::C工厂::f接口_新建() const {
	return new C发散(m属性);
}
C发散::C发散(const std::shared_ptr<S属性> &a属性):
	m属性(a属性) {
}
void C发散::f接口_产生子弹() {
	m子弹制造机->m参数.m坐标 = m发射环境->fg发射坐标();
	m子弹制造机->m参数.m速度 = {0, c速度大小};
	for (auto &v循环 : m子弹制造机->f循环(m属性->m数量)) {
		v循环.f变换模板_发散(m发射环境, m属性->m向外张开角度, m属性->m水平坐标间隔);
		m子弹制造机->f产生子弹<C玩家子弹>();
	}
}
//结束
}
}