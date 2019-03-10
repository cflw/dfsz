#include "动画.h"
#include "游戏.h"
namespace 东方山寨 {
//==============================================================================
// 动画接口&无动画
//==============================================================================
void I动画::f接口_计算() {
}
void I动画::f接口_更新() {
}
void I动画::f接口_s父对象(void *) {
}
int I动画::f接口_g顶点序号() const {
	return 0;
}
void I动画::f接口_动作(const E动画动作 &, const t动画动作值 &) {
}
t向量3 I动画::f接口_g旋转() const {
	return t向量3::c零;
}
t向量3 I动画::f接口_g缩放() const {
	return t向量3::c一;
}
float I动画::f接口_g透明度() const {
	return 1;
}
const C游戏速度 *I动画::f接口_g游戏速度() const {
	return &C游戏::g内容.fg游戏速度();
}
int I动画::fg动作值i(const t动画动作值 &p) {
	if (std::holds_alternative<int>(p)) {
		return std::get<int>(p);
	} else if (std::holds_alternative<float>(p)) {
		return (int)std::get<float>(p);
	} else {
		if (std::get<bool>(p)) {
			return 1;
		} else {
			return 0;
		}
	}
}
float I动画::fg动作值f(const t动画动作值 &p) {
	if (std::holds_alternative<float>(p)) {
		return std::get<float>(p);
	} else if (std::holds_alternative<int>(p)) {
		return (float)std::get<int>(p);
	} else {
		if (std::get<bool>(p)) {
			return 1;
		} else {
			return 0;
		}
	}
}
bool I动画::fg动作值b(const t动画动作值 &p) {
	if (std::holds_alternative<bool>(p)) {
		return std::get<bool>(p);
	} else if (std::holds_alternative<int>(p)) {
		return std::get<int>(p);
	} else {
		return std::get<float>(p);
	}
}
//==============================================================================
// 角色动画
//==============================================================================
//工厂
C角色动画::C工厂::C工厂(std::shared_ptr<S属性> p):
	m属性{p} {
}
I动画 *C角色动画::C工厂::f接口_新建() const {
	return new C角色动画(m属性);
}
//类
C角色动画::C角色动画(std::shared_ptr<S属性> p):
	m属性{p},
	m动画方向{&p->m正常},
	m目标方向{&p->m正常} {
}
void C角色动画::f接口_更新() {
	const auto &v游戏速度 = C游戏::fg内容().fg游戏速度();
	const float v过帧 = v游戏速度.fg渲染帧();
	const float v过秒 = v游戏速度.fg渲染秒();
	const float v变化帧 = m动画方向->m变化速度 * v过帧;
	const float v循环帧 = m动画方向->m循环速度 * v过帧;
	//动画帧
	if (m动画方向 == m目标方向) {	//相同的方向
		const float &v循环 = m动画方向->m循环;
		const float &v帧数 = m动画方向->m帧数;
		if (m动画帧 < v循环) {
			m动画帧 += v变化帧;
		} else {
			m动画帧 += v循环帧;
		}
		if (m动画帧 > v帧数) {
			m动画帧 = v循环;
		}
	} else {	//不同的方向
		if (m目标方向 == &m属性->m正常) {
			const float &v循环 = m动画方向->m循环;
			if (m动画帧 > v循环) {
				m动画帧 = v循环;
			}
			m动画帧 -= v变化帧;
			if (m动画帧 <= 0) {
				m动画方向 = m目标方向;
			}
		} else {
			m动画方向 = m目标方向;
			m动画帧 = 0;
		}
	}
	//透明度
	if (m透明度 < 1) {
		m透明度 += 2 * v过秒;
	}
	if (m透明度 > 1) {
		m透明度 = 1;
	}
}
void C角色动画::f接口_动作(const E动画动作 &a动作, const t动画动作值 &a值) {
	switch (a动作) {
	case E动画动作::e正常:
		f动作_正常();
		break;
	case E动画动作::e水平移动:
		f动作_水平移动(I动画::fg动作值f(a值));
		break;
	case E动画动作::e透明度:
		f动作_透明度(I动画::fg动作值f(a值));
		break;
	}
}
void C角色动画::f动作_正常() {
	m目标方向 = &m属性->m正常;
}
void C角色动画::f动作_水平移动(float a) {
	if (a < 0) {
		return f动作_左移();
	} else if (a > 0) {
		return f动作_右移();
	} else {
		return f动作_正常();
	}
}
void C角色动画::f动作_左移() {
	m目标方向 = &m属性->m左移;
}
void C角色动画::f动作_右移() {
	m目标方向 = &m属性->m右移;
}
void C角色动画::f动作_透明度(float a) {
	m透明度 = a;
}
int C角色动画::f接口_g顶点序号() const {
	return (int)m动画帧 + m动画方向->m序号;
}
t向量3 C角色动画::f接口_g缩放() const {
	if (m动画方向->m境像) {
		return {-1, 1, 1};
	} else {
		return t向量3::c一;
	}
}
float C角色动画::f接口_g透明度() const {
	return m透明度;
}
//==============================================================================
// 二维变换动画
//==============================================================================
C二维变换动画::C二维变换动画(float a旋转, const t向量2 &a缩放, const tf计算 &af计算):
	m旋转{a旋转},
	m缩放{a缩放},
	mf计算{af计算} {
}
void C二维变换动画::f接口_计算() {
	mf计算(*this);
}
t向量3 C二维变换动画::f接口_g旋转() const {
	return {0, 0, m旋转};
}
t向量3 C二维变换动画::f接口_g缩放() const {
	return {m缩放.x, m缩放.y, 1};
}
//=============================================================================
// 三维变换动画
//=============================================================================
C三维变换动画::C三维变换动画(const t向量3 &a旋转, const t向量3 &a缩放, const tf计算 &af计算):
	m旋转{a旋转},
	m缩放{a缩放},
	mf计算{af计算} {
}
void C三维变换动画::f接口_计算() {
	mf计算(*this);
}
t向量3 C三维变换动画::f接口_g旋转() const {
	return m旋转;
}
t向量3 C三维变换动画::f接口_g缩放() const {
	return m缩放;
}

}