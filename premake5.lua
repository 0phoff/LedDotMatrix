workspace "LedDotMatrix"
  -- Workspace related configurations
  configurations {
    "Release",
    "Debug",
  }
  startproject "LDMTest"

  -- Include LDM library as a premake project
  include "ldm.lua"

project "LDMTest"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++17"
  targetdir "bin"
  objdir "obj"

  -- Link LDM library (we are in same dir as LDM, so no path is needed)
  useLDM()

  files {
   "test/**.cpp",
   "test/**.h",
  }

  filter "configurations:Debug"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    runtime "Release"
    optimize "on"
