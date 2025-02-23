#include "玩家子弹发射_发散.h"
import 东方山寨.计算;
namespace 东方山寨 {
namespace 玩家子弹发射 {
//属性
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
//工厂
C发散::C工厂::C工厂(const S属性 &a属性) :
	m属性(std::make_shared<S属性>(a属性)) {
}
std::tuple<const std::shared_ptr<C发散::S属性> &> C发散::C工厂::f工厂_g构造实参() const {
	return std::forward_as_tuple(m属性);
}
//发散
C发散::C发散(const std::shared_ptr<S属性> &a属性):
	m属性(a属性) {
}
void C发散::f接口_产生子弹() {
	m参数.m坐标 = m发射环境->fg发射坐标();
	m参数.m速度 = {0, c速度大小};
	for (auto &v循环 : m参数.f循环(m属性->m数量)) {
		v循环.f变换模板_发散(m发射环境, m属性->m向外张开角度, m属性->m水平坐标间隔);
		m工厂.f产生子弹<C玩家子弹>(m参数);
	}
}
//结束
}	//namespace 玩家子弹发射
}	//namespace 东方山寨