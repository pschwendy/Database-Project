cc_test(
    name = "driver_test",
    srcs = ["driver_test.cpp"],
    deps = [
        ":driver_lib"
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