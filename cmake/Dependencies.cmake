find_package(Protobuf REQUIRED)

list(APPEND CABIN_COMMON_LIBRARIES "pthread")
list(APPEND CABIN_COMMON_LIBRARIES "protobuf::libprotobuf")
list(APPEND CABIN_COMMON_LIBRARIES "rt")
list(APPEND CABIN_COMMON_LIBRARIES "cryptopp")