cc_library(
    name = "ProtoTable",
    srcs = ["table.pb.cc"],
    hdrs = ["table.pb.h"],
    deps = ["//protos:table_cc_proto"]
)

cc_library(
    name = "Table",
    srcs = ["Table.cpp"],
    hdrs = ["Table.h"],
    deps = [
        "//protos:table_cc_proto"
    ],
)

cc_binary(
    name = "table_test",
    srcs = ["table_test.cpp"],
    deps = [
        ":Table",
    ],
)