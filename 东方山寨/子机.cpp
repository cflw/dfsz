#include "子机.h"
#include "玩家.h"
#include "子机移动接口.h"
#include "游戏.h"
#include "图形引擎.h"
#include "子机图形.h"
namespace 东方山寨 {
//==============================================================================
// 发射环境
//==============================================================================
class C子机发射环境 : public I玩家发射环境 {
public:
	C子机发射环境(C玩家 &a玩家, const C子机 &a子机) :
		m玩家(&a玩家),
		m自机坐标{&a玩家.m自机.m坐标},
		m子机坐标{&a子机.m坐标},
		m子机目标坐标{&a子机.m目标坐标},
		m低速渐变{&a玩家.m低速渐变},
		m游戏速度{&a子机.m游戏速度} {
	}
	C玩家 &fg玩家() const override {
		return *m玩家;
	}
	t向量2 fg发射坐标() const override {
		return *m子机坐标;
	}
	t向量2 fg中心坐标() const override {
		return *m自机坐标;
	}
	t向量2 fg相对坐标() const override {
		return *m子机目标坐标 - *m自机坐标;
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
	const t向量2 *m子机坐标;
	const t向量2 *m子机目标坐标;
	const float *m低速渐变;
	const C游戏速度 *const *m游戏速度;
};
//==============================================================================
// 子机
//==============================================================================
C子机::C子机() {
}
void C子机::f坐标_移动(const t向量2 &a目标) {
	m目标坐标 = a目标;
	const float m游戏速度 = this->m游戏速度->fg速度();
	const float v渐变倍数 = 0.2f * m游戏速度;
	const float v最大渐变 = 10.f * m游戏速度;
	m坐标.fs倍数渐变(a目标, v渐变倍数, 0, v最大渐变);
}
void C子机::f坐标_重置(const t向量2 &a目标) {
	m坐标 = m目标坐标 = a目标;
}
void C子机::f计算() {
	m发射->f接口_计算();
	m图形->f计算();
	m出生时间 += c帧秒<float> * 4;
}
void C子机::f更新() {
	m图形->f更新();
}
const t向量2 &C子机::fg坐标() const {
	return m坐标;
}
float C子机::fg透明度() const {
	return std::min<float>(m出生时间, 1);
}
void C子机::f出现() {
	m出生时间 = 0;
}
//==============================================================================
// 子机组
//==============================================================================
C子机组::C子机组() {
}
void C子机组::f初始化_在关卡开始() {
	assert(m子机属性 != nullptr);
	m数量 = fg目标子机数();
	for (auto &v子机 : fe使用()) {
		v子机.f出现();
		v子机.m发射->f基础_s子弹属性(m子机属性->m子弹属性.m指针);
	}
	m子机移动->f接口_复位(-1);
	f发射_停止发射子弹();
}
template<typename t子机图形>
void f创建子机图形(C子机 &a子机, C缓冲数组<I图形缓冲> &aa图形缓冲) {
	a子机.m图形 = std::make_unique<t子机图形>(a子机, aa图形缓冲);
}
void C子机组::f初始化_图形(C缓冲数组<I图形缓冲> &aa图形缓冲) {
	C子机 &v子机 = ma子机.front();
	if (v子机.m图形) {
		return;
	}
	const auto vf创建图形 = v子机.m子机属性->m纹理 ? f创建子机图形<C子机图形_图片> : f创建子机图形<C子机图形_线条>;
	//创建图形对象
	for (C子机 &v子机1 : ma子机) {
		vf创建图形(v子机1, aa图形缓冲);
	}
}
void C子机组::fs子机属性(const S子机属性 *a属性) {
	assert(a属性 != nullptr);
	if (m子机属性 == a属性) {
		return;
	}
	m子机属性 = a属性;
	m子机移动 = m子机属性->m移动->f新建u();
	ma子机.resize(m子机属性->m数量上限);
	const I工厂<C玩家子弹发射器> *v发射 = m子机属性->m发射.m指针;
	const I工厂<I动画> *v动画 = m子机属性->m动画.m指针;
	for (C子机 &v子机 : ma子机) {
		v子机.m子机属性 = a属性;
		v子机.m发射 = v发射->f新建u();
		v子机.m发射->f接口_初始化();
	}
}
const S子机属性 &C子机组::f子机属性() const {
	return *m子机属性;
}
void C子机组::f发射_发射子弹() {
	for (auto &v子机 : fe使用()) {
		v子机.m发射->f发射();
	}
}
void C子机组::f发射_停止发射子弹() {
	for (auto &v子机 : fe使用()) {
		v子机.m发射->f接口_复位();
	}
}
void C子机组::f计算() {
	//数量
	const int v目标子机数 = fg目标子机数();
	if (v目标子机数 != m数量) {
		const int v数量差 = v目标子机数 - m数量;
		m数量 = v目标子机数;
		if (v数量差 == 1) {	//+1
			m子机移动->f接口_复位(v目标子机数);
		} else {
			m子机移动->f接口_复位(-1);
		}
		//不使用的子机不显示
		for (int i = v目标子机数; i != fg子机数上限(); ++i) {
			ma子机[i].m出生时间 = 0;
		}
	}
	//移动
	m子机移动->f接口_计算();
	//其它
	for (auto &v子机 : fe使用()) {
		v子机.f计算();
	}
}
void C子机组::f更新() {
	for (auto &v子机 : fe使用()) {
		v子机.f更新();
	}
}
void C子机组::f绑定玩家(C玩家 &a玩家) {
	m火力 = &a玩家.m成绩.m火力;
	m子机移动->f接口_绑定玩家(a玩家);
	C游戏速度 &m游戏速度 = C游戏::g内容.fg游戏速度();
	for (auto &v子机 : ma子机) {
		v子机.m游戏速度 = &m游戏速度;
		v子机.m发射->f初始化_发射环境(std::make_shared<C子机发射环境>(a玩家, v子机));
	}
}
void C子机组::f复活() {
	for (auto &v子机 : fe使用()) {
		v子机.f出现();
	}
	m子机移动->f接口_复位(-1);
}
int C子机组::fg目标子机数() const {
	const int v数量上限 = fg子机数上限();
	const int v火力 = boost::rational_cast<int>(*m火力);
	const int v目标子机数 = (v火力 < v数量上限) ? v火力 : v数量上限;
	return v目标子机数;
}
int C子机组::fg子机数上限() const {
	return m子机属性->m数量上限;
}
循环::C范围<std::vector<C子机>> C子机组::fe使用() {
	return 循环::C范围<std::vector<C子机>>{ma子机, 0, m数量};
}
循环::C范围<const std::vector<C子机>> C子机组::fe使用c() const {
	return 循环::C范围<const std::vector<C子机>>{ma子机, 0, m数量};
}
}