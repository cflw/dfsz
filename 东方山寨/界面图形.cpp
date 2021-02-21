#include "界面图形.h"
#include "游戏.h"
#include "图形引擎.h"
#include "图形_图片.h"
#include "图形_背景.h"
#include "图形管理.h"
#include "边框常量.h"
#include "图形_背景.h"
namespace 东方山寨 {
//==============================================================================
// 界面图形
//==============================================================================
namespace 界面图形 {
//基础
template<typename t>
bool fi使用(const std::shared_ptr<t> &a) {
	return a && a->f对象_i使用();
}
class C消失 {
public:
	static constexpr float c消失速度 = 2;
	void f计算_消失(float a过秒) {
		m透明度 += (m消失 ? -1 : 1) * a过秒 * c消失速度;
		m透明度 = 数学::f夹取<float>(m透明度, 0, 1);
	}
	bool fi已消失() const {
		return m消失 && (m透明度 <= 0);
	}
	void f消失() {
		m消失 = true;
	}
	void f不消失() {
		m消失 = false;
	}
	float m透明度 = 0;
	bool m消失 = false;
};
//类
class C标题人物 : public C二维图片图形, public C消失 {
public:
	C标题人物() {
		m缩放 = t向量2::fc相同(0.4f);
	}
	void f接口_计算() override {
		const float v过秒 = m游戏速度->fg秒();
		f计算_生命();
		//const float v目标x = m生命 < 1 ? 
		//	数学::f插值<float>(c屏幕范围x, 0, m生命) :
		//	0;
		const t向量2 v抖动 = {sin(m生命 * 0.6f) * 10, sin(m生命 * 0.5f) * 10};
		m目标 = /*t向量2{v目标x, 0} + */v抖动;
		m速度 = m目标 - m坐标;
		f计算_运动();
		f计算_消失(v过秒);
	}
	bool f接口_i可销毁() const override {
		return fi已消失();
	}
	float f接口_g透明度() const override {
		return m透明度;
	}
	t向量2 m目标;
};
class C云 : public C二维图片图形, public C消失 {
public:
	static constexpr float c边 = 128;
	static constexpr float c左边 = -c框架范围x - c边;
	static constexpr float c右边 = c框架范围x + c边;
	static constexpr float c层分界线 = -c框架范围y * 0.5f;
	C云() {
		m缩放 = t向量2::fc相同(2);
	}
	void f接口_计算() override {
		const float v过秒 = m游戏速度->fg秒();
		f计算_生命();
		f计算_运动();
		if (m坐标.x >= c右边) {
			m坐标.x = c左边;
		}
		f计算_消失(v过秒);
	}
	bool f接口_i可销毁() const override {
		return fi已消失();
	}
	float f接口_g透明度() const override {
		return 0.05f * m透明度;
	}
};
}	//namespace 界面图形
//==============================================================================
// 界面图形控制
//==============================================================================
C界面图形控制::C界面图形控制() {

}
C界面图形控制::~C界面图形控制() {

}
void C界面图形控制::f计算() {
	const float v云加 = (m标志[e云] ? 1 : -1) * c帧秒<float> * 4;
	const float v云透明度 = m云透明度 + v云加;
	m云透明度 = 数学::f夹取<float>(v云透明度, 0, 1);
}
void C界面图形控制::f关闭图形() {
	f背景(false);	//缺乏过渡，以后修改
	f标题人物(false);
	f云(false);
}
void C界面图形控制::f背景(bool a) {
	if (a) {
		if (m背景 == nullptr) {
			const S纹理 *const v纹理 = C游戏::fg图形().fg纹理()[L"东方月亮船.背景"];
			m背景 = 图形模板::f全屏静态背景(*v纹理);
		}
	} else {
		if (m背景) {
			m背景->f动作_结束();
			m背景 = nullptr;
		}
	}
}
void C界面图形控制::f标题人物(bool a) {
	if (a) {
		if (!界面图形::fi使用(m标题人物)) {
			auto v图形工厂 = C游戏::fg资源().f工厂_图形();
			v图形工厂.m参数.m纹理 = C游戏::fg图形().fg纹理()[L"东方月亮船.灵梦"];
			v图形工厂.m参数.m顶点 = C游戏::fg图形().fg顶点矩形()[L"东方月亮船.灵梦"];
			v图形工厂.m参数.m坐标 = t向量2(c框架范围x, 0);
			v图形工厂.m参数.m图层 = E图层::e人;
			m标题人物 = v图形工厂.f产生图形<界面图形::C标题人物>();
		} else {
			m标题人物->f不消失();
		}
	} else if (界面图形::fi使用(m标题人物)) {
		m标题人物->f消失();
	}
}
void C界面图形控制::f云(bool a) {
	if (a) {
		auto v图形工厂 = C游戏::fg资源().f工厂_图形();
		auto v随机工厂 = C游戏::fg资源().f工厂_随机数引擎();
		const std::uniform_real_distribution<float> c坐标分布x{界面图形::C云::c左边,  界面图形::C云::c右边};
		const std::uniform_real_distribution<float> c坐标分布y{-c框架范围y, 0};
		const std::uniform_real_distribution<float> c速度分布x{100, 200};
		v图形工厂.m参数.m纹理 = C游戏::fg图形().fg纹理()[L"东方月亮船.云"];
		const S顶点矩形 *vp云矩形 = C游戏::fg图形().fg顶点矩形()[L"东方月亮船.云"];
		int i = 0;
		for (auto &vp云 : ma云) {
			if (!界面图形::fi使用(vp云)) {
				v图形工厂.m参数.m顶点 = vp云矩形 + i;
				v图形工厂.m参数.m坐标.x = c坐标分布x(v随机工厂);
				v图形工厂.m参数.m坐标.y = c坐标分布y(v随机工厂);
				v图形工厂.m参数.m速度.x = c速度分布x(v随机工厂);
				const int v图层 = v图形工厂.m参数.m坐标.y > 界面图形::C云::c层分界线 ? E图层::e后云 : E图层::e前云;
				v图形工厂.m参数.m图层 = v图层;
				vp云 = v图形工厂.f产生图形<界面图形::C云>();
				i = (i + 1) % 8;
			} else {
				vp云->f不消失();
			}
		}
	} else {
		for (auto &vp云 : ma云) {
			if (fi使用(vp云)) {
				vp云->f消失();
			}
		}
	}
}
}	//namespace 东方山寨