module;
#include <functional>
#include "图形基础.h"
#include "图形_图片.h"
#include "图形工厂.h"
export module 东方山寨.图形_符卡立绘;
export namespace 东方山寨 {
//==============================================================================
// 图形
//==============================================================================
class C符卡立绘 : public I图形 {
public:
	static constexpr float c最大透明度 = 0.8f;
	static constexpr float c显示时间 = 3.f;
	using tf显示参数 = std::function<S动画缓冲(float)>;
	using t图形缓冲 = C图片动画图形缓冲;
	C符卡立绘(tf显示参数 af显示参数, float a寿命 = c显示时间):
		mf显示参数(af显示参数),
		m寿命(a寿命) {
	}
	void f接口_计算() override {
		m时间 += m游戏速度->fg秒();
	}
	void f接口_更新() override {
		t图形缓冲 *const v缓冲 = static_cast<t图形缓冲 *>(m图形缓冲);
		*v缓冲 = mf显示参数(m时间 / m寿命);
	}
	void f接口_初始化(const S图形参数 &a参数) override {
		t图形缓冲 *const v缓冲 = static_cast<t图形缓冲 *>(m图形缓冲);
		v缓冲->m纹理 = a参数.m纹理.m指针;
		v缓冲->m顶点 = a参数.m顶点.m指针;
	}
	bool f接口_i可销毁() const override {
		return m时间 >= m寿命;
	}
private:
	float m时间 = 0;
	float m寿命 = 0;
	tf显示参数 mf显示参数;
};
}	//namespace 东方山寨