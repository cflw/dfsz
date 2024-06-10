#pragma once
#include "游戏.h"
#include "基础.h"
//子弹
#include "标识.h"
#include "子弹基础.h"
#include "子弹制造机.h"

#include "子弹_普通子弹.h"
#include "子弹_直线激光.h"
#include "子弹_曲线激光.h"
#include "子弹_大子弹.h"
#include "子弹_连续子弹.h"
#include "子弹_射线激光.h"
//敌机
#include "敌机基础.h"
#include "敌机制造机.h"
#include "敌机扩展.h"
#include "敌机模板.h"
//道具
#include "道具.h"
#include "道具制造机.h"
//遮罩
#include "遮罩基础.h"
#include "遮罩形状.h"
#include "遮罩工厂.h"
#include "边框形状.h"
//图形
#include "图形工厂.h"
#include "敌机图形模板.h"
#include "图形_抬显.h"
#include "图形_三维.h"
#include "图形_对话.h"
#include "图形_对话立绘.h"
#include "图形_静态立绘.h"
#include "图形_背景.h"
//关卡
#include "关卡.h"
#include "场景.h"
#include "对话.h"
#include "王战.h"
//其它
#include "玩家.h"
#include "计算.h"
#include "取文本.h"
#include "难度.h"
#include "轨迹.h"
import 东方山寨.基础_计时器;
import 东方山寨.图形_符卡立绘函数;
import 东方山寨.图形_符卡立绘模板;
import 东方山寨.关卡标识;
import 东方山寨.关卡工厂;
import 东方山寨.关卡练习;
import 东方山寨.关卡效果;
namespace 东方山寨 {
using t子弹工厂 = C子弹制造机;
using t敌机工厂 = C敌机制造机;
using t图形工厂 = C图形工厂;
using tp子弹工厂 = std::shared_ptr<C子弹制造机>;
using tp敌机工厂 = std::shared_ptr<C敌机制造机>;
using tp图形工厂 = std::shared_ptr<C图形工厂>;
using 工具::C计次器;
//实用函数
namespace 脚本 {
//游戏资源
tp敌机属性 fg敌机样式(const std::wstring &);
//图形资源
tp模型 fg模型(const std::wstring &);
tp纹理 fg纹理(const std::wstring &);
tp静态立绘 fg静态立绘(const std::wstring &);
//内容
std::function<float()> F随机数(unsigned long long 推进 = 0);
void f全屏清弹(const t向量2 &坐标 = t向量2::c零, float 最大半径 = 600, bool 产生道具 = false);
float fg动态难度();
t向量2 fg自机坐标();
t向量2 fg自机速度(float 秒 = 1);	//平均速度
std::shared_ptr<C敌机> f王入场(E敌机, const t向量2 &开始, const t向量2 &结束);
void f掉落道具(const t道具组 &, const t向量2 &坐标, const t向量2 &速度 = t向量2::c零);
//模板
template<typename t> auto F均匀随机(t a, t b) {
	if constexpr (std::is_integral_v<t>) {
		return C游戏::fg内容().f工厂_随机数f(std::uniform_int_distribution<t>(a, b));
	} else if constexpr (std::is_floating_point_v<t>) {
		return C游戏::fg内容().f工厂_随机数f(std::uniform_real_distribution<t>(a, b));
	} else {
		return C游戏::fg内容().f工厂_随机数f(std::uniform_real_distribution<t>(a, b));
	}
}
}	//namespace 脚本
}	//namespace 东方山寨