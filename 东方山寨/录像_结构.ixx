module;
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <cflw时间.h>
#include "游戏设置.h"
#include "玩家.h"
export module 东方山寨.录像_结构;
namespace 时间 = cflw::时间;
export namespace 东方山寨 {
constexpr int c录像版本 = 1;
constexpr int c游戏版本 = 1;
struct S录像帧 {
	t向量2 m方向;
	t标志 m按键;
	int m帧速率;
};
struct S录像信息 {
	int m录像版本 = c录像版本;
	int m游戏版本 = c游戏版本;
	std::wstring m玩家名称;
	时间::t时间点 m开始时间, m结束时间;
	size_t m关卡数量;	//校验
	S游戏设置 m游戏设置;
};
struct S关卡信息 {
	int m关卡 = 0;
	size_t m帧数 = 0;	//校验
	时间::t时间点 m开始时间, m结束时间;
	//结束信息
	long long m分数 = 0;
	//开始信息
	int m随机数种子;
	t向量2 m自机坐标;
	C玩家::S成绩 m玩家成绩;
};
class C录像 {
public:
	C录像() = default;
	~C录像() = default;
	S录像信息 m录像信息;
	std::vector<S关卡信息> m关卡信息;
	std::map<int, std::vector<S录像帧>> m关卡数据;
};
}	//namespace 东方山寨