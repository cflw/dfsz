#include "常量.h"
#include "游戏.h"
#include "游戏设置.h"
#include "基础.h"
#include "输入.h"
#include "玩家.h"
#include "自机.h"
#include "子机.h"
#include "玩家子弹基础.h"
#include "玩家子弹制造机.h"
#include "图形_玩家成绩.h"
namespace 东方山寨 {
class C炸弹发射环境 : public I玩家发射环境 {
public:
};
//==============================================================================
// 玩家
//==============================================================================
C玩家::C玩家() {
}
void C玩家::f初始化_环境(const C游戏速度 &a游戏速度) {
	m游戏速度 = &a游戏速度;
	m成绩.m残机 = 3;
	m成绩.m炸弹 = 3;
	m成绩.m火力 = 1;
	m成绩.m最大点 = 10000;
	m成绩.m擦弹 = 0;
	m成绩.m吸收.m值 = 0;
}
void C玩家::f计算() {
	const bool v减速键 = m标志[e低速移动];
	const bool v射击键 = m标志[e射击];
	const bool v炸弹键 = m标志[e炸弹];
	const float v过秒 = m游戏速度->fg秒();
	//时间
	m抑制子弹 -= v过秒;
	m抑制炸弹 -= v过秒;
	//渐变
	const float v渐变目标 = v减速键 ? 1.f : 0.f;
	m低速渐变 = 数学::f线性渐变<float>(m低速渐变, v渐变目标, 8 * v过秒);
	//移动
	if (m标志[e正在复活]) {
		m复活时间 -= v过秒;
		m自机.m坐标 = f计算复活位置();
		if (m复活时间 <= 0) {
			m标志[e正在复活] = false;
		}
	} else {
		m自机.f控制_移动(m方向键);
		m自机.f计算_移动范围限制();
	}
	//发射
	if (v射击键 && f发射_i可发射子弹()) {
		f发射_发射子弹();
	}
	//炸弹
	if (v炸弹键 && f发射_i可发射炸弹()) {
		m发射炸弹->f发射();
	}
	//计算
	m自机.f计算();
	m子机组.f计算();
	m发射炸弹->f计算();
	if (m自机.fi死亡()) {
		f复活();
	}
}
void C玩家::f更新() {
	m自机.f更新();
	m子机组.f更新();
}
void C玩家::f显示() const {
	m自机.f显示();
	m子机组.f显示();
}
void C玩家::f输入按键(const t向量2 &a方向键, const 输入::C按键组 &a按键) {
	m方向键 = a方向键;
	const bool v低速 = a按键.f按键((输入::t索引)E按键::e低速).f按下();
	//处理方向键速度
	if (v低速) {
		m方向键 *= 0.5f;
	}
	m标志[e低速移动] = v低速;
	m标志[e射击] = a按键.f按键((输入::t索引)E按键::e射击).f按下();
	m标志[e炸弹] = a按键.f按键((输入::t索引)E按键::e炸弹).f刚按下();
}
void C玩家::f关卡初始化() {
	m自机.f关卡初始化();
	m子机组.f关卡初始化();
}
void C玩家::f游戏初始化(const S游戏设置 &a设置) {
	m成绩.m得分 = 0;
	m成绩.m残机 = a设置.m残机;
	m成绩.m火力 = a设置.m火力;
	m成绩.m炸弹 = a设置.m炸弹;
	m成绩.m最大点 = a设置.m最大点;
	m成绩.m擦弹 = 0;
	m成绩.m吸收.m值 = 0;
	//玩家成绩
	ma玩家成绩.clear();
	f游戏初始化_玩家成绩图形();
}
void C玩家::f游戏初始化_玩家成绩图形() {
	auto &v文本工厂 = C游戏::fg图形().fg文本工厂();
	二维::S文本格式参数 v格式;
	v格式.fs字号(C画玩家成绩::c字号);
	v格式.fs垂直对齐(二维::E文本垂直对齐::e上);
	const 二维::tp文本格式 v上对齐 = v文本工厂.fc文本格式(v格式);
	v格式.fs垂直对齐(二维::E文本垂直对齐::e下);
	const 二维::tp文本格式 v下对齐 = v文本工厂.fc文本格式(v格式);
	C玩家成绩图形工厂 v玩家成绩图形工厂(C游戏::fg资源().f工厂_图形(), C游戏::fg图形().fg画玩家成绩(), ma玩家成绩);
	constexpr float c行距 = C画玩家成绩::c行距;
	float v上位置 = c边框范围y + c行距;
	float v下位置 = -c边框范围y - c行距;
	const auto f上位置 = [&]()->float {
		return v上位置 -= c行距;
	};
	const auto f下位置 = [&]()->float {
		return v下位置 += c行距;
	};
	v玩家成绩图形工厂.f产生图形<long long>(f上位置(), v上对齐, t颜色::c黑, 
		C玩家成绩图形<long long>::F跟踪_值(m成绩.m得分), 
		C玩家成绩图形<long long>::F计算_渐变(0.1f, 10, 100000),
		&C玩家成绩图形<long long>::f更新_直接);
	v玩家成绩图形工厂.f产生图形<double>(f下位置(), v下对齐, t颜色::c橙,
		[&v难度 = C游戏::fg内容().fg难度()]()->double {return v难度.fg动态难度();},
		&C玩家成绩图形<double>::f计算_直接,
		C玩家成绩图形<double>::F更新_小数(2));
	v玩家成绩图形工厂.f产生图形<int>(f下位置(), v下对齐, t颜色::c黄,
		C玩家成绩图形<int>::F跟踪_值(m成绩.m吸收), 
		C玩家成绩图形<int>::f计算_直接, 
		C玩家成绩图形<int>::F更新_转换([](int a)->std::wstring {return std::to_wstring(a) + L"%";}));
	v玩家成绩图形工厂.f产生图形<int>(f下位置(), v下对齐, t颜色::c灰,
		C玩家成绩图形<int>::F跟踪_值(m成绩.m擦弹),
		&C玩家成绩图形<int>::f计算_直接,
		&C玩家成绩图形<int>::f更新_直接);
	v玩家成绩图形工厂.f产生图形<int>(f下位置(), v下对齐, t颜色::c蓝,
		C玩家成绩图形<int>::F跟踪_值(m成绩.m最大点),
		&C玩家成绩图形<int>::f计算_直接,
		&C玩家成绩图形<int>::f更新_直接);
	v玩家成绩图形工厂.f产生图形<double>(f下位置(), v下对齐, t颜色::c红,
		C玩家成绩图形<double>::F跟踪_分数(m成绩.m火力),
		&C玩家成绩图形<double>::f计算_直接,
		C玩家成绩图形<double>::F更新_小数(2));
	v玩家成绩图形工厂.f产生图形<double>(f下位置(), v下对齐, t颜色::c绿,
		C玩家成绩图形<double>::F跟踪_分数(m成绩.m炸弹),
		&C玩家成绩图形<double>::f计算_直接,
		C玩家成绩图形<double>::F更新_小数(1));
	v玩家成绩图形工厂.f产生图形<double>(f下位置(), v下对齐, t颜色::c紫,
		C玩家成绩图形<double>::F跟踪_分数(m成绩.m残机),
		&C玩家成绩图形<double>::f计算_直接,
		C玩家成绩图形<double>::F更新_小数(1));
}
void C玩家::f发射_发射子弹() {
	m自机.f发射_发射子弹();
	m子机组.f发射_发射子弹();
}
void C玩家::f发射_停止发射子弹() {
	m自机.f发射_停止发射子弹();
	m子机组.f发射_停止发射子弹();
}
void C玩家::f发射_抑制发射子弹(float a时间, bool a立即停止) {
	m抑制子弹 = a时间;
	if (a立即停止) {
		f发射_停止发射子弹();
	}
}
void C玩家::f发射_抑制发射炸弹(float a时间) {
	m抑制炸弹 = a时间;
}
void C玩家::f复活() {
	C游戏::fg内容().f游戏_全屏清弹(m自机.fg坐标());
	m成绩.m残机 -= 1;
	m标志[e正在复活] = true;
	m自机.f复活();
	m子机组.f复活();
	m复活时间 = c复活时间;
}
t向量2 C玩家::f计算复活位置() {
	return {0, c自机初始坐标y - 数学::f插值<float>(0, c复活距离, m复活时间 / c复活时间)};
}
void C玩家::fs自机(int a) {
	const auto &va自机属性 = C游戏::fg资源().fg自机属性();
	m自机.fs自机属性(&va自机属性.fg数据(a));
	m自机.f绑定玩家(*this);
}
void C玩家::fs子机(int a) {
	const auto &va子机属性 = C游戏::fg资源().fg子机属性();
	m子机组.fs子机属性(&va子机属性.fg数据(a));
	m子机组.f绑定玩家(*this);
}
void C玩家::fs炸弹(int a) {
	const auto &va玩家发射 = C游戏::fg资源().fg玩家发射();
	m发射炸弹 = va玩家发射.fg扩展(a)->f新建u();
	m发射炸弹->f初始化_发射环境(std::make_shared<C玩家发射环境>(*this));
	m发射炸弹->f接口_初始化();
}
bool C玩家::f发射_i可发射子弹() const {
	if (m标志[e正在复活]) {
		return false;
	}
	if (m抑制子弹 > 0) {
		return false;
	}
	return true;
}
bool C玩家::f发射_i可发射炸弹() const {
	if (m抑制炸弹 > 0) {
		return false;
	}
	return true;
}
bool C玩家::fi可复活() const {
	return m成绩.m残机 >= 1;
}
//==============================================================================
// 各种值
//==============================================================================
//分数值
void C分数值::f计算() {
	m显示值 = 数学::f倍数渐变<long long>(m显示值, m实际值, 0.1f, 1, 100000);
}
void C分数值::f加分(long long p) {
	m实际值 += p;
}
//吸收值
const float C吸收值::c减少速度 = 50.f * (float)c帧秒;
const float C吸收值::c上限 = 130.f;
C吸收值::operator int() const {
	return (int)m值;
}
void C吸收值::f计算() {
	m值 -= c减少速度;
	if (m值 < 0) {
		m值 = 0;
	} else if (m值 > c上限) {
		m值 -= c减少速度;
	}
	if (m值 >= 100) {
		
	}
}
void C吸收值::f加() {

}
void C吸收值::f满() {
	m值 = c上限;
}
//难度
void C难度::f增加难度(const boost::rational<int> &p) {
	m增加难度 += boost::rational_cast<int>(p * 100'0000);
}
void C难度::f增加难度_最大点(int p) {
	m增加难度 += p;
}
void C难度::f减少难度() {
	//减10%,最多减0.1难度
	if (m增加难度 < 1000000) {
		m增加难度 = m增加难度 * 9 / 10;
	} else {
		m增加难度 -= 100000;
	}
}
float C难度::fg基础难度() const {
	return (float)m基础难度;
}
float C难度::fg动态难度() const {
	return (float)m基础难度 + (float)m增加难度 / 100'0000.f;
}
}	//namespace 东方山寨