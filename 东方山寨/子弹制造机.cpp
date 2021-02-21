#include "子弹制造机.h"
#include "子弹基础.h"
#include "子弹图形缓冲.h"
#include "游戏.h"
#include "自机.h"
#include "标识.h"
namespace 东方山寨 {
//==============================================================================
// 基本属性
//==============================================================================
S子弹参数::S子弹参数() :
	m坐标{t向量2::c零}, m速度{50, 0} {
	m颜色[0] = t颜色::c红;
	m颜色[1] = t颜色::c白;
	m绘制 = (int)E画子弹::e正常;
	m样式 = (int)E子弹::e米弹;
}
void S子弹参数::fs坐标(const t向量2 &a坐标) {
	m坐标 = a坐标;
}
void S子弹参数::fs速度(const t向量2 &a速度) {
	m速度 = a速度;
}
void  S子弹参数::fs速度_到自机(float a大小) {
	m速度 = t向量2::fc方向r(a大小, m坐标.f到点方向r(C游戏::fg内容().fg自机().fg坐标()));
}
void S子弹参数::fs顶色(const t颜色 &a颜色) {
	m颜色[0] = a颜色;
}
void S子弹参数::fs底色(const t颜色 &a颜色) {
	m颜色[1] = a颜色;
}
void S子弹参数::fs长度(float a) {
	m长宽.x = a;
}
void S子弹参数::fs宽度(float a) {
	m长宽.y = a;
}
void S子弹参数::fs样式(int a) {
	m样式 = a;
}
void S子弹参数::fs绘制(int a) {
	m绘制 = a;
}
void S子弹参数::fs子弹基础(const C子弹 &a子弹) {
	m坐标 = a子弹.m坐标;
	m速度 = a子弹.m速度;
	m颜色[0] = a子弹.m颜色[0];
	m颜色[1] = a子弹.m颜色[1];
	m绘制 = a子弹.m图形缓冲->m绘制;
	m样式 = a子弹.m子弹属性;
}
void S子弹参数::fs立即出现(bool a) {
	m出现 = a ? 1.f : 0.f;
}
//==============================================================================
// 循环变换
//==============================================================================
int C子弹制造机::C循环::C变换::fg计数() const {
	return m计数;
}
int C子弹制造机::C循环::C变换::fg总数() const {
	return m总数;
}
float C子弹制造机::C循环::C变换::fg百分比() const {
	return (float)(m计数) / (float)(m总数 - 1);
}
//循环计算
float C子弹制造机::C循环::C变换::f计算(t标志 a标志) const {
	return C循环计算::f计算(fg计数(), fg总数(), a标志);
}
float C子弹制造机::C循环::C变换::f计算_正弦波(float a振幅, float a频率, t计算 a计算) const {
	const float v计算 = a计算.value_or(f计算(C循环计算::c小数));
	const float v正弦 = sin(数学::c二π<float> * v计算 * a频率);
	return a振幅 * v正弦;
}
t向量2 C子弹制造机::C循环::C变换::f计算_速度变换(float a大小, float a方向, t计算 a计算) const {
	const float v计算 = a计算.value_or(f计算(C循环计算::c标准计数));
	const t向量2 &m速度 = m参数->m速度;
	const float v大小 = m速度.fg大小() + a大小 * v计算;
	const float v方向 = m速度.fg方向r() + a方向 * v计算;
	return t向量2::fc方向r(v大小, v方向);
}
t向量2 C子弹制造机::C循环::C变换::f计算_速度线性插值(const t向量2 &a目标, t计算 a计算) const {
	const float v计算 = a计算.value_or(f计算(C循环计算::c小数));
	const t向量2 &m速度 = m参数->m速度;
	return 数学::f插值(m速度, a目标, v计算);
}
t向量2 C子弹制造机::C循环::C变换::f计算_速度平滑插值(const t向量2 &a目标, t计算 a计算) const {
	const float v计算 = a计算.value_or(f计算(C循环计算::c小数));
	const t向量2 &v原来速度 = m参数->m速度;
	const float v原来大小 = v原来速度.fg大小();
	const float v原来方向 = v原来速度.fg方向r();
	const float v目标大小 = a目标.fg大小();
	const float v目标方向 = a目标.fg方向r();
	const float v插值大小 = 数学::f插值<float>(v原来大小, v目标大小, v计算);
	const float v插值方向 = 数学::C角度计算<float>::c弧度.f插值(v原来方向, v目标方向, v计算);
	return t向量2::fc方向r(v插值大小, v插值方向);
}
//循环变换
void C子弹制造机::C循环::C变换::f变换_备份() {
	*m备份 = *m参数;
}
void C子弹制造机::C循环::C变换::f变换_还原() {
	*m参数 = *m备份;
}
void C子弹制造机::C循环::C变换::f变换_圆形(int a圈数, t计算 a计算) {
	t向量2 &m速度 = m参数->m速度;
	const float v计算 = a计算.value_or(f计算(C循环计算::c圆形));
	m速度 = f计算_速度变换(0, 数学::c二π<float> * a圈数, v计算);
}
void C子弹制造机::C循环::C变换::f变换_椭圆(float a短轴变化) {
	t向量2 &m速度 = m参数->m速度;
	const float v方向 = m速度.fg方向r();
	const float v长轴 = m速度.fg大小();
	const float v短轴 = v长轴 - a短轴变化;
	const float v旋转方向 = f计算(C循环计算::c圆形) * 数学::c二π<float>;
	m速度.x = v长轴 * cos(v旋转方向);
	m速度.y = v短轴 * sin(v旋转方向);
	m速度 = m速度.f旋转r(v方向);
}
void C子弹制造机::C循环::C变换::f变换_扇形(float a间隔, t计算 a计算) {
	t向量2 &m速度 = m参数->m速度;
	const float v计算 = a计算.value_or(f计算(C循环计算::c计数居中));
	m速度 = f计算_速度变换(0, a间隔, v计算);
}
void C子弹制造机::C循环::C变换::f变换_速度(float a大小, float a方向, t计算 a计算) {
	t向量2 &m速度 = m参数->m速度;
	m速度 = f计算_速度变换(a大小, a方向, a计算);
}
void C子弹制造机::C循环::C变换::f变换_速度线性插值(const t向量2 &a目标, t计算 a计算) {
	t向量2 &m速度 = m参数->m速度;
	m速度 = f计算_速度线性插值(a目标, a计算);
}
void C子弹制造机::C循环::C变换::f变换_速度平滑插值(const t向量2 &a目标, t计算 a计算) {
	t向量2 &m速度 = m参数->m速度;
	m速度 = f计算_速度平滑插值(a目标, a计算);
}
void C子弹制造机::C循环::C变换::f变换_颜色(int i0, const t颜色 &a颜色, t计算 a计算) {
	const float v计算 = a计算.value_or(f计算(C循环计算::c小数));
	t颜色 &v修改色 = m参数->m颜色[i0];
	v修改色 = v修改色.f全插值(a颜色, v计算);
}
void C子弹制造机::C循环::C变换::f变换_坐标插值(const t向量2 &a目标, t计算 a计算) {
	const float v计算 = a计算.value_or(f计算(C循环计算::c小数));
	t向量2 &m坐标 = m参数->m坐标;
	m坐标 = 数学::f插值<t向量2>(m坐标, a目标, v计算);
}
void C子弹制造机::C循环::C变换::f变换_坐标前移(float a位移, t计算 a计算) {
	t向量2 &m速度 = m参数->m速度;
	f变换_坐标平移(m速度.f大小(a位移), a计算);
}
void C子弹制造机::C循环::C变换::f变换_坐标平移(const t向量2 &a移动, t计算 a计算) {
	const float v计算 = a计算.value_or(f计算(C循环计算::c标准计数));
	m参数->m坐标 += a移动 * v计算;
}
//==============================================================================
// 循环总控制
//==============================================================================
C子弹制造机::C循环::C循环(C子弹制造机 &a工厂, int a次数) :
	m工厂(&a工厂), m总数(a次数), m参数备份(a工厂.m参数) {
}
//==============================================================================
// 实现
//==============================================================================
void C子弹制造机::C实现::f初始化_环境(const C游戏速度 &a游戏速度) {
	m游戏速度 = &a游戏速度;
}
void C子弹制造机::C实现::f初始化_数组(C对象数组<C子弹> &aa子弹, C缓冲数组<C子弹图形缓冲> &aa缓冲) {
	ma子弹 = &aa子弹;
	ma子弹图形缓冲 = &aa缓冲;
}
void C子弹制造机::C实现::f初始化_资源(const C属性数组<S子弹属性> &aa子弹属性, const C扩展数组<I画子弹> &aa画子弹) {
	ma子弹属性 = &aa子弹属性;
	ma画子弹 = &aa画子弹;
}
void C子弹制造机::C实现::f产生子弹(const std::shared_ptr<C子弹> &a子弹, S子弹参数 &a) {
	//计算缓存
	if (a.m样式.m指针 == nullptr) {
		a.m样式.m指针 = ma子弹属性->fg指针(a.m样式.m整数);
	}
	if (a.m绘制.m指针 == nullptr) {
		a.m绘制.m指针 = ma画子弹->fg扩展(a.m绘制.m整数);
	}
	//初始化子弹
	C子弹 *const v子弹 = a子弹.get();
	v子弹->f接口_参数初始化(a);
	v子弹->m动画帧 = 0;
	v子弹->m游戏速度 = m游戏速度;
	v子弹->m计数指针 = &ma子弹->m计数;
	v子弹->f事件_初始化();
	if (v子弹->m标志[C子弹::e取消产生]) {
		v子弹->m标志.reset();
	}
	v子弹->m图形缓冲 = ma子弹图形缓冲->f新建();
	v子弹->m图形缓冲->m绘制 = a.m绘制.m指针;
	//数据合法性检查
	assert(v子弹->m速度.fg大小() > 0);
	assert(v子弹->m缩放.x >= 0);
	assert(v子弹->m缩放.y >= 0);
	//结束
	v子弹->f对象_使用();
	ma子弹->f添加(a子弹);
}
bool C子弹制造机::C实现::fi有空() {
	return ma子弹->fi有空();
}
//==============================================================================
// 公共函数
//==============================================================================
C子弹制造机::C子弹制造机(C实现 &p实现) :
	m实现{&p实现} {
}
C子弹制造机::~C子弹制造机() {
}
std::shared_ptr<C子弹> C子弹制造机::f产生子弹() {
	if (m实现->fi有空()) {
		std::shared_ptr<C子弹> v子弹 = std::make_shared<C子弹>();
		m实现->f产生子弹(v子弹, m参数);
		return v子弹;
	}
	return nullptr;
}
bool C子弹制造机::f实现_i有空() {
	return m实现->fi有空();
}
void C子弹制造机::f实现_产生子弹(const std::shared_ptr<C子弹> &a子弹) {
	m实现->f产生子弹(a子弹, m参数);
}
C子弹制造机::C循环 C子弹制造机::f循环(int a次数) {
	if (m实现->ma子弹->fi有空(a次数)) {
		return C循环(*this, a次数);
	} else {
		return C循环(*this, 0);
	}
}
C子弹制造机::t循环生成器 C子弹制造机::f循环(const tf循环模板 &af模板) {
	return af模板(*this);
}
//==============================================================================
// 循环模板
//==============================================================================
C子弹制造机::tf循环模板 F循环模板_旋转(float a旋转角, int a次数, int a边细分, float a坐标前移倍数, float a速度插值) {
	return [=](C子弹制造机 &a子弹制造机)->C子弹制造机::t循环生成器 {
		C子弹制造机::C循环 v循环(a子弹制造机, a次数 * a边细分);
		const t向量2 v初始坐标 = a子弹制造机.m参数.m坐标;
		const t向量2 v初始速度 = a子弹制造机.m参数.m速度;
		const float v初始方向 = v初始速度.fg方向r();
		const float v初始大小 = v初始速度.fg大小();
		t向量2 v当前速度 = v初始速度;
		int i = 0;
		for (int v角 = 1; v角 <= a次数; ++v角) {
			const float v下一方向 = v初始方向 + a旋转角 * v角;
			const t向量2 v下一速度 = t向量2::fc方向r(v初始大小, v下一方向);
			for (int v边计数 = 0; v边计数 != a边细分; ++v边计数) {
				const t向量2 v中间速度 = 数学::f插值<t向量2>(v当前速度, v下一速度, (float)v边计数 / (float)a边细分);
				a子弹制造机.m参数.m速度 = 数学::f插值<t向量2>(v初始速度, v中间速度, a速度插值);
				a子弹制造机.m参数.m坐标 = v初始坐标 + v中间速度 * a坐标前移倍数;
				co_yield v循环.f变换(i++);
				v循环.f参数还原();
			}
			v当前速度 = v下一速度;
		}
	};
}
C子弹制造机::tf循环模板 F循环模板_正多边形(int a角数, int a边细分, float a坐标前移倍数, float a速度插值) {
	assert(a角数 >= 3);
	const float v旋转角 = 数学::c二π<float> / (float)a角数;
	return F循环模板_旋转(v旋转角, a角数, a边细分, a坐标前移倍数, a速度插值);
}
C子弹制造机::tf循环模板 F循环模板_锐多角星(int a角数, int a边细分, float a坐标前移倍数, float a速度插值) {
	assert(a角数 % 2 == 1);
	assert(a角数 >= 5);
	const float v旋转角 = 数学::c二π<float> / (float)a角数 * (a角数 / 2);
	return F循环模板_旋转(v旋转角, a角数, a边细分, a坐标前移倍数, a速度插值);
}
C子弹制造机::tf循环模板 F循环模板_钝多角星(int a角数, int a边细分, float a坐标前移倍数, float a速度插值) {
	assert(a角数 % 2 == 1);
	assert(a角数 >= 5);
	const float v旋转角 = 数学::c二π<float> / (float)a角数 * 2;
	return F循环模板_旋转(v旋转角, a角数, a边细分, a坐标前移倍数, a速度插值);
}

}	//namespace 东方山寨