cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":main_lib"
    ],
)

cc_library(
	name = "main_lib",
	srcs = ["main.cpp"],
	deps = [
        "//driver:driver_lib"
	],
    visibility = ["//visibility:public"],
)