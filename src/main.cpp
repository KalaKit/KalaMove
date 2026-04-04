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
using KalaHeaders::KalaLog::LogType;

using KalaCLI::Core;
using KalaCLI::CommandManager;

using KalaMove::KalaMoveCore;

using std::vector;
using std::string;

static void AddExternalCommands()
{
	auto move_all = [](const vector<string>& params) -> void
		{
			if (params.size() > 1)
			{
				Log::Print(
					"Command 'all' does not allow any arguments!",
					"PARSE",
					LogType::LOG_ERROR,
					2);

				return;
			}

			KalaMoveCore::Move(params);
		};

	auto move_selected = [](const vector<string>& params) -> void
		{
			if (params.size() == 1)
			{
				Log::Print(
					"Command 'move' got no arguments! You must pass a .kmf path!",
					"PARSE",
					LogType::LOG_ERROR,
					2);

				return;
			}
			if (params.size() > 2)
			{
				Log::Print(
					"Command 'move' only allows one argument! You must pass a .kmf path!",
					"PARSE",
					LogType::LOG_ERROR,
					2);

				return;
			}

			KalaMoveCore::Move(params);
		};

	auto version = [](const vector<string>& params)
		{
			if (params.size() > 1)
			{
				Log::Print(
					"Command 'version' does not allow any arguments!",
					"PARSE",
					LogType::LOG_ERROR,
					2);

				return;
			}

			Log::Print("KalaMove 1.2");
		};

	CommandManager::AddCommand(
		{
			.primaryParam = "move",
			.description = "Parse a kmf file, second parameter must be valid path.",
			.targetFunction = move_selected
		});
	CommandManager::AddCommand(
		{
			.primaryParam = "all",
			.description = "Parse all found kmf files in current directory.",
			.targetFunction = move_all
		});

	CommandManager::AddCommand(
		{
			.primaryParam = "version",
			.description = "Prints current KalaMove version.",
			.targetFunction = version
		});
}

int main(int argc, char* argv[])
{
	Core::Run(argc, argv, AddExternalCommands);

	return 0;
}
