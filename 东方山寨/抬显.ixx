export module 东方山寨.抬显;
import "游戏常量.h";
import "游戏.h";
import 东方山寨.关卡;
export namespace 东方山寨 {
class C抬显控制 {
public:
	static constexpr float c渐变速度 = c帧秒<float> *4;
	void f计算();
	float fg总透明度() const;	//只能由抬显调用,对话和立绘不要调用
	static float fg全局透明度();	//返回 C游戏::fg内容().fg抬显控制().fg总透明度();
public:
	float m对话渐变 = 0;
};
}	//namespace 东方山寨
module: private;
namespace 东方山寨 {
void C抬显控制::f计算() {
	C关卡控制 &v关卡 = C游戏::fg内容().fg关卡控制();
	const float v对话渐变目标 = v关卡.fi对话() ? 1 : 0;
	m对话渐变 = 数学::f线性渐变(m对话渐变, v对话渐变目标, c渐变速度);
}
float C抬显控制::fg总透明度() const {
	return 1 - m对话渐变;
}
float C抬显控制::fg全局透明度() {
	return C游戏::fg内容().fg抬显控制().fg总透明度();
}
}	//namespace 东方山寨