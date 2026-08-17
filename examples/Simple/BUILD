load("@roo_testing//roo_testing/emulation:arduino.bzl", "roo_arduino_example")

roo_arduino_example(
    name = "Simple",
    defines = ["ROO_LOGGING_COLORLOGTOSTDERR=1"],
    sketch = "Simple.ino",
    visibility = ["//visibility:public"],
    deps = ["//:roo_quantity"],
)
