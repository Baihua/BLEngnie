project "BL"
kind "ConsoleApp"
language "C++"

includedirs{
	"%{wks.location}/glad/include",
	"%{wks.location}/glfw/include",
	"src/vendor","src"
	}
   

links{"Glad.lib","glfw3"}
libdirs{"%{wks.location}/glad/bin/" .. outputdir .. "/glad", "%{wks.location}/glfw/lib"}    
files
{
    "include/x.h",
	"src/**.*",
	"res/shader/*.*"
}

configuration "Debug"
debugdir "%{wks.location}/%{prj.location}/bin/debug"

filter { "configurations:Debug" }
    defines { "DEBUG" }
    symbols "On"
	
filter { "configurations:Release" }
    defines { "NDEBUG" }
    optimize "On"
