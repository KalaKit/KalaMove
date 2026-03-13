//Copyright(C) 2026 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <vector>
#include <string>

#include "log_utils.hpp"

#include "kc_core.hpp"
#include "kc_command.hpp"

#include "move.hpp"

using KalaHeaders::KalaLog::Log;

using KalaCLI::Core;
using KalaCLI::CommandManager;

using KalaMove::KalaMoveCore;

using std::vector;
using std::string;

static void AddExternalCommands()
{
	auto version = [](const vector<string>& params)
		{
			Log::Print("KalaMove 1.2, KMF 1.0");
		};

	CommandManager::AddCommand(
		{
			.primaryParam = "move",
			.description = "Parse a kmf file, second parameter must be valid path.",
			.paramCount = 2,
			.targetFunction = KalaMoveCore::Move
		});
	CommandManager::AddCommand(
		{
			.primaryParam = "all",
			.description = "Parse all found kmf files in current directory.",
			.paramCount = 1,
			.targetFunction = KalaMoveCore::Move
		});

	CommandManager::AddCommand(
		{
			.primaryParam = "version",
			.description = "Prints current KalaMove version",
			.paramCount = 1,
			.targetFunction = version
		});
}

int main(int argc, char* argv[])
{
	Core::Run(argc, argv, AddExternalCommands);

	return 0;
}
