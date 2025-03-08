if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_INSTALL_INCLUDEDIR
        "include/dius-${PROJECT_VERSION}"
        CACHE STRING ""
    )
    set_property(CACHE CMAKE_INSTALL_INCLUDEDIR PROPERTY TYPE PATH)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package dius)

install(
    TARGETS dius_dius dius_dius_test_main
    EXPORT diusTargets
    RUNTIME COMPONENT dius_Runtime
    LIBRARY COMPONENT dius_Runtime NAMELINK_COMPONENT dius_Development
    ARCHIVE COMPONENT dius_Development
    INCLUDES
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET HEADERS
)

write_basic_package_version_file("${package}ConfigVersion.cmake" COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT)
# Allow package maintainers to freely override the path for the configs
set(dius_INSTALL_CMAKEDIR
    "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE STRING "CMake package config location relative to the install prefix"
)
set_property(CACHE dius_INSTALL_CMAKEDIR PROPERTY TYPE PATH)
mark_as_advanced(dius_INSTALL_CMAKEDIR)

install(
    FILES meta/cmake/install-config.cmake
    DESTINATION "${dius_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT dius_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${dius_INSTALL_CMAKEDIR}"
    COMPONENT dius_Development
)

install(
    EXPORT diusTargets
    NAMESPACE dius::
    DESTINATION "${dius_INSTALL_CMAKEDIR}"
    COMPONENT dius_Development
)

if(dius_USE_RUNTIME)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/crt0.o" DESTINATION lib)
endif()

if(PROJECT_IS_TOP_LEVEL)
    include(CPack)
endif()
