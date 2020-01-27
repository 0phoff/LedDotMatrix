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
