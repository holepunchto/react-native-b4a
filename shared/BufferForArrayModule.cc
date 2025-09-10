#include <memory>

#include <react/bridging/Bridging.h>

#include "BufferForArrayModule.h"

using namespace facebook::jsi;
using namespace facebook::react;

namespace facebook::react {

BufferForArrayModule::BufferForArrayModule(std::shared_ptr<CallInvoker> jsInvoker) : NativeBufferForArrayCxxSpec(std::move(jsInvoker)) {}

double
BufferForArrayModule::byteLengthUTF8(Runtime &rt, String string) {
  return string.utf8(rt).size();
}

String
BufferForArrayModule::toStringUTF8(Runtime &rt, Object buffer, double offset, double length) {
  auto data = buffer.getArrayBuffer(rt).data(rt);

  return String::createFromUtf8(rt, &data[size_t(offset)], size_t(length));
}

double
BufferForArrayModule::writeUTF8(jsi::Runtime &rt, jsi::Object buffer, double offset, double length, jsi::String string) {
  auto data = buffer.getArrayBuffer(rt).data(rt);

  auto utf8 = string.utf8(rt);

  auto written = std::min(size_t(length), utf8.size());

  std::copy(utf8.begin(), utf8.begin() + written, &data[size_t(offset)]);

  return double(written);
}

} // namespace facebook::react
