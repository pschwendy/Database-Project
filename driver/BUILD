cc_test(
    name = "driver_test",
    srcs = ["driver_test.cpp"],
    deps = [
        ":driver_lib"
    ],
)

cc_binary(
    name = "insert_test",
    srcs = ["insert_test.cpp"],
    deps = [
        ":driver_lib",
        ":test_lib",
    ],
)

cc_binary(
    name = "select_test",
    srcs = ["select_test.cpp"],
    deps = [
        ":driver_lib",
        ":test_lib",
    ],
)

cc_library(
	name = "driver_lib",
	srcs = ["driver.cpp"],
	hdrs = ["driver.h"],
	deps = [
        "//storage:storage_lib",
        "//table:table_lib",
	],
    visibility = ["//visibility:public"],
)

cc_library(
	name = "test_lib",
	srcs = ["test_utils.cpp"],
    hdrs = ["test_utils.h"],
	deps = [
        ":driver_lib",
	],
    visibility = ["//visibility:public"],
)