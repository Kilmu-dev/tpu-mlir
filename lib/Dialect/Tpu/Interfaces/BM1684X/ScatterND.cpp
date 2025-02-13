//===----------------------------------------------------------------------===//
//
// Copyright (C) 2022 Sophgo Technologies Inc.  All rights reserved.
//
// TPU-MLIR is licensed under the 2-Clause BSD License except for the
// third-party components.
//
//===----------------------------------------------------------------------===//

#include "tpu_mlir/Backend/BM168x/BM1684X.h"
#include "tpu_mlir/Dialect/Top/IR/TopOps.h"
#include "tpu_mlir/Dialect/Tpu/IR/TpuOps.h"
#include "tpu_mlir/Support/Module.h"
#include <strings.h>

using namespace tpu_mlir::backend;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  int data_dims;
  int indices_dims;
  int updates_dims;
} scatter_nd_global_param_t;

#ifdef __cplusplus
}
#endif

// =========================================
// GlobalGenInterface
// =========================================

void tpu::ScatterNDOp::codegen_global_bm1684x() {
  auto op = getOperation();
  scatter_nd_global_param_t param{0};
  auto data_shape = module::getShape(getInputData());
  auto indices_shape = module::getShape(getIndices());
  auto updates_shape = module::getShape(getUpdates());
  param.data_dims = data_shape.size();
  param.indices_dims = indices_shape.size();
  param.updates_dims = updates_shape.size();
  // assert(module::getStorageType(getIndices()).isInteger(32));
  auto input_spec = BM168x::get_input_spec(op);
  auto output_spec = BM168x::get_output_spec(op);
  BM168x::call_global_func("backend_api_scatter_nd_global", &param,
                           sizeof(param), input_spec->data(),
                           output_spec->data());
}

// ======================================
// Dynamic GlobalGenInterface
// ======================================
int64_t tpu::ScatterNDOp::dyn_codegen_global_bm1684x(void *buffer) { return 0; }
