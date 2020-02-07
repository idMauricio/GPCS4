#include "Emulator/Emulator.h"
#include "Emulator/SceModuleSystem.h"
#include "Emulator/TLSHandler.h"
#include "Loader/ModuleLoader.h"

#include <memory>

#include "SceModules/SceAudioOut/sce_audioout.h"

LOG_CHANNEL(Main);

int main(int argc, char *argv[])
{
	std::unique_ptr<CEmulator> pEmulator = std::make_unique<CEmulator>();
	int nRet = -1;

	//audioTest();

	do
	{
		processCommandLine(argc, argv);

		// Initialize log system.
		logsys::init();

		if (g_CommandLineArgs.m_sEBoot.empty())
		{
			break;
		}

		// Initialize the whole emulator.

		LOG_DEBUG("GPCS4 start.");

		if (!pEmulator->Init())
		{
			break;
		}

		if (!installTLSManager())
		{
			break;
		}

		CLinker linker      = {*CSceModuleSystem::GetInstance()};
		ModuleLoader loader = { *CSceModuleSystem::GetInstance(), linker };

		auto eboot = g_CommandLineArgs.m_sEBoot;
		
		MemoryMappedModule *ebootModule = nullptr;
		if (!loader.loadModule(eboot, &ebootModule))
		{
			break;
		}

		if(!pEmulator->Run(*ebootModule))
		{
			break;
		}

		uninstallTLSManager();
		pEmulator->Unit();
		
		nRet = 0;
	} while (false);

	return nRet;
}
