#pragma once

#include <dlfcn.h>

namespace {
	void *MinecraftHandle() {
		static void *handle = dlopen(nullptr, RTLD_LAZY);
		return handle;
	}
}