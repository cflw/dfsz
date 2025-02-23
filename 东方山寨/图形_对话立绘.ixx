export module 东方山寨.图形.对话立绘;
export import "边框常量.h";
export import "基础.h";
export import "图形包含.h";
export import "图形建造机.h";
export import 东方山寨.对话基础;
import "游戏.h";
import "图形引擎.h";
import "图形工厂.h";
export namespace 东方山寨 {
//==============================================================================
// 对话立绘
//==============================================================================
class I对话立绘 : public I图形 {
public:
	enum E初始化标志 {
		e方向,
	};
	enum E标志 {
		e焦点 = I图形::E标志::e自定义,
	};
	static constexpr float c立绘位置x = c边框范围x - 32;
	static constexpr float c立绘位置y = -75;	//中心
	static constexpr float c动画速度 = 4;	//0.25秒完成
	//接口
	void f接口_初始化(const S图形参数 &) override;
	void f接口_计算() override;
	bool f接口_i可销毁() const override;
	virtual void f接口_改变表情(E立绘表情);
	//属性
	t向量2 fg显示坐标() const;
	float fg显示透明度() const;
	//动作
	void f动作_表情(E立绘表情);	//调用f接口_改变表情
	void f动作_聚焦();
	void f动作_失焦();
protected:
	t向量2 m坐标;	//立绘位置
	float m出现 = 0;
	float m焦点 = 0;	//如果说话者是当前立绘,为1
	E对话方向 m方向 = E对话方向::e从左向右;	//同对话框
};
//方框,用来测试
class C对话立绘_空 : public I对话立绘 {
public:
	class C图形缓冲 : public I图形缓冲 {	//画个白色矩形
	public:
		void f显示() const override;
		二维::tp画图形 m画图形;
		t矩形 m矩形;
	};
	using t图形缓冲 = C图形缓冲;
	void f接口_初始化(const S图形参数 &) override;
	void f接口_更新() override;
};
using C空白立绘建造机 = C图形建造机<C对话立绘_空, C对话立绘_空::C图形缓冲>;
}	//namespace 东方山寨
module: private;
namespace 东方山寨 {
//==============================================================================
// 对话立绘接口
//==============================================================================
void I对话立绘::f接口_初始化(const S图形参数 &a参数) {
	const bool vi从右向左 = a参数.m标志[E初始化标志::e方向];
	m方向 = vi从右向左 ? E对话方向::e从右向左 : E对话方向::e从左向右;
	m坐标.x = vi从右向左 ? c立绘位置x : -c立绘位置x;
	m坐标.y = c立绘位置y;
}
void I对话立绘::f接口_计算() {
	const float v过秒 = C游戏::fg内容().fg游戏速度().fg秒();
	const float v速度 = v过秒 * c动画速度;
	const float v出现目标 = m标志[I图形::E标志::e结束] ? 0.f : 1.f;
	m出现 = 数学::f线性渐变<float>(m出现, v出现目标, v速度);
	const float v焦点目标 = m标志[I对话立绘::E标志::e焦点] ? 1.f : 0.f;
	m焦点 = 数学::f线性渐变<float>(m焦点, v焦点目标, v速度);
}
bool I对话立绘::f接口_i可销毁() const {
	return m标志[I图形::E标志::e结束] && m出现 <= 0;
}
void I对话立绘::f接口_改变表情(E立绘表情) {
}
t向量2 I对话立绘::fg显示坐标() const {
	return {m坐标.x * std::lerp(1.25f, 1.f, m出现), m坐标.y};
}
float I对话立绘::fg显示透明度() const {
	return std::min<float>(m出现, 数学::f插值<float>(0.8f, 1.f, m焦点));
}
void I对话立绘::f动作_表情(E立绘表情 a) {
	this->f接口_改变表情(a);
}
void I对话立绘::f动作_聚焦() {
	m标志[I对话立绘::E标志::e焦点] = true;
}
void I对话立绘::f动作_失焦() {
	m标志[I对话立绘::E标志::e焦点] = false;
}
//==============================================================================
// 空白立绘
//==============================================================================
void C对话立绘_空::f接口_初始化(const S图形参数 &a参数) {
	I对话立绘::f接口_初始化(a参数);
	C图形缓冲 *const v缓冲 = static_cast<C图形缓冲 *>(m图形缓冲);
	v缓冲->m画图形 = C游戏::fg图形().fc画图形();
	v缓冲->m矩形.m坐标 = m坐标;
	v缓冲->m矩形.m半尺寸 = {64, 64};
}
void C对话立绘_空::f接口_更新() {
	C图形缓冲 *const v缓冲 = static_cast<C图形缓冲 *>(m图形缓冲);
	const float v灰 = 数学::f插值<float>(0.5f, 1.f, m焦点);
	const float v透明 = std::min<float>(m出现, 数学::f插值<float>(0.8f, 1.f, m焦点));
	v缓冲->m画图形->fs颜色(数学::S颜色::fc黑白(v灰, v透明));
}
void C对话立绘_空::C图形缓冲::f显示() const {
	m画图形->f填充矩形(m矩形);
}
}	// namespace 东方山寨