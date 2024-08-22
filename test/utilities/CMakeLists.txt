add_executable(
	test_for_utilities 
	./testUtilities.c 
	./../main.cpp
)

target_include_directories(test_for_utilities PRIVATE 
	../../src
)

target_sources(test_for_utilities PRIVATE 
	../../src/utilities.h
	../../src/utilities.c
)

target_link_libraries(
	test_for_utilities
	PRIVATE
	gtest_main	
)

add_test(gtest_for_utilities test_for_utilities)