#pragma once

#include <chrono>
#include <memory>

#include "gmock/gmock.h"

#include "test/test_common/simulated_time_system.h"

#include "envoy/api/api.h"
#include "envoy/common/time.h"
#include "envoy/event/dispatcher.h"
#include "envoy/stats/store.h"

#include "nighthawk/client/options.h"
#include "nighthawk/common/platform_util.h"
#include "nighthawk/common/rate_limiter.h"
#include "nighthawk/common/sequencer.h"
#include "nighthawk/common/statistic.h"

using namespace std::chrono_literals;

constexpr std::chrono::milliseconds TimeResolution = 1ms;

namespace Nighthawk {

// TODO(oschaaf): split this out in files for common/ and client/ mocks

class MockPlatformUtil : public PlatformUtil {
public:
  MockPlatformUtil();
  ~MockPlatformUtil();

  MOCK_CONST_METHOD0(yieldCurrentThread, void());
};

class MockRateLimiter : public RateLimiter {
public:
  MockRateLimiter();
  ~MockRateLimiter();

  MOCK_METHOD0(tryAcquireOne, bool());
  MOCK_METHOD0(releaseOne, void());
};

class MockSequencer : public Sequencer {
public:
  MockSequencer();
  ~MockSequencer();

  MOCK_METHOD0(start, void());
  MOCK_METHOD0(waitForCompletion, void());
  MOCK_CONST_METHOD0(completionsPerSecond, double());
  MOCK_CONST_METHOD0(statistics, StatisticPtrMap());
};

class MockOptions : public Client::Options {
public:
  MockOptions();
  ~MockOptions();

  MOCK_CONST_METHOD0(requests_per_second, uint64_t());
  MOCK_CONST_METHOD0(connections, uint64_t());
  MOCK_CONST_METHOD0(duration, std::chrono::seconds());
  MOCK_CONST_METHOD0(timeout, std::chrono::seconds());
  MOCK_CONST_METHOD0(uri, std::string());
  MOCK_CONST_METHOD0(h2, bool());
  MOCK_CONST_METHOD0(concurrency, std::string());
  MOCK_CONST_METHOD0(verbosity, std::string());
  MOCK_CONST_METHOD0(toCommandLineOptions, Client::CommandLineOptionsPtr());
};

class FakeSequencerTarget {
public:
  FakeSequencerTarget();
  virtual ~FakeSequencerTarget();
  // A fake method that matches the sequencer target signature.
  virtual bool callback(std::function<void()>) PURE;
};

class MockSequencerTarget : public FakeSequencerTarget {
public:
  MockSequencerTarget();
  ~MockSequencerTarget();

  MOCK_METHOD1(callback, bool(std::function<void()>));
};

} // namespace Nighthawk