#include "msec_logger.h"

MsecLogger::MsecLogger() {

}

MsecLogger::MsecLogger(const char* package_name) {
	this.package_name = package_name;

	if(openLogfile() == false) {
		target_fd = STDIN_FILENO;
	}
}

static MsecLogger* MsecLogger::getMsecLogger() {
	if(logger == null) {
		logger = new MsecLogger();
	}

	return logger;
}

bool MsecLogger::openLogfile() {
	if(package_name == NULL) {
		return false;
	}

	target_fd = open(LOGPATH(package_name), O_CREAT | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if(target_fd == -1) {
		return false;
	}

	return true;
}

void MsecLogger::writeLog(const char* log) {
	if(target_fd < 0) {
		// MSEC TODO : error processing
	}

	write(target_fd, log, LOG_LENGTH);
}

void MsecLogger::writeLogFromArtMethod(ArtMethod* method) {
	char log[LOG_LENGTH] = {};
	const char* invokeType = GetInvokeTypeToString(method->GetInvokeType());
	const char* retType = method->GetReturnTypeDescriptor();
	const char* methodName = method->GetName();
	DexFile::TypeList* typeList = method->GetParameterTypeList();

	sprintf(log, "[%s] %s %s (", invokeType, retType, methodName);

	// Parameter
	for(int i = 0 ; i < typeList->Size() ; i++) {
		uint16_t type_idx = typeList->GetTypeItem(xx);//->type_idx_;
		const char *type = method->GetTypeDescriptorFromTypeIdx(type_idx);

		strcat(log, type, strlen(type));
	}
	strcat(log, ")\n");

	// [invoke type] ret method ( param1, param2, ...)
	writeLog(log);
}

void MsecLogger::setPackageName(const char* package_name) {
	this.package_name = package_name;
}

const char* MsecLogger::getPackageName() {
	return package_name;
}