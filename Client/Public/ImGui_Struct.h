#pragma once
#include "../../Reference/Imgui/imgui.h"

#include <unordered_map>
#include <algorithm>
#include <vector>
#include <list>
#include <map>
using namespace std;

struct ImGuiDESC
{
	string				strName;
	ImGuiWindowFlags	eWindowFlags = ImGuiWindowFlags_None;
	ImVec2				vWindowSize = { 0.f, 0.f };
};

