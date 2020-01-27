workspace "LedDotMatrix"
  configurations {
    "Release",
    "Debug",
  }
  startproject "LDMTest"

project "LedDotMatrix"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  targetdir "bin"
  objdir "obj"

  files {
    "src/**.cpp",
    "src/**.h",
    "include/**.h",
  }

  includedirs {
    "include/LDM",
    "src",
  }

  filter "configurations:Debug"
    defines "LDM_DEBUG"
    runtime "Debug"
    symbols "on"

  filter "configurations:Release"
    defines {
      "LDM_RELEASE",
      "NDEBUG"
    }
    runtime "Release"
    optimize "on"


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
