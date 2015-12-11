#pragma once
#include <string>


#include <vector>
#include <unordered_map>
#include "Json.h"
#include <fstream>

class Debug {
public:
	~Debug() {

		using namespace nlohmann;

		json writer;

		for (auto &it : messages) {
			writer[it.first] += it.second;
		}

		std::ofstream("log/recent.log") << writer;
	}

	void log(const std::string& subset, const std::string& message) {
		messages[subset].push_back(message);
	}

	std::unordered_map<std::string, std::vector<std::string>> messages;

};



