#!/bin/bash
set -ex

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"

TEST_DIR=$REGRESSION_PATH/regression_out/script_test
mkdir -p $TEST_DIR
pushd $TEST_DIR

# convert by batch 4
model_transform.py \
  --model_name mobilenet_v2 \
  --model_def ${REGRESSION_PATH}/model/mobilenet_v2_deploy.prototxt \
  --model_data ${REGRESSION_PATH}/model/mobilenet_v2.caffemodel \
  --input_shapes=[[4,3,224,224]] \
  --resize_dims=256,256 \
  --mean=103.94,116.78,123.68 \
  --scale=0.017,0.017,0.017 \
  --pixel_format=bgr \
  --test_input=${REGRESSION_PATH}/image/cat.jpg \
  --test_result=mobilenet_v2_top_outputs.npz \
  --mlir mobilenet_v2.mlir

# input to npy
npz_tool.py to_npy mobilenet_v2_in_f32.npz data

# cali with batch 4
run_calibration.py mobilenet_v2.mlir \
  --dataset ${REGRESSION_PATH}/dataset/ILSVRC2012 \
  --input_num 6 \
  -o mobilenet_v2_cali_table

# cali by npz
mkdir -p npz_data
cp mobilenet_v2_in_f32.npz npz_data
run_calibration.py mobilenet_v2.mlir \
  --dataset npz_data \
  --input_num 1 \
  -o mobilenet_v2_cali_table_by_npz

# cali by npy
mkdir -p npy_data
cp data.npy npy_data
run_calibration.py mobilenet_v2.mlir \
  --dataset npy_data \
  --input_num 1 \
  -o mobilenet_v2_cali_table_by_npy

# cali by list
echo data.npy >data.list
run_calibration.py mobilenet_v2.mlir \
  --data_list data.list \
  -o mobilenet_v2_cali_table_by_list

run_qtable.py mobilenet_v2.mlir \
  --dataset ${REGRESSION_PATH}/dataset/ILSVRC2012 \
  --calibration_table mobilenet_v2_cali_table \
  --chip bm1684x \
  -o mobilenet_qtable

popd
