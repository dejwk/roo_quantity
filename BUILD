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
    name = "areic_number_test",
    srcs = glob(["test/areic_number_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "charge_test",
    srcs = glob(["test/charge_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "capacitance_test",
    srcs = glob(["test/capacitance_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "current_test",
    srcs = glob(["test/current_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "force_test",
    srcs = glob(["test/force_test.cpp"]),
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
    name = "lineic_number_test",
    srcs = glob(["test/lineic_number_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "mass_test",
    srcs = glob(["test/mass_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "power_test",
    srcs = glob(["test/power_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "pressure_test",
    srcs = glob(["test/pressure_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "resistance_test",
    srcs = glob(["test/resistance_test.cpp"]),
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
    name = "velocity_test",
    srcs = glob(["test/velocity_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "voltage_test",
    srcs = glob(["test/voltage_test.cpp"]),
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

cc_test(
    name = "volume_flow_rate_test",
    srcs = glob(["test/volume_flow_rate_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "volumic_number_test",
    srcs = glob(["test/volumic_number_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "work_test",
    srcs = glob(["test/work_test.cpp"]),
    linkstatic = 1,
    size = "small",
    deps = [
        ":roo_quantity",
        "@googletest//:gtest_main",
    ],
)
