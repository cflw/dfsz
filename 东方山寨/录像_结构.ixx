module;
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <filesystem>
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
	std::wstring m录像标题;	//按结束时间命名
	std::wstring m玩家名称;
	时间::t时间点 m开始时间, m结束时间;
	size_t m关卡数量;
	S游戏设置 m游戏设置;
};
struct S关卡信息 {
	int m关卡 = 0;	//关卡标识
	size_t m帧数 = 0;	//校验
	时间::t时间点 m开始时间, m结束时间;
	//结束信息
	long long m结束分数 = 0;
	//开始信息
	unsigned int m随机数种子;
	t向量2 m自机坐标;
	C玩家::S成绩 m玩家成绩;
};
class C录像 {	//从文件中读取的录像
public:
	//函数
	C录像() = default;
	~C录像() = default;
	const std::wstring &fg录像标题() const {
		return m录像信息.m录像标题;
	}
	const std::wstring &fg玩家名称() const {
		return m录像信息.m玩家名称;
	}
	const 时间::t时间点 &fg结束时间() const {
		return m录像信息.m结束时间;
	}
	int fg机型() const {
		return m录像信息.m游戏设置.m子机标识;
	}
	int fg难度() const {
		return ma关卡信息[0].m关卡;
	}
	int fg关卡() const {
		return ma关卡信息[0].m关卡;
	}
	long long fg结束分数() const {
		return ma关卡信息[0].m结束分数;
	}
	bool fi头部数据() const {	//是否载入了头部数据.如果没有,说明录像是空的
		return !ma关卡信息.empty();
	}
	bool fi完整数据() const {	//如果没有完整读取,帧数据是空的
		return !ma帧数据.empty();
	}
	//变量
	std::filesystem::path m文件路径;	//保存的文件路径
	S录像信息 m录像信息;
	std::vector<S关卡信息> ma关卡信息;
	std::map<int, std::vector<S录像帧>> ma帧数据;
};
}	//namespace 东方山寨