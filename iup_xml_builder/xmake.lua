toolchain("i686-windows")
set_toolset("cc", "i686-w64-mingw32-gcc")
set_toolset("cxx", "i686-w64-mingw32-gcc", "i686-w64-mingw32-g++")
set_toolset("ld", "i686-w64-mingw32-g++", "i686-w64-mingw32-gcc")
set_toolset("ar", "i686-w64-mingw32-ar")

-- 工程
target("iup_xml_builder")

-- 构建之后运行插件
after_build(function(target)
    -- 导入task模块
    import("core.base.task")
    -- 运行插件任务
    task.run("project", {kind = "compile_commands"})
end)

set_kind("binary")
set_optimize("faster")
set_targetdir("$(buildir)/$(mode)")
-- add_linkdirs("$(buildir)/$(mode)")

add_includedirs("$(projectdir)/lib/iup3/include",
                "$(projectdir)/lib/pcre2/include",
                "$(projectdir)/lib/libarchive/include",
                "$(projectdir)/lib/libxml2/include/libxml2",
                "$(projectdir)/lib/libxslt/include",
                "$(projectdir)/lib/libiconv/include")
add_linkdirs("$(projectdir)/lib/iup3/lib", "$(projectdir)/lib/pcre2/lib",
             "$(projectdir)/lib/libarchive/lib",
             "$(projectdir)/lib/libxml2/lib",
             "$(projectdir)/lib/libxslt/lib",
             "$(projectdir)/lib/libiconv/lib",
             "$(projectdir)/lib/zlib/lib")

add_includedirs("$(projectdir)/collections/dl_list",
                "$(projectdir)/utils/src",
                "$(projectdir)/iup_xml_builder/src")

add_includedirs(
    "/usr/local/Cellar/mingw-w64/8.0.0_3/toolchain-i686/i686-w64-mingw32/include")
set_toolchains("i686-windows")

add_files("$(projectdir)/collections/dl_list/*.c|test_*.c",
          "$(projectdir)/utils/src/*.c")
add_files("$(projectdir)/iup_xml_builder/src/*.c|iup_xml_builder_preview.c",
          "$(projectdir)/iup_xml_builder/test/*.c")

add_ldflags("-static-libgcc")
add_links("iupim", "iupcd", "iup", "pcre2-8", "exslt", "xslt", "xml2",
          "archive", "iconv", "charset", "zlib")
add_syslinks("kernel32", "user32", "gdi32", "winspool", "comdlg32", "advapi32",
             "shell32", "uuid", "ole32", "oleaut32", "comctl32", "ws2_32")
