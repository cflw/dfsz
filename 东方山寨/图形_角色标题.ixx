export module 东方山寨.图形.角色标题;
export import "图形包含.h";
export import "图形基础.h";
export import "图形缓冲.h";
import "游戏.h";
import "图形引擎.h";
import "图形工厂.h";
import 东方山寨.抬显;
import 东方山寨.图形.抬显;
export namespace 东方山寨 {
struct S角色标题 {
	std::wstring m名称;
	std::wstring m称号;
};
class C角色标题 : public I粒子 {
public:
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		二维::tp文本布局 m布局;
		t向量2 m坐标;
		float m透明度;
	};
	static constexpr float c大字号 = 二维::ca中文字号[二维::e二号];
	static constexpr float c小字号 = 二维::ca中文字号[二维::e五号];
	using t图形缓冲 = C图形缓冲;
	C角色标题(const S角色标题 &);
	void f接口_初始化(const S图形参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
private:
	S角色标题 m标题;
};
namespace 图形模板 {
std::shared_ptr<C角色标题> f角色标题(const t向量2 &坐标, const S角色标题 &角色标题);
}	//namespace 图形模板
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
C角色标题::C角色标题(const S角色标题 &a):
	m标题(a) {
}
void C角色标题::f接口_初始化(const S图形参数 &a) {
	I粒子::f接口_初始化(a);
	//格式
	auto &v文本工厂 = C游戏::fg图形().fg文本工厂();
	二维::S文本格式参数 v文本格式;
	v文本格式.m字体 = c文本字体;
	v文本格式.m字号 = c大字号;
	v文本格式.m水平对齐 = DWRITE_TEXT_ALIGNMENT_CENTER;
	//文本
	const std::wstring v文本 = m标题.m称号 + L"\n" + m标题.m名称;
	//创建布局
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	v图形缓冲.m布局 = v文本工厂.fc文本布局(v文本, v文本格式);
	v图形缓冲.m布局->SetFontSize(c小字号, {0, (UINT32)m标题.m称号.size() + 1});
}
void C角色标题::f接口_计算() {
	f计算_生命();
}
void C角色标题::f接口_更新() {
	auto &v图形缓冲 = static_cast<C图形缓冲 &>(*m图形缓冲);
	v图形缓冲.m坐标 = m坐标;
	v图形缓冲.m透明度 = fg渐变(0.5f);
}
//图形缓冲
void C角色标题::C图形缓冲::f显示() const {
	auto &v画文本 = C游戏::fg图形().fg画文本();
	v画文本.fs区域(m坐标);
	v画文本.fs颜色(t颜色::c白);
	v画文本.fs透明度(m透明度);
	v画文本.f绘制文本布局(m布局.Get());
}
namespace 图形模板 {
std::shared_ptr<C角色标题> f角色标题(const t向量2 &a坐标, const S角色标题 &a角色标题) {
	const auto &v图形工厂 = C游戏::fg资源().f工厂_图形();
	t图形参数 v参数 = t图形参数::c游戏中;
	v参数.m坐标 = a坐标;
	v参数.m寿命 = 5;
	v参数.m图层 = (int)E图层::e对话;	//放在立绘前面
	return v图形工厂.f产生图形<C角色标题>(v参数, a角色标题);
}
}	//namespace 图形模板
}	//namespace 东方山寨