// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <torch/extension.h>
#include <core/framework/ort_value.h>
#include "core/common/status.h"
#include <core/framework/provider_options.h>
#include <core/eager/ort_kernel_invoker.h>
#include <core/graph/schema_registry.h>
#include "onnx/defs/schema.h"
#include <core/graph/model.h>

namespace torch_ort {
namespace eager {

class ORTBackendsManager {
public:
  ORTBackendsManager(const onnxruntime::logging::Logger& logger);

  void RegisterProviderLib(const std::string& provider_type, 
                           const std::string& lib_path,
                           const std::string& entry_point);

  onnxruntime::Status set_device(size_t device_index, const std::string& provider_type,
                                 const onnxruntime::ProviderOptions& provider_options);

  onnxruntime::ORTInvoker& GetInvoker(const at::Device device);

private:
  std::map<at::DeviceIndex, std::unique_ptr<onnxruntime::ORTInvoker>> backends_;
  const onnxruntime::logging::Logger& logger_;
  //custom op schema registry
  //TODO: we might want to support load custom op schema on the fly
  onnxruntime::IOnnxRuntimeOpSchemaRegistryList custom_op_schema_ = {};
  std::unordered_map<std::string, std::pair<std::string, std::string> > additional_provider_libs_ = {};
};

ORTBackendsManager& GetORTBackendsManager();

onnxruntime::ORTInvoker& GetORTInvoker(const at::Device device);

} // namespace eager
} // namespace torch_ort