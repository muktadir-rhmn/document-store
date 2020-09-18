cmake_minimum_required(VERSION 3.17)
project(document_store)

set(CMAKE_CXX_STANDARD 14)

add_executable(document_store main.cc utils/socket/server_socket.cc utils/socket/socket_exception.cc utils/socket/client_socket.cc connection/connection_handler.cc connection/connection_manager.cc connection/connection_manager.h user/user_manager.cc user/user_manager.h user/user.cc user/user.h utils/debug/debug.h utils/exceptions/exception.cc utils/exceptions/exception.h processor/processor.cc processor/processor.h utils/socket/buffered_input_stream.cc utils/socket/buffered_input_stream.h utils/socket/buffered_output_stream.cc utils/socket/buffered_output_stream.h connection/connection_descriptor.cc connection/connection_descriptor.h storage/engines/wiredtiger/lib/wiredtiger.h storage/api/database_manager.cc storage/api/database_manager.h storage/api/database.h processor/database_processor.cc processor/database_processor.h storage/engines/wiredtiger/database_imp.cc storage/engines/wiredtiger/database_imp.h storage/engines/wiredtiger/database_manager_imp.cc storage/engines/wiredtiger/database_manager_imp.h storage/api/collection.h processor/collection_processor.cc processor/collection_processor.h typedefs.h storage/engines/wiredtiger/collection_imp.cc storage/engines/wiredtiger/collection_imp.h storage/api/field_name_id_map.cc storage/api/field_name_id_map.h document/bson_constants.h document/document_converter.cc document/document_converter.h utils/data/byte_input_stream.cc utils/data/byte_input_stream.h processor/request_response_constants.h utils/data/output_stream.h utils/data/input_stream.h utils/exceptions/internal_exception.h document/array_reader.h document/document_reader.h document/document_writer.h document/array_writer.h utils/data/allocatable_output_stream.h utils/data/raw_data.h document/dr/dr_document_writer.cc document/dr/dr_document_writer.h utils/data/byte_output_stream.cc utils/data/byte_output_stream.h document/dr/dr_document_reader.cc document/dr/dr_document_reader.h utils/data/data_utils.cc utils/data/data_utils.h document/document_typedefs.h document/dr/dr_array_reader.cc document/dr/dr_array_reader.h document/dr/dr_array_writer.cc document/dr/dr_array_writer.h)
find_library(WIREDTIGER wiredtiger storage/engines/wiredtiger/lib)
target_link_libraries(document_store LINK_PUBLIC ${WIREDTIGER})

# Google Test
#add_subdirectory(third_parties/gtest)
#include_directories(third_parties/gtest/googletest/include)
#add_executable(Google_Tests_run third_parties/Test.cc)
#target_link_libraries(Google_Tests_run gtest gtest_main)

