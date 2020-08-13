add_executable(sample main.cc sample.cc ../instrument.cc)
target_compile_options(sample PRIVATE -g -finstrument-functions)