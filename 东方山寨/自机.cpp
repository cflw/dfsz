#include "程序常量.h"
#include "游戏常量.h"
#include "自机.h"
#include "游戏.h"
#include "玩家.h"
#include "图形引擎.h"
namespace 东方山寨 {
//==============================================================================
// 发射环境
//==============================================================================
class C自机发射环境 : public I玩家发射环境 {
public:
	C自机发射环境(C玩家 &a玩家, const C自机 &a自机):
		m玩家(&a玩家),
		m自机坐标{&a自机.m坐标},
		m低速渐变{&a玩家.m低速渐变},
		m游戏速度{&a自机.m游戏速度} {
	}
	C玩家 &fg玩家() const override {
		return *m玩家;
	}
	t向量2 fg发射坐标() const override {
		return *m自机坐标;
	}
	t向量2 fg中心坐标() const override {
		return *m自机坐标;
	}
	t向量2 fg相对坐标() const override {
		return t向量2::c零;
	}
	float fg相对方向r() const override {
		return 数学::c半π<float>;
	}
	const C游戏速度 &fg游戏速度() const override {
		return **m游戏速度;
	}
	const float &fg低速渐变() const override {
		return *m低速渐变;
	}
public:
	C玩家 *m玩家;
	const t向量2 *m自机坐标;
	const float *m低速渐变;
	const C游戏速度 *const *m游戏速度;
};

//==============================================================================
// 自机
//==============================================================================
void C自机::f关卡初始化() {
	assert(m自机属性 >= 0);
	m坐标.x = 0;
	m坐标.y = c自机初始坐标y;
	m发射子弹->f基础_s子弹属性(m自机属性->m子弹属性.m指针);
	f发射_停止发射子弹();
}
void C自机::f控制_移动(const t向量2 &a速度) {
	m移动 = a速度 * m自机属性->m移动速度;
	m坐标 += m移动 * m游戏速度->fg秒();
}
void C自机::f发射_发射子弹() {
	m发射子弹->f发射();
}
void C自机::f发射_停止发射子弹() {
	m发射子弹->f接口_复位();
}
void C自机::f计算() {
	const float v过秒 = m游戏速度->fg秒();
	m决死时间 += v过秒;
	m无敌时间 -= v过秒;
	m发射子弹->f计算();
	m动画->f接口_动作(E动画动作::e水平移动, m移动.x);
	m动画->f接口_计算();
}
void C自机::f计算_移动范围限制() {
	if (m坐标.x < -c移动范围x) {
		m坐标.x = -c移动范围x;
	} else if (m坐标.x > c移动范围x) {
		m坐标.x = c移动范围x;
	}
	if (m坐标.y < -c移动范围y) {
		m坐标.y = -c移动范围y;
	} else if (m坐标.y > c移动范围y) {
		m坐标.y = c移动范围y;
	}
}
void C自机::f更新() {
	m动画->f接口_更新();
}
void C自机::f显示() const {
	if (fi纹理()) {
		f显示图片();
	} else {
		auto &v图形 = C游戏::fg图形();
		v图形.f画十字(m坐标);
	}
}
void C自机::f绑定玩家(C玩家 &a玩家) {
	m游戏速度 = a玩家.m游戏速度;
	m发射子弹->f初始化_发射环境(std::make_shared<C自机发射环境>(a玩家, *this));
	//m发射->f绑定_玩家(a玩家);
}
//属性
void C自机::fs自机属性(const S自机属性 *a属性) {
	assert(a属性 != nullptr);
	if (m自机属性 == a属性) {
		return;
	}
	//检查有效性
	assert((a属性->m纹理.m指针 != nullptr) ? (a属性->m顶点.m指针 != nullptr) : true);
	//赋值
	m自机属性 = a属性;
	m发射子弹 = m自机属性->m发射子弹->f新建u();
	m发射子弹->f接口_初始化();
	m动画 = m自机属性->m动画->f新建u();
}
const t向量2 &C自机::fg坐标() const {
	return m坐标;
}
const S图片动画属性 &C自机::fg图片动画属性() const {
	return *m自机属性;
}
const S顶点矩形 &C自机::fg顶点矩形() const {
	const auto &v顶点 = m自机属性->m顶点.m指针;
	return v顶点[m动画->f接口_g顶点序号()];
}
t圆形 C自机::fg判定点() const {
	return t圆形{m坐标, m自机属性->m判定半径};
}
t圆形 C自机::fg擦弹点() const {
	return t圆形{m坐标, m自机属性->m擦弹半径};
}
t圆形 C自机::fg吸道具点() const {
	return t圆形{m坐标, m自机属性->m道具半径};
}
t圆形 C自机::fg吃道具点() const {
	return t圆形{m坐标, 8};
}
t向量2 C自机::fg移动预判(float a时间) const {
	return m坐标 + m移动 * a时间;
}
bool C自机::fi无敌() const {
	return (m无敌时间 > 0) || c调试_自机无敌;
	//return m无敌时间 > 0;
}
bool C自机::fi死亡() const {
	return m决死时间 >= c决死时间;
}
//状态
void C自机::f中弹() {
	m决死时间 = 0;
	m无敌时间 = c决死时间;
}
void C自机::f复活() {
	m决死时间 = c无决死时间;
	m无敌时间 = 5;
	f动画_s透明度(0.f);
}
void C自机::f动画_s透明度(float a) {
	m动画->f接口_动作(E动画动作::e透明度, a);
}
}