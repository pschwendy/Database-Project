load("@rules_cc//cc:defs.bzl", "cc_proto_library")
proto_library (
    name = "table_proto",
    srcs = ["table.proto"],
)

proto_library (
    name = "condition_proto",
    srcs = ["condition.proto"],
)

cc_proto_library (
    name = "table_cc_proto",
    deps = [":table_proto"],
    visibility = ["//visibility:public"],
)

cc_proto_library (
    name = "condition_cc_proto",
    deps = [":condition_proto"],
    visibility = ["//visibility:public"],
)