#pragma once
#include <boost/property_tree/ptree.hpp>
#include <filesystem>
#include <memory>
#include <cflw文件_json.h>
namespace 东方山寨::载入 {
using t属性文件 = cflw::文件::json::C文件;
using t路径 = std::filesystem::path;
using t属性树 = boost::property_tree::wptree;
using tp属性树 = std::unique_ptr<boost::property_tree::wptree>;
using t节点 = std::pair<const std::wstring, boost::property_tree::wptree>;
using t可选属性树 = boost::optional<const boost::property_tree::wptree &>;
struct S载入参数 {
	const t属性树 &m树;
	const t路径 &m路径;
};
}	//namespace 东方山寨