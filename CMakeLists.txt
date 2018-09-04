project (format_message_test)

cmake_minimum_required (VERSION 3.3)

add_executable (
	format_message_test
	main.c
	)

set_target_properties (
	format_message_test
	PROPERTIES
	OUTPUT_NAME format-message-test
	)
