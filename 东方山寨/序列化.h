#pragma once
#include <cflw文件_json.h>
namespace 东方山寨 {
struct S游戏设置;
struct S录像信息;
struct S录像关卡信息;
struct S玩家成绩;
}	//namespace 东方山寨
namespace cflw::文件::json {
//游戏设置
template<> t树 f序列化(const 东方山寨::S游戏设置&);
template<> 东方山寨::S游戏设置 f解析(const t树&);
//录像信息
template<> t树 f序列化(const 东方山寨::S录像信息 &);
template<> 东方山寨::S录像信息 f解析(const t树 &);
//关卡信息
template<> t树 f序列化(const 东方山寨::S录像关卡信息 &);
template<> 东方山寨::S录像关卡信息 f解析(const t树 &);
//玩家成绩
template<> t树 f序列化(const 东方山寨::S玩家成绩 &);
template<> 东方山寨::S玩家成绩 f解析(const t树 &);
}	//namespace cflw::文件::json