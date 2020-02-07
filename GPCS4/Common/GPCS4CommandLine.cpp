
#include "GPCS4Common.h"

#include <cxxopts/cxxopts.hpp>

CommandLineArgs g_CommandLineArgs;

void processCommandLine(int argc, char* argv[])
{
	cxxopts::Options opts("GPCS4", "PlayStation 4 Emulator");
	opts.allow_unrecognised_options();

	opts.positional_help("<eboot.bin>").show_positional_help();

	opts.add_options()  //
		("e,eboot", "Set main executable. The folder where GPCS4.exe located will be mapped to /app0.", cxxopts::value<std::string>());

	//opts.add_options("Config")  //
	//	("c,configure", "Config file.");

	//opts.add_options("Audio")                                   //
	//	("list-audio-device", "List avaliable audio devices.")  //
	//	("disable-audio", "Disable audio playback")             //
	//	("playback-device", "The ID of device to playback audio.", cxxopts::value<uint32_t>());

	opts.add_options("Debug")                                                                                                         //
		("debug-channel", "Debug channel, use ',' to seperate. 'ALL' for all channels.", cxxopts::value<std::vector<std::string>>())  //
		("list-debug-channels", "List avaliable debug channels.");

	opts.add_options("Misc")  //
		("help", "Print help message.");

	opts.parse_positional({ "eboot" });

	// Backup arg count,
	// because cxxopts will change argc value internally,
	// which I think is a bad design.
	const uint32_t argCount = argc;

	auto optResult = opts.parse(argc, argv);
	if (optResult.count("help") || argCount < 2)
	{
		auto helpString = opts.help();
		printf("%s\n", helpString.c_str());
		exit(-1);
	}

	if (optResult.count("eboot"))
	{
		g_CommandLineArgs.m_sEBoot = optResult["eboot"].as<std::string>();
	}

	if (optResult.count("debug-channel"))
	{
		g_CommandLineArgs.m_vsDebugChannel = optResult["debug-channel"].as<std::vector<std::string>>();
	}

	if (optResult.count("list-debug-channels"))
	{
		g_CommandLineArgs.m_bListDebugChannel = true;
	}
}
