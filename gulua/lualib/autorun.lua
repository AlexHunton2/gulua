--[[
	autorun.lua

	File that is run prior to any user program to give access to special
	functions/structures/etc.
]]--
local p = package.path
package.path = "../../gulua/lualib/?.lua"

require "tabledump"

package.path = p