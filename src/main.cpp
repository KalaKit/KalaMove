//Copyright(C) 2026 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include "KalaCLI/include/core.hpp"
#include "KalaCLI/include/command.hpp"

#include "move.hpp"

using KalaCLI::Core;
using KalaCLI::Command;
using KalaCLI::CommandManager;

using KalaMove::KalaMoveCore;

static void AddExternalCommands()
{
	Command cmd_move
		{
			.primary = { "move" },
			.description = "Parse a kmf file, second parameter must be valid path.",
			.paramCount = 2,
			.targetFunction = KalaMoveCore::Move
		};
		Command cmd_move_all
		{
			.primary = { "all" },
			.description = "Parse all found kmf files in current directory.",
			.paramCount = 1,
			.targetFunction = KalaMoveCore::Move
		};

	CommandManager::AddCommand(cmd_move);
	CommandManager::AddCommand(cmd_move_all);
}

int main(int argc, char* argv[])
{
	Core::Run(argc, argv, AddExternalCommands);

	return 0;
}