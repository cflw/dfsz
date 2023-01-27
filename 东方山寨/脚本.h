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
#include "关卡效果.h"
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
import 东方山寨.关卡练习;
import 东方山寨.关卡管理;
namespace 东方山寨 {
using t子弹工厂 = C子弹制造机;
using t敌机工厂 = C敌机制造机;
using t图形工厂 = C图形工厂;
using tp子弹工厂 = std::shared_ptr<C子弹制造机>;
using tp敌机工厂 = std::shared_ptr<C敌机制造机>;
using tp图形工厂 = std::shared_ptr<C图形工厂>;
using 工具::C计次器;
t向量2 fg自机坐标();
t向量2 fg自机速度(float 秒 = 0.5f);
std::shared_ptr<C敌机> f王入场(E敌机, const t向量2 &开始, const t向量2 &结束);
}	//namespace 东方山寨