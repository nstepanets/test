file(REMOVE_RECURSE
  "bootloader/bootloader.bin"
  "bootloader/bootloader.elf"
  "bootloader/bootloader.map"
  "config/sdkconfig.cmake"
  "config/sdkconfig.h"
  "flash_project_args"
  "project_elf_src_esp32s2.c"
  "test1prj.bin"
  "test1prj.map"
  "CMakeFiles/dfu"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/dfu.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()