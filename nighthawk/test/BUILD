load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_mock",
    "envoy_cc_test",
)

package(default_visibility = ["//visibility:public"])

envoy_cc_mock(
    name = "nighthawk_mocks",
    srcs = ["mocks.cc"],
    hdrs = ["mocks.h"],
    repository = "@envoy",
    deps = [
        "//nighthawk/include/nighthawk/common:base_includes",
        "//nighthawk/source/client:nighthawk_client_lib",
        "@envoy//test/test_common:simulated_time_system_lib",
    ],
)

envoy_cc_test(
    name = "nighthawk_test",
    srcs = [
        "frequency_test.cc",
        "options_test.cc",
        "platform_util_test.cc",
        "rate_limiter_test.cc",
        "sequencer_test.cc",
        "statistic_test.cc",
        "stream_decoder_test.cc",
        "utility_test.cc",
    ],
    data = [
        "test_data/hdr_proto_json.gold",
    ],
    repository = "@envoy",
    deps = [
        "//nighthawk/source/client:nighthawk_client_lib",
        "//nighthawk/test:nighthawk_mocks",
        "//nighthawk/test/test_common:environment_lib",
        "@envoy//source/common/filesystem:filesystem_lib",
        "@envoy//source/common/protobuf:utility_lib",
        "@envoy//source/common/stats:isolated_store_lib",
        "@envoy//test/integration:http_integration_lib",
        "@envoy//test/integration:integration_lib",
        "@envoy//test/mocks/event:event_mocks",
        "@envoy//test/mocks/thread_local:thread_local_mocks",
        "@envoy//test/server:utility_lib",
        "@envoy//test/test_common:simulated_time_system_lib",
    ],
)
