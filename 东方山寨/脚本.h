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
//图形
#include "图形工厂.h"
#include "敌机图形模板.h"
#include "图形_抬显.h"
#include "图形_三维.h"
#include "图形_对话.h"
//关卡
#include "关卡.h"
#include "场景.h"
#include "对话.h"
#include "关卡效果.h"
#include "王战.h"
//其它
#include "玩家.h"
#include "道具.h"
#include "计算.h"
#include "取文本.h"
typedef 东方山寨::C子弹制造机 t子弹工厂;
typedef 东方山寨::C敌机制造机 t敌机工厂;
typedef 东方山寨::C图形工厂 t图形工厂;
typedef std::shared_ptr<t子弹工厂> tp子弹工厂;
typedef std::shared_ptr<t敌机工厂> tp敌机工厂;
typedef std::shared_ptr<t图形工厂> tp图形工厂;
using namespace 东方山寨;