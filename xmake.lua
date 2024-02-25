add_rules("mode.debug", "mode.release")
add_requires("brew::llvm", "zstd", "curses", "gtest")

sourceDirs = { "src/lexing/*.cpp", "src/source/*.cpp" }
testDirs = { "tests/*.cpp", "tests/lexing/*.cpp" }

target("HaibaraScript")
    set_kind("binary")
    set_languages("c++20")

    add_linkdirs("/opt/homebrew/opt/llvm/lib") -- 注意：这里的 linkDir 可能不适合所有设备
    add_includedirs("/opt/homebrew/opt/llvm/include")

    add_includedirs("includes/")

    add_files("src/main.cpp", sourceDirs)

    add_packages("brew::llvm", "zstd", "curses")

target("tests")
    set_kind("binary")
    set_languages("c++20")

    add_linkdirs("/opt/homebrew/opt/llvm/lib") -- 注意：这里的 linkDir 可能不适合所有设备
    add_includedirs("/opt/homebrew/opt/llvm/include")

    add_includedirs("includes/")

    add_files(sourceDirs, testDirs)

    add_packages("gtest")