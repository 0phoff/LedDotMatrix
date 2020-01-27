workspace "LedDotMatrix"
  configurations {
    "Release",
    "Debug",
  }
  startproject "LDMTest"

include "ldm.lua"

project "LDMTest"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir "bin"
  objdir "obj"

  files {
   "test/**.cpp",
   "test/**.h",
  }

  includedirs {
    "include",
  }

  links {
    "LedDotMatrix",
  }

  filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    runtime "Release"
    optimize "on"
