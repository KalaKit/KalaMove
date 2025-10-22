//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include <vector>
#include <string>

namespace KalaMove
{
	using std::vector;
	using std::string;

	class Move
	{
	public:
		//Ensures all paths we need to copy from and to are valid
		//and handles copying all files to relevant paths
		static void Run(const vector<string>& params);
	};
}