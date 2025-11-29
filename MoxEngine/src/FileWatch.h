#pragma once
#include <filesystem>
struct FileWatch {

	std::filesystem::file_time_type lastWriteTime;
};