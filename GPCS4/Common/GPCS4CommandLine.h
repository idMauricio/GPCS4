#pragma once

#include <string>
#include <vector>

struct CommandLineArgs
{
	// Game binary
	std::string m_sEBoot;

	// Debug Message (Channel)
	bool m_bListDebugChannel;
	std::vector<std::string> m_vsDebugChannel;

	// Audio System
	// bool m_bListAudioDevice;
	// uint32_t m_audioOutDevice;
};

extern CommandLineArgs g_CommandLineArgs;

void processCommandLine(int argc, char* argv[]);
