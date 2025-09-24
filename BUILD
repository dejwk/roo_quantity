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
    name = "area_test",
    srcs = glob(["test/area_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "frequency_test",
    srcs = glob(["test/frequency_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "length_test",
    srcs = glob(["test/length_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "linear_density_test",
    srcs = glob(["test/linear_density_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "temperature_test",
    srcs = glob(["test/temperature_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "time_test",
    srcs = glob(["test/time_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
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

cc_test(
    name = "volume_test",
    srcs = glob(["test/volume_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)
