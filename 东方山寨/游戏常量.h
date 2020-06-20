#pragma once
namespace 东方山寨 {
//时间
template<typename t> constexpr t c计算频率 = (t)240;
template<typename t> constexpr t c帧秒 = 1 / c计算频率<t>;
//上限
constexpr unsigned int c子弹上限 = 2000;
constexpr unsigned int c玩家子弹上限 = 1000;
constexpr unsigned int c道具上限 = 2000;
constexpr unsigned int c敌机上限 = 100;
constexpr unsigned int c图形上限 = 5000;
constexpr unsigned int c遮罩上限 = 200;
//细节
constexpr float c王战倒计时0 = 10;
constexpr float c王战倒计时1 = 5;

}