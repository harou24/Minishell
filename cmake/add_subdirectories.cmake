#https://gitlab.math.ethz.ch/NumCSE/NumCSE/commit/cf5ff7238bca5994e0142f310f4dddb148fb1a95
MACRO(ADD_ALL_SUBDIRECTORIES directory)
  subdirlist(SUBDIRS ${directory})

  foreach(SUBDIR ${SUBDIRS})
    if(EXISTS "${directory}/${SUBDIR}/CMakeLists.txt")
      add_subdirectory(${SUBDIR})
    else()
      message(WARNING "Skipping ${directory}/${SUBDIR} because no CMakeLists.txt file was found")
    endif()
  endforeach()
ENDMACRO()

