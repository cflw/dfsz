module;
#include "图形包含.h"
#include "图形基础.h"
#include "图形缓冲.h"
#include "边框常量.h"
#include "游戏.h"
#include "图形引擎.h"
#include "图形_抬显.h"
export module 东方山寨.图形_关卡标题;
import 东方山寨.抬显;
export namespace 东方山寨 {
struct S关卡标题 {
	std::wstring m标题;
	std::wstring m场景;
};
class C关卡标题 : public I粒子 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		二维::tp文本布局 m布局;
		float m透明度;
	};
	static constexpr float c大字号 = 二维::ca中文字号[二维::e初号];
	static constexpr float c小字号 = 二维::ca中文字号[二维::e五号];
	using t图形缓冲 = C图形缓冲;
	C关卡标题(const S关卡标题 &);
	void f接口_初始化(const S图形参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
private:
	S关卡标题 m标题;
};
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
C关卡标题::C关卡标题(const S关卡标题 &a) :
	m标题(a) {
}
void C关卡标题::f接口_初始化(const S图形参数 &a) {
	I粒子::f接口_初始化(a);
	//格式
	auto &v文本工厂 = C游戏::fg图形().fg文本工厂();
	二维::S文本格式参数 v文本格式;
	v文本格式.m字体 = c文本字体;
	v文本格式.m字号 = c大字号;
	v文本格式.m水平对齐 = DWRITE_TEXT_ALIGNMENT_CENTER;
	//文本
	const std::wstring v文本 = m标题.m标题 + L"\n" + m标题.m场景;
	//创建布局
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	v图形缓冲.m布局 = v文本工厂.fc文本布局(v文本, v文本格式);
	v图形缓冲.m布局->SetFontSize(c小字号, {(UINT32)m标题.m标题.size(), (UINT32)m标题.m场景.size() + 1});
}
void C关卡标题::f接口_计算() {
	f计算_生命();
}
void C关卡标题::f接口_更新() {
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	v图形缓冲.m透明度 = 数学::f等腰梯形插值<float>(0, 1, 1.f / m寿命, fg生命百分比()) * C抬显控制::fg全局透明度();
}
//图形缓冲
void C关卡标题::C图形缓冲::f显示() const {
	auto &v画文本 = C游戏::fg图形().fg画文本();
	v画文本.fs区域(t向量2{0, 100});
	v画文本.fs颜色(t颜色::c白);
	v画文本.fs透明度(m透明度);
	v画文本.f绘制文本布局(m布局.Get());
}
}	//namespace 东方山寨