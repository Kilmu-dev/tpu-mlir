//===----------------------------------------------------------------------===//
//
// Copyright (C) 2022 Sophgo Technologies Inc.  All rights reserved.
//
// TPU-MLIR is licensed under the 2-Clause BSD License except for the
// third-party components.
//
//===----------------------------------------------------------------------===//

#include "tpu_mlir/Backend/BM168x/BM1684X.h"
#include "tpu_mlir/Dialect/Tpu/IR/TpuOps.h"
#include "tpu_mlir/Support/Module.h"
#include "tpu_mlir/Support/MathUtils.h"

using namespace tpu_mlir::backend;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

// =========================================
// GlobalGenInterface
// =========================================

void tpu::ActiveOp::codegen_global_bm1684x() {
  active_global_spec_t spec = {0};
  spec.common.active_type = (int)getMode();
  if (getCoeffs().has_value()) {
    const auto coeffs_ = module::getF64Array(getCoeffs().value());
    for (int i = 0; i < coeffs_->size(); ++i) {
      spec.common.coeffs[i] = (float)coeffs_->at(i);
    }
  }
  auto op = getOperation();
  auto input_spec = BM168x::get_input_spec(op);
  auto output_spec = BM168x::get_output_spec(op);
  BM168x::call_global_func("backend_api_active_global", &spec, sizeof(spec),
                           input_spec->data(), output_spec->data());
}

// =========================================
// LocalGenInterface
// =========================================

int64_t tpu::ActiveOp::getBufferSize_bm1684x(
    int64_t in_lmem_bytes, int64_t out_lmem_bytes, int64_t in_nslice,
    int64_t in_hslice, int64_t out_nslice, int64_t out_hslice) {
  auto stype = module::getStorageType(getInput());
  int64_t dtype_len = stype.getIntOrFloatBitWidth() / 8;
  int64_t buffer_size = 0;
  int64_t tensor_size = in_lmem_bytes / in_nslice;
  switch (getMode()) {
  case ActiveMode::ERF:
    buffer_size = 3 * tensor_size;
    // 32 exp coeff, 192 exp table, 10 erf coeff, all memory need align to
    // 64byte
    buffer_size += align_up(32 * dtype_len, 64l) +
                   align_up(192 * dtype_len, 64l) +
                   align_up(10 * dtype_len, 64l);
    break;
  case ActiveMode::TANH:
  case ActiveMode::MISH:
  case ActiveMode::EXP:
  case ActiveMode::ELU:
  case ActiveMode::SOFT_PLUS:
  case ActiveMode::SILU:
  case ActiveMode::SIGMOID:
    // |    work1    |    work0    | exp coeff  | exp_table |
    // | tensor_size | tensor_size |     32     |    192    |
    buffer_size = 2 * align_up(tensor_size, 64l);
    buffer_size +=
        align_up(32 * dtype_len, 64l) + align_up(192 * dtype_len, 64l);
    break;
  case ActiveMode::GELU:
    buffer_size = 4 * tensor_size;
    // 32 exp coeff, 192 exp table, 10 erf coeff, all memory need align to
    // 64byte
    buffer_size += align_up(32 * dtype_len, 64l) +
                   align_up(192 * dtype_len, 64l) +
                   align_up(10 * dtype_len, 64l);
    break;
  case ActiveMode::LN:
  case ActiveMode::TAN:
  case ActiveMode::SIN:
  case ActiveMode::COS:
  case ActiveMode::ARCSIN:
  case ActiveMode::ARCCOS:
    buffer_size = tensor_size + align_up(32 * dtype_len, 64l);
    break;
  case ActiveMode::HSWISH:
  case ActiveMode::HSIGMOID:
    buffer_size = in_lmem_bytes;
    break;
  }
  return buffer_size;
}

void tpu::ActiveOp::codegen_local_bm1684x(int64_t n_step, int64_t h_step,
                                          local_sec_info_t &sec_info) {
  auto op = getOperation();
  auto input_spec = BM168x::get_input_spec(op);
  auto output_spec = BM168x::get_output_spec(op);
  auto gi = getGroupInfo(n_step, h_step);

  active_local_spec_t spec;
  memset(&spec, 0, sizeof(spec));
  spec.common.active_type = (int)getMode();
  spec.buffer_addr = gi.buffer_addr;
  if (getCoeffs().has_value()) {
    const auto coeffs_ = module::getF64Array(getCoeffs().value());
    for (int i = 0; i < coeffs_->size(); ++i) {
      spec.common.coeffs[i] = (float)coeffs_->at(i);
    }
  }

  BM168x::call_local_func("backend_api_active_local", &spec, sizeof(spec),
                          &sec_info, input_spec->data(), output_spec->data());
}

// dynamic codegen
int64_t tpu::ActiveOp::dyn_codegen_local_bm1684x(void *buffer) {
  if (!buffer)
    return sizeof(active_local_spec_t);
  auto gi = getGroupInfo(0, 0);
  active_local_spec_t spec;
  memset(&spec, 0, sizeof(spec));
  spec.common.active_type = (int)getMode();
  spec.buffer_addr = gi.buffer_addr;
  if (getCoeffs().has_value()) {
    const auto coeffs_ = module::getF64Array(getCoeffs().value());
    for (int i = 0; i < coeffs_->size(); ++i) {
      spec.common.coeffs[i] = (float)coeffs_->at(i);
    }
  }

  return BM168x::dynamic_spec_to_buffer(buffer, spec);
}

// ======================================
// Dynamic GlobalGenInterface
// ======================================
int64_t tpu::ActiveOp::dyn_codegen_global_bm1684x(void *buffer) {
  if (!buffer)
    return sizeof(active_global_spec_t);
  active_global_spec_t spec;
  memset(&spec, 0, sizeof(spec));
  spec.common.active_type = (int)getMode();
  if (getCoeffs().has_value()) {
    const auto coeffs_ = module::getF64Array(getCoeffs().value());
    for (int i = 0; i < coeffs_->size(); ++i) {
      spec.common.coeffs[i] = (float)coeffs_->at(i);
    }
  }
  return BM168x::dynamic_spec_to_buffer(buffer, spec);
}
