#ifndef __MSEC_LOGGER__
#define __MSEC_LOGGER__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mirror/art_method.h"

#define LOGPATH(package)	"/data/local/tmp/" ##package
#define CONFIG_PATH			"/data/local/tmp/log.config"

#define LOG_LENGTH	512

namespace art {

class MsecLogger {
public:
	MsecLogger();
	MsecLogger(const char* package_name);

	static MsecLogger* getMsecLogger();

	bool openLogfile();

	void writeLog(const char* log);
	void writeLogFromArtMethod(ArtMethod* method);

	void setPackageName(const char* package_name);
	const char* getPackageName();

private:
	static MsecLogger* logger;

	// target package name
	char* package_name;

	// log file descriptor
	int target_fd;

};

} // namespace art

#endif /* __MSEC_LOGGER__ */