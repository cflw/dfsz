export module 东方山寨.图形.对话框;
export import "游戏常量.h";
export import "边框常量.h";
export import "图形包含.h";
export import "数学包含.h";
export import "图形基础.h";
export import "图形缓冲.h";
export import 东方山寨.对话基础;
import "图形工厂.h";
import "游戏.h";
export namespace 东方山寨 {
//每句话都是一个对话框对象
class C对话框 : public I图形 {
public:
	static constexpr float c渐变速度 = 4;
	static constexpr float c边框 = 12;
	static constexpr float c开始位置x = c边框范围x - 32;
	static constexpr float c开始位置y = -96;	//对话框顶部坐标,在立绘中心坐标下面
	static constexpr float c对话框透明度 = 0.8f;
	static constexpr float c字号 = 二维::ca中文字号[二维::E中文字号::e三号];
	class C图形缓冲 : public I图形缓冲 {
	public:
		void f显示() const override;
		二维::tp画图形 m画图形;
		二维::tp画文本 m画文本;
		二维::tp文本布局 m文本布局;
		二维::tp路径几何 m三角形;
		t圆角矩形 m方框矩形;
		t向量2 m文本坐标;	//中心坐标
	};
	using t图形缓冲 = C图形缓冲;
	C对话框(const S对话参数_对话 &);
	void f接口_初始化(const S图形参数 &) override;
	void f接口_计算() override;
	void f接口_更新() override;
	bool f接口_i可销毁() const override;
private:
	t向量2 m实际尺寸;
	t向量2 m显示尺寸;
	S对话参数_对话 m参数;
	float m出现 = 0;
};
}	//namespace 东方山寨
module: private;
namespace 东方山寨 {
//==============================================================================
// 对话框
//==============================================================================
C对话框::C对话框(const S对话参数_对话 &a) {
	m参数 = a;
}
void C对话框::f接口_初始化(const S图形参数 &a参数) {
	C图形缓冲 *const v缓冲 = static_cast<C图形缓冲 *>(m图形缓冲);
	auto &v二维 = C游戏::fg图形().fg二维();
	v缓冲->m画图形 = v二维.fc画图形(v二维.fc纯色画笔(t颜色::c黑));
	v缓冲->m画文本 = v二维.fc画文本();
	v缓冲->m画文本->fs颜色(t颜色::c白);
	auto &v文本工厂 = v二维.fg文本工厂();
	二维::S文本格式参数 v文本格式参数;
	v文本格式参数.fs字号(c字号);
	v文本格式参数.fs垂直对齐(二维::E文本垂直对齐::e中);
	v文本格式参数.fs水平对齐(二维::E文本水平对齐::e中);
	v缓冲->m文本布局 = v文本工厂.fc文本布局(m参数.m文本, v文本格式参数);
	//计算文本度量
	DWRITE_TEXT_METRICS v文本度量;
	v缓冲->m文本布局->GetMetrics(&v文本度量);
	m实际尺寸.x = v文本度量.width + c边框 * 2;
	m实际尺寸.y = v文本度量.height + c边框 * 2;
	v缓冲->m方框矩形.m角半径 = {c边框, c边框};
}
void C对话框::f接口_计算() {
	const float v过秒 = C游戏::fg内容().fg游戏速度().fg秒();
	if (m标志[I图形::E标志::e结束]) {
		m出现 -= c渐变速度 * v过秒;
	} else {
		m出现 = 数学::f线性渐变<float>(m出现, 1, c渐变速度 * v过秒);
	}
}
void C对话框::f接口_更新() {
	C图形缓冲 *const v缓冲 = static_cast<C图形缓冲 *>(m图形缓冲);
	//透明度
	v缓冲->m画图形->fs透明度(m出现 * c对话框透明度);
	v缓冲->m画文本->fs透明度(m出现);
	//位置
	m显示尺寸.x = 数学::f插值<float>(0, m实际尺寸.x, m出现);
	m显示尺寸.y = m实际尺寸.y;
	const bool vi从右向左 = m参数.m方向 == E对话方向::e从右向左;
	const float v左 = vi从右向左 ? (c开始位置x - m显示尺寸.x) : (-c开始位置x);
	const float v右 = vi从右向左 ? (c开始位置x) : (-c开始位置x + m显示尺寸.x);
	const float v上 = c开始位置y;
	const float v下 = c开始位置y - m实际尺寸.y;
	v缓冲->m方框矩形 = t圆角矩形::fc左上右下(v左, v上, v右, v下, {c边框, c边框});
	v缓冲->m画文本->fs区域(v缓冲->m方框矩形.m坐标);
}
bool C对话框::f接口_i可销毁() const {
	return m标志[I图形::E标志::e结束] && m出现 <= 0;
}
void C对话框::C图形缓冲::f显示() const {
	//画图形
	m画图形->f填充圆角矩形(m方框矩形);
	//画文本
	m画文本->f绘制文本布局(m文本布局.Get());
}
}	//namespace 东方山寨