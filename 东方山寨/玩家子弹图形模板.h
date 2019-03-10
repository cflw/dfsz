#pragma once
namespace 东方山寨 {
class C玩家子弹;
struct S玩家子弹属性;
namespace 图形模板 {
void f玩家子弹消失(const C玩家子弹 &);
void f玩家子弹消失(const t向量2 &坐标, const t向量2 &速度, const S玩家子弹属性 &);
}
}