#ifndef HOOK_REG
#define HOOK_REG

#include <string>
#include <vector>
#include <map>

#include "Hook.hpp"

// singleton
class HookRegistry {
private:
	HookRegistry();
	std::map<std::string, std::vector<std::shared_ptr<Hook>>> mHooks;
	lua_State *mLuaState;

	void callAll(lua_State *L, std::string callSig, const char *sig, va_list &vl) noexcept;
public:
	static std::shared_ptr<HookRegistry> getInstance() noexcept;
	static std::shared_ptr<HookRegistry> getInstance(lua_State *L) noexcept;
	std::string add(std::shared_ptr<Hook> hook) noexcept;
	int remove(std::string callSig) noexcept; // 0 means none removed, 1 means success
	void callAll(lua_State *L, std::string callSig, const char* sig, ...) noexcept;
	void callAll(std::string callSig, const char* sig, ...) noexcept;
	void register_lua_state(lua_State *L) noexcept;
};

#endif