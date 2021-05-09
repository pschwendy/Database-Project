cc_test(
    name = "table_test",
    srcs = ["table_test.cpp"],
    deps = [
        ":table_lib"
    ],
)

cc_library(
    name = "table_lib",
    srcs = ["table.cpp"],
    hdrs = ["table.h"],
    deps = [
        "//protos:table_cc_proto"
    ],
)
