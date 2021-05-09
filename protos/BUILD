load("@rules_cc//cc:defs.bzl", "cc_proto_library")
proto_library (
    name = "table_proto",
    srcs = ["table.proto"],
)

cc_proto_library (
    name = "table_cc_proto",
    deps = [":table_proto"],
    visibility = ["//visibility:public"],
)