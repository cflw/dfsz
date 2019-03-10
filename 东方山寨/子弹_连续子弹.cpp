#include "子弹_连续子弹.h"
#include "子弹图形接口.h"
#include "子弹制造机.h"
#include "游戏.h"
namespace 东方山寨 {
//==============================================================================
// 连续子弹的连接工具
//==============================================================================
C连续子弹::C连接工具::C连接工具() :
	mf连接{f连续子弹_连接0} {
}
C连续子弹::C连接工具::C连接工具(tf两点操作 a) :
	mf连接{a} {
}
C连续子弹::C连接工具 &C连续子弹::C连接工具::operator +=(const std::shared_ptr<C连续子弹> &a) {
	if (m这) {
		mf连接(*m这, *a);
	}
	m这 = a;
	return *this;
}
//环形工具
C连续子弹::C环形工具::C环形工具() :
	mf连接{f连续子弹_连接0} {
}
C连续子弹::C环形工具::C环形工具(tf两点操作 a) :
	mf连接{a} {
}
C连续子弹::C环形工具::~C环形工具() {
	mf连接(*m这, *m头);
	m头->m标志[e环形头部] = true;
}
C连续子弹::C环形工具 &C连续子弹::C环形工具::operator +=(const std::shared_ptr<C连续子弹> &a) {
	if (a != nullptr) {	//达到子弹上限时可能有空指针
		if (m这) {
			mf连接(*m这, *a);
		} else {
			m头 = a;
		}
		m这 = a;
	}
	return *this;
}
//==============================================================================
// 扩展-连续子弹
//==============================================================================
std::mutex C连续子弹::m连接互斥;
C连续子弹::C连续子弹(const C连续子弹 &a前, const C连续子弹 &a后, float a插值) {
}
void C连续子弹::f接口_初始化() {
	m出现.f初始化();
	m消失.f初始化();
}
void C连续子弹::f接口_销毁() {
	std::lock_guard<std::mutex> v锁(m连接互斥);
	m前 = nullptr;
	m后 = nullptr;
}
void C连续子弹::f接口_计算() {
	auto vi窗口外 = m标志[e窗口外];
	//运动
	f基础_计算运动();
	f基础_计算方向();
	vi窗口外 = C边界::c窗口.f外边判断(m坐标, m子弹属性->fg显示x(m缩放.x));
	//渐变&消失
	m出现.f计算();
	if (m消失.fi消失()) {
		m消失.f计算();
		if (m消失.fi已经消失()) {
			auto f消失判断 = [this](C连续子弹 *a连接)->bool {
				if (a连接) {
					return a连接->m消失.fi已经消失();
				} else {
					return true;
				}
			};
			const bool v前消失 = f消失判断(m前.get());
			const bool v后消失 = f消失判断(m后.get());
			if (v前消失 && v后消失) {
				f对象_销毁();
			}
			return;
		}
	}
}
void C连续子弹::f接口_更新() {
	//清除连接关系
	if (m后 && !m后->f对象_i使用()) {
		std::lock_guard<std::mutex> v锁(m连接互斥);
		m后 = nullptr;
	}
	if (m前 && !m前->f对象_i使用()) {
		std::lock_guard<std::mutex> v锁(m连接互斥);
		m前 = nullptr;
	}
	if (m前 == nullptr) {
		m标志[e环形头部] = false;
	}
	if (!f接口_可显示()) {
		return;
	}
	//准备绘制
	const bool vi环 = m标志[e环形头部];
	if (m后) {	//连续子弹
		C子弹顶点::C曲线::ta顶点 va原始顶点;
		//后面的子弹
		const C连续子弹 *vp这 = this;
		while (true) {
			C子弹顶点::C曲线::t顶点 v原始顶点;
			v原始顶点.m坐标 = vp这->m坐标;
			v原始顶点.m消失 = vp这->m消失.m帧;
			va原始顶点.push_back(v原始顶点);
			//取后节点
			std::lock_guard<std::mutex> v锁(m连接互斥);
			const C连续子弹 *vp后 = vp这->m后.get();
			//结束条件
			if (vp后 == this) {	//一圈了
				assert(vi环);	//成环时只有头部能显示,其它部位显示时会触发断言
				break;
			}
			if (vp后 == nullptr) {
				break;
			}
			if (!vp后->f对象_i使用()) {
				break;
			}
			//继续循环
			vp这 = vp后;
		}
		//
		C子弹顶点::C曲线 v子弹顶点{this, (signed)va原始顶点.size()};
		v子弹顶点.m标志[C子弹顶点::e环] = vi环;
		v子弹顶点.m中心.m出现 = m出现.m帧;
		m图形数据 = m绘制->f生成连续点(v子弹顶点, va原始顶点);
	} else {	//单个子弹
		C子弹顶点::C点 v子弹顶点{this};
		v子弹顶点.m中心.m出现 = m出现.m帧;
		v子弹顶点.m中心.m消失 = 0;
		m图形数据 = m绘制->f生成点(v子弹顶点);
	}
}
void C连续子弹::f接口_显示() const {
	m绘制->f绘制图形数据(m图形数据);
}
void C连续子弹::f接口_自机判定(C自机与子弹判定 &a判定) {
	if (m消失.fi正在消失()) {
		return;
	}
	if (f基础_i不透明判定()) {
		return;
	}
	//子弹自身的判定区域总是圆形
	const float v判定半径 = m子弹属性->fg判定x(m缩放.x);
	const t圆形 v圆形{m坐标, v判定半径};
	if (a判定.f子弹_提交判定(v圆形)) {
		a判定.f子弹_判定有效();
		if (a判定.f子弹_i碰撞()) {
			f扩展_自动细分();
			m消失.f消失();
			return;
		}
	}
	//计算连续子弹之间的判定区域
	if (m后) {
		auto &v后消失 = m后->m消失;
		if (v后消失.fi正在消失()) {
			return;
		}
		const t旋转矩形 v矩形 = t旋转矩形::fc线段(m坐标, m后->m坐标, v判定半径);
		if (a判定.f子弹_提交判定(v矩形)) {
			a判定.f子弹_判定有效();
			if (a判定.f子弹_i碰撞()) {
				if (m坐标.f到点距离(m后->m坐标) > f扩展_g细分间隔()) {
					//进行细分
					C连续子弹 *const va后 = m后.get();	//细分之前的后指针
					f扩展_自动细分();
					m后->f扩展_自动细分();
					C连续子弹 *vp这 = this;	//细分后的后指针
					//计算细分后子弹的判定
					while (vp这 != va后) {
						const t圆形 v圆形{vp这->m坐标, v判定半径};
						if (a判定.f子弹_提交判定(v圆形)) {
							if (a判定.f子弹_i碰撞()) {
								vp这->m消失.f消失();
								break;
							}
						}
						C连续子弹 *const va后 = vp这->m后.get();
						const t旋转矩形 v矩形 = t旋转矩形::fc线段(vp这->m坐标, va后->m坐标, v判定半径);
						if (a判定.f子弹_提交判定(v矩形)) {
							if (a判定.f子弹_i碰撞()) {
								vp这->m消失.f消失();
								va后->m消失.f消失();
								break;
							}
						}
						vp这 = va后;
					}
				} else {
					m消失.f消失();
					v后消失.f消失();
				}
			}
		}
	}
}
bool C连续子弹::f接口_i在窗口外() {
	if (m标志[e窗口外]) {
		auto f窗口外 = [](C连续子弹*a)->bool {
			if (a) {
				return a->m标志[e窗口外];
			} else {
				return true;
			}
		};
		const bool vi前 = f窗口外(m前.get());
		const bool vi后 = f窗口外(m后.get());
		return vi前 && vi后;
	} else {
		return false;
	}
}
bool C连续子弹::f接口_可显示() const {
	if (m前) {	//有前节点时,只有头部才能渲染子弹
		if (m标志[e环形头部]) {
			return f扩展_i环();
		} else {
			return false;
		}
	} else {
		return true;
	}
}
bool C连续子弹::f接口_炸弹判定(C子弹与玩家炸弹判定 &a判定) {
	if (m消失.fi消失()) {
		return false;
	}
	if (a判定.f子弹_提交判定(m坐标, m子弹属性->fg判定x())) {
		a判定.f子弹_产生道具(m坐标, m速度);
		f动作_消失(true);
		return true;
	}
	return false;
}
//动作
void C连续子弹::f动作_消失(bool a) {
	if (a) {
		m消失.f消失();
	} else {
		f对象_销毁();
	}
}
//扩展
std::shared_ptr<C连续子弹> C连续子弹::fg这指针() const {
	return m这.lock();
}
bool C连续子弹::f扩展_i环() const {
	const C连续子弹 *vp这 = this;
	while (vp这) {
		const C连续子弹 *va前 = vp这->m前.get();
		if (va前 == this) {
			return true;
		}
		vp这 = va前;
	}
	return false;
}
void C连续子弹::f扩展_自动细分() {
	if (!mf细分) {
		return;
	}
	auto f细分 = [v判定直径乘二 = f扩展_g细分间隔()](C连续子弹 &a前, C连续子弹 &a后) {
		const float v距离 = a前.m坐标.f到点距离(a后.m坐标);
		const int v数量 = (int)(v距离 / v判定直径乘二);
		if (v数量 > 0) {
			f连续子弹_细分0(a前, a后, v数量);
		}
	};
	if (m前) {
		f细分(*m前, *this);
	}
	if (m后) {
		f细分(*this, *m后);
	}
}
float C连续子弹::f扩展_g细分间隔() const {
	return m子弹属性->fg判定x() * 4;
}
//外部
std::shared_ptr<C连续子弹> C连续子弹::f连续子弹_c细分(C连续子弹 &a前, C连续子弹 &a后, float a插值) {
	return std::make_shared<C连续子弹>(a前, a后, a插值);
}
void C连续子弹::f连续子弹_连接0(C连续子弹 &a子弹0, C连续子弹 &a子弹1) {
	assert(!a子弹0.m后);	//必需是空指针
	assert(!a子弹1.m前);
	f连续子弹_连接1(a子弹0, a子弹1);
}
void C连续子弹::f连续子弹_断开0(C连续子弹 &a子弹0, C连续子弹 &a子弹1) {
	//assert(a子弹0.m后 == a子弹1);
	//assert(a子弹1.m前 == a子弹0);
	f连续子弹_断开1(a子弹0, a子弹1);
}
void C连续子弹::f连续子弹_细分0(C连续子弹 &a前, C连续子弹 &a后, int a数量) {
	assert(a数量 > 0);
	C子弹制造机 v子弹制造机 = C游戏::fg内容().f工厂_子弹();
	v子弹制造机.m参数.fs子弹基础(a前);
	C连接工具 v连续{f连续子弹_连接1};
	v连续 += a前.fg这指针();
	for (auto v循环0 : v子弹制造机.f循环(a数量)) {
		const float v计算 = v循环0.f计算(C循环计算::fc插值(false, false));
		v循环0.f变换_坐标插值(a后.m坐标, v计算);
		v循环0.f变换_速度平滑插值(a后.m速度, v计算);
		if (v子弹制造机.f实现_i有空()) {
			std::shared_ptr<C连续子弹> v新扩展 = a前.mf细分(a前, a后, v计算);
			v子弹制造机.f实现_产生子弹(v新扩展);
			v连续 += v新扩展;
			v新扩展->mf细分 = a前.mf细分;
		}
	}
	v连续 += a后.fg这指针();
}
void C连续子弹::f连续子弹_连接1(C连续子弹 &a子弹0, C连续子弹 &a子弹1) {
	std::lock_guard<std::mutex> v锁(m连接互斥);
	a子弹0.m后 = a子弹1.fg这指针();
	a子弹1.m前 = a子弹0.fg这指针();
}
void C连续子弹::f连续子弹_断开1(C连续子弹 &a子弹0, C连续子弹 &a子弹1) {
	std::lock_guard<std::mutex> v锁(m连接互斥);
	a子弹0.m后 = nullptr;
	a子弹1.m前 = nullptr;
}
}