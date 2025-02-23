export module 东方山寨.关卡效果;
export import <functional>;
export import 东方山寨.图形.关卡标题;
export namespace 东方山寨 {
namespace 关卡效果 {
std::function<void()> F显示标题(const S关卡标题 &);
}	//namespace 关卡效果
}	//namespace 东方山寨
module : private;
namespace 东方山寨 {
namespace 关卡效果 {
std::function<void()> F显示标题(const S关卡标题 &a关卡标题) {
	return [a关卡标题]() {
		图形模板::f关卡标题(a关卡标题);
	};
}
}	//namespace 关卡效果
}	//namespace 东方山寨