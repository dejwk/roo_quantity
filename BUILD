# BUILD file for use with https://github.com/dejwk/roo_testing.

cc_library(
    name = "roo_quantity",
    visibility = ["//visibility:public"],
    srcs = glob(
        [
            "src/**/*.cpp",
            "src/**/*.h",
        ],
        exclude = ["test/**"],
    ),
    includes = [
        "src",
    ],
    deps = [
        "@roo_flags",
        "@roo_logging",
        "@roo_time"
    ],
)

cc_test(
    name = "si_test",
    srcs = glob(["test/si_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)