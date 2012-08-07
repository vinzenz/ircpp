--- Solution
solution "irc++"
	configurations {
		"Debug Dynamic Runtime-Shared", 
		"Debug Library Runtime-Shared", 
		"Release Dynamic Runtime-Shared", 
		"Release Library Runtime-Shared", 
		"Debug Dynamic Runtime-Static", 
		"Debug Library Runtime-Static", 
		"Release Dynamic Runtime-Static",
		"Release Library Runtime-Static" 
	}

	project "irc++"
		language "C++"
		flags { "ExtraWarnings", "FatalWarnings" }
		files { "../source/**.cc" }
		links { "boost_system" }
		includedirs { "../include", "../source/include" }

		configuration { "gmake" }
			buildoptions { "-std=c++0x", "-pedantic" }

		configuration "*Dynamic*"
			kind "SharedLib"
			defines { "IRCMM_SHARED" }

		configuration "*Library*"
			kind "StaticLib"
			defines { "IRCMM_STATIC" }

		configuration "Debug*"
			defines { "IRCMM_DEBUG" }
			flags { "Symbols" }
		
		configuration "Release*"
			defines { "IRCMM_NDEBUG" }
			flags { "Optimize" }
		
		configuration "*Runtime-Static"
			flags { "StaticRuntime" }

		configuration "linux or macosx or bsd"
			buildoptions "-pthread"

	project "irctest"
		kind "ConsoleApp"
		language "C++"
		flags { "ExtraWarnings", "FatalWarnings" }
		files { "../include/irc++/test.cpp" }
		includedirs { "../include" }
		links { "irc++", "boost_system", "pthread" }

		configuration { "gmake" }
			buildoptions { "-std=c++0x", "-pedantic" }

		configuration "linux or macosx or bsd"
			buildoptions "-pthread"

		configuration "*Dynamic*"
			defines { "IRCMM_SHARED" }

		configuration "*Library*"
			defines { "IRCMM_STATIC" }

		configuration "Debug*"
			defines { "IRCMM_DEBUG" }
			flags { "Symbols" }
		
		configuration "Release*"
			defines { "IRCMM_NDEBUG" }
			flags { "Optimize" }
		
		configuration "*Runtime-Static"
			flags { "StaticRuntime" }


