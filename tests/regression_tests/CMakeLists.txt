# Add the executable target for regression tests
add_executable(openturbine_regression_tests)

# Add subdirectories for additional components
add_subdirectory(external)
add_subdirectory(regression)
add_subdirectory(interfaces)

# Specify the source files for the regression tests
target_sources(openturbine_regression_tests PRIVATE rtest_main.cpp)

# Link internal libraries to the regression test executable
target_link_libraries(openturbine_regression_tests PRIVATE
  openturbine_warnings
  openturbine_options
  OpenTurbine::openturbine_library
)

# Link system libraries and dependencies
if(TARGET yaml-cpp::yaml-cpp)
  set(YAML_CPP_TARGET yaml-cpp::yaml-cpp)
else()
  set(YAML_CPP_TARGET yaml-cpp)
endif()

#----------------------------------------
# NetCDF
#----------------------------------------
if(TARGET netCDF::netcdf)
  set(NETCDF_TARGET netCDF::netcdf)
elseif(TARGET NetCDF::NetCDF)
  set(NETCDF_TARGET NetCDF::NetCDF)
elseif(TARGET netcdf)
  set(NETCDF_TARGET netcdf)
else()
  message(FATAL_ERROR "NetCDF library not found")
endif()

target_link_system_libraries(openturbine_regression_tests PRIVATE
  KokkosKernels::kokkoskernels
  ${YAML_CPP_TARGET}
  GTest::gtest
  GTest::gtest_main
)

# Add compile definition for writing outputs
if(OpenTurbine_WRITE_OUTPUTS)
  target_compile_definitions(openturbine_regression_tests PRIVATE OpenTurbine_WRITE_OUTPUTS)
endif()

# Add compile definitions for OpenTurbine_ENABLE_OPENFAST_ADI if enabled
if(OpenTurbine_ENABLE_OPENFAST_ADI)
  target_compile_definitions(openturbine_regression_tests PRIVATE OpenTurbine_ENABLE_OPENFAST_ADI)
endif()

target_include_directories(openturbine_regression_tests PRIVATE
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/tests/regression_tests>
)

# Include GoogleTest module and discover tests
include(GoogleTest)
gtest_discover_tests(openturbine_regression_tests PROPERTIES DISCOVERY_TIMEOUT 60000)
