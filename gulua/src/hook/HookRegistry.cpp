#include "hook/HookRegistry.hpp"

HookRegistry::HookRegistry() {}

std::shared_ptr<HookRegistry> HookRegistry::getInstance() noexcept {
  	static std::shared_ptr<HookRegistry> d(new HookRegistry);
  	return d;
}

std::shared_ptr<HookRegistry> HookRegistry::getInstance(lua_State *L) noexcept {
	getInstance()->register_lua_state(L);
	return getInstance();
}

std::string HookRegistry::add(std::shared_ptr<Hook> hook) noexcept {
	mHooks[hook->mCallSignature].push_back(hook);
	return hook->mCallSignature;
}

int HookRegistry::remove(std::string callSig) noexcept {
	return mHooks.erase(callSig);
}

void HookRegistry::callAll(lua_State *L, std::string callSig, const char *sig, ...) noexcept {
	va_list vl;
	va_start(vl, sig);
	callAll(L, callSig, sig, vl);
	va_end(vl);
}

void HookRegistry::callAll(std::string callSig, const char* sig, ...) noexcept {
	if (mLuaState == nullptr) {
		return;
	}	

	va_list vl;
	va_start(vl, sig);
	callAll(mLuaState, callSig, sig, vl);
	va_end(vl);
}

void HookRegistry::callAll(lua_State *L, std::string callSig, const char *sig, va_list &vl) noexcept {
	for (auto hook : mHooks[callSig]) {
		hook->call(L, sig, vl);
	}
}

void HookRegistry::register_lua_state(lua_State *L) noexcept {
	mLuaState = L;
}

void HookRegistry::clear() noexcept {
	mHooks.clear();
}