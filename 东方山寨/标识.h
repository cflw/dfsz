#pragma once
namespace 东方山寨 {
namespace 计算 {
constexpr int f标识(int a, int a大, int a小) {
	return a + a大 + (a小 << 16);
}
int fc随机标识();	//为了避免撞车,实际上并不随机
}	//namespace 计算
//上限
constexpr int c标识上限 = 2147483647;	//0x7fffffff
//常量
constexpr int c子弹标识 = 1329182951;//0x4f39b8e7
constexpr int c子弹扩展标识 = 1208143544;//0x4802ceb8
constexpr int c画子弹标识 = 1321863430;	//0x4eca0906
constexpr int c子弹纹理标识 = 487792821;	//0x1d1320b5
constexpr int c自机标识 = 670299935;	//0x27f3f71f
constexpr int c内置动画标识 = 0;
constexpr int c动画标识 = 358166379;	//0x15592f6b
constexpr int c子机标识 = 744384505;	//0x2c5e67f9
constexpr int c子机移动标识 = 916599177;	//0x36A23189
constexpr int c玩家子弹标识 = 1642107557;	//0x61e092a5
constexpr int c玩家炸弹标识 = 1792698507;	//0x6ada688b
constexpr int c玩家发射标识 = 1096709819;	//0x415e76bb
constexpr int c玩家图形 = 1950318609;	//0x743f8011
constexpr int c敌机标识 = 660212840;	//0x275a0c68
constexpr int c飞机顶点标识 = 1937597986;	//0x737d6622
constexpr int c道具标识 = 190639115;	//0x0b5cec0b
constexpr int c效果标识 = 573865576;	//0x22347e68
constexpr int c模型标识 = 502188807;	//0x1deecb07
constexpr int c纹理标识 = 1776032171;	//0x69dc19ab
enum class E子弹 {
	e大光弹 = c子弹标识,
	e环圆弹,
	e激光,
	e米弹,
	e鳞弹,
	e曲线激光
};
enum class E画子弹 {
	e正常 = c画子弹标识,
	e高光,
	e线条,
};
enum class E纹理 {
	e空 = 0,
	e测试 = 1,
	e子弹0 = c子弹纹理标识,	//bullet16x16_00.bmp
};
enum class E子弹扩展 {
	e测试子弹 = c子弹扩展标识,
	e普通子弹,
	e直线激光,
	e曲线激光,
	e大子弹,
	e连续子弹,
	e射线激光,
};
enum class E自机 {
	e测试 = c自机标识,
	e灵梦,
	e魔理沙,
};
enum class E顶点 {
	e自机 = c飞机顶点标识,
	e子机,
	e敌机0
};
enum class E动画 {
	e静态 = c内置动画标识,
	e道具0,
	e道具,
	e自机 = c动画标识,
	e敌机,
};
enum class E子机 {
	e测试 = c子机标识 - 1,
	e灵梦集中,
	e灵梦诱导,
	e魔理沙贯穿,
	e魔理沙范围,
};
enum class E子机移动 {
	e位置 = c子机移动标识,
};
enum class E玩家子弹 {
	e测试子弹 = c玩家子弹标识,
	e灵梦基础,
	e魔理沙基础,
	e灵梦诱导,
	e灵梦集中,
	e魔理沙贯穿,
	e魔理沙范围,
};
enum class E玩家炸弹 {
	e普通 = c玩家炸弹标识,
	e全屏清弹,
};
enum class E玩家发射 {
	//子弹
	e测试子弹 = c玩家发射标识 - 1,
	e自机基础,
	e灵梦集中,
	e灵梦诱导,
	e魔理沙贯穿,
	e魔理沙范围,
	//炸弹
	e全屏清弹,
	e测试炸弹,
};
enum class E敌机 {
	e测试 = c敌机标识,
	e敌机00蓝
};
enum class E道具 {
	e残机 = c道具标识,
	e残机碎片,
	e炸弹,
	e炸弹碎片,
	e火力,
	e得点,
	e最大点,
	e微最大点,
};
enum class E图形 {
	e效果0 = c效果标识,
	e道具0 = c道具标识,
	e道具1
};
enum class E模型 {
	e测试平面 = 1
};
}	//namespace 东方山寨