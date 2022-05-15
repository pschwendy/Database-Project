cc_library(
	name = "storage_lib",
	srcs = ["storage.cpp"],
	hdrs = ["storage.h"],
	deps = [
		"//table:table_lib",
	],
	visibility = ["//visibility:public"],
)

cc_binary(
	name = "main",
	srcs = ["main.cpp"],
	deps = [
		":storage_lib"
	]
)