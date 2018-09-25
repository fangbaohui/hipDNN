#include "test_convolution_forward.hpp"

TEST(convolution_fwd, func_check_zero_padding_medium_input_batch32) {
    Desc inputDesc(32, 3, 224, 224);
    Desc filterDesc(21, 3, 3, 3);
    int pad[2] = {0, 0};    // zero padding
    int stride[2] = {1, 1}; // stride 1
    float avg_time = 0;

    Desc outputDesc =
        calculateConv2DOutputDesc(inputDesc, filterDesc, pad, stride);
    Memory<float> srcData = createMemory<float>(inputDesc);
    Memory<float> dstDataCPU = createMemory<float>(outputDesc);
    Memory<float> dstDataGPU = createMemory<float>(outputDesc);
    Memory<float> filterData = createMemory<float>(filterDesc);
    populateMemoryRandom<float>(srcData);
    populateMemoryRandom<float>(filterData);
    test_convolution_sizes_t testConvolutionSizes(
        inputDesc.N, 1, inputDesc.C, inputDesc.H, inputDesc.W, outputDesc.C,
        outputDesc.H, outputDesc.W, filterDesc.H, filterDesc.W, pad[0], pad[1],
        stride[0], stride[1], 1, 1);

  int ip_size[4] = {inputDesc.N, inputDesc.C, inputDesc.H, inputDesc.W};
  int k_size[4] = {filterDesc.N, filterDesc.C, filterDesc.H, filterDesc.W};
  int op_size[4] =  {outputDesc.N, outputDesc.C, outputDesc.H, outputDesc.W};

  std::string str_ip_size  = convert_to_string((int*)ip_size,4);
  std::string str_k_size  = convert_to_string((int*)k_size,4);
  std::string str_op_size  = convert_to_string((int*)op_size,4);

  compute_hipdnn_conv_fwd<float>(testConvolutionSizes, srcData.gpu(),
                                filterData.gpu(), NULL, dstDataGPU.gpu(),&avg_time);
     
  std::cout << "\nAverage Time is: " << avg_time << "micro seconds"<<std::endl;

    std::string strt = "./result_unittest.csv";
    std::string testname = "convolution_fwd:func_check_zero_padding_medium_input_batch32";
    float* temp = dstDataGPU.getDataFromGPU();
    std::string str  = convert_to_string((float*)temp,(int)dstDataGPU.get_num_elements());
    write_to_csv(strt, str, testname, avg_time, str_ip_size, str_k_size, str_op_size);
}

TEST(convolution_fwd, func_check_two_strides_medium_kernelsize) {
    Desc inputDesc(1, 3, 600, 600);
    Desc filterDesc(2, 3, 30, 30);
    int pad[2] = {0, 0};    // zero padding
    int stride[2] = {2, 2}; // stride 2
    float avg_time = 0;

    Desc outputDesc =
        calculateConv2DOutputDesc(inputDesc, filterDesc, pad, stride);
    Memory<float> srcData = createMemory<float>(inputDesc);
    Memory<float> dstDataCPU = createMemory<float>(outputDesc);
    Memory<float> dstDataGPU = createMemory<float>(outputDesc);
    Memory<float> filterData = createMemory<float>(filterDesc);
    populateMemoryRandom<float>(srcData);
    populateMemoryRandom<float>(filterData);
    test_convolution_sizes_t testConvolutionSizes(
        inputDesc.N, 1, inputDesc.C, inputDesc.H, inputDesc.W, outputDesc.C,
        outputDesc.H, outputDesc.W, filterDesc.H, filterDesc.W, pad[0], pad[1],
        stride[0], stride[1], 1, 1);

  int ip_size[4] = {inputDesc.N, inputDesc.C, inputDesc.H, inputDesc.W};
  int k_size[4] = {filterDesc.N, filterDesc.C, filterDesc.H, filterDesc.W};
  int op_size[4] =  {outputDesc.N, outputDesc.C, outputDesc.H, outputDesc.W};

  std::string str_ip_size  = convert_to_string((int*)ip_size,4);
  std::string str_k_size  = convert_to_string((int*)k_size,4);
  std::string str_op_size  = convert_to_string((int*)op_size,4);

  compute_hipdnn_conv_fwd<float>(testConvolutionSizes, srcData.gpu(),
                                filterData.gpu(), NULL, dstDataGPU.gpu(),&avg_time);

    std::cout << "\nAverage Time is: " << avg_time << "micro seconds"<<std::endl;

    std::string strt = "./result_unittest.csv";
    std::string testname = "convolution_fwd:func_check_two_strides_medium_kernelsize";
    float* temp = dstDataGPU.getDataFromGPU();
    std::string str  = convert_to_string((float*)temp,(int)dstDataGPU.get_num_elements());
    write_to_csv(strt, str, testname,avg_time, str_ip_size, str_k_size, str_op_size);
}

TEST(convolution_fwd, func_check_padding_and_strides_small_size) {
    Desc inputDesc(1, 3, 7, 7);
    Desc filterDesc(21, 3, 3, 3);
    int pad[2] = {2, 2};    // padding 2
    int stride[2] = {2, 2}; // stride 2
    float avg_time = 0;

    Desc outputDesc =
        calculateConv2DOutputDesc(inputDesc, filterDesc, pad, stride);
    Memory<float> srcData = createMemory<float>(inputDesc);
    Memory<float> dstDataCPU = createMemory<float>(outputDesc);
    Memory<float> dstDataGPU = createMemory<float>(outputDesc);
    Memory<float> filterData = createMemory<float>(filterDesc);
    populateMemoryRandom<float>(srcData);
    populateMemoryRandom<float>(filterData);
    test_convolution_sizes_t testConvolutionSizes(
        inputDesc.N, 1, inputDesc.C, inputDesc.H, inputDesc.W, outputDesc.C,
        outputDesc.H, outputDesc.W, filterDesc.H, filterDesc.W, pad[0], pad[1],
        stride[0], stride[1], 1, 1);

  int ip_size[4] = {inputDesc.N, inputDesc.C, inputDesc.H, inputDesc.W};
  int k_size[4] = {filterDesc.N, filterDesc.C, filterDesc.H, filterDesc.W};
  int op_size[4] =  {outputDesc.N, outputDesc.C, outputDesc.H, outputDesc.W};

  std::string str_ip_size  = convert_to_string((int*)ip_size,4);
  std::string str_k_size  = convert_to_string((int*)k_size,4);
  std::string str_op_size  = convert_to_string((int*)op_size,4);

  compute_hipdnn_conv_fwd<float>(testConvolutionSizes, srcData.gpu(),
                                filterData.gpu(), NULL, dstDataGPU.gpu(), &avg_time);

   std::cout << "\nAverage Time is: " << avg_time << "micro seconds"<<std::endl;

    std::string strt = "./result_unittest.csv";
    std::string testname = "convolution_fwd:func_check_padding_and_strides_small_size";
    float* temp = dstDataGPU.getDataFromGPU();
    std::string str  = convert_to_string((float*)temp,(int)dstDataGPU.get_num_elements());
    write_to_csv(strt, str, testname,avg_time, str_ip_size, str_k_size, str_op_size);
}

TEST(convolution_fwd, func_check_full_conv) {
    Desc inputDesc(1, 3, 7, 7);
    Desc filterDesc(3, 3, 7, 7);
    int pad[2] = {0, 0};    // zero padding
    int stride[2] = {1, 1}; // stride 1
    float avg_time = 0;

    Desc outputDesc =
        calculateConv2DOutputDesc(inputDesc, filterDesc, pad, stride);
    Memory<float> srcData = createMemory<float>(inputDesc);
    Memory<float> dstDataCPU = createMemory<float>(outputDesc);
    Memory<float> dstDataGPU = createMemory<float>(outputDesc);
    Memory<float> filterData = createMemory<float>(filterDesc);
    populateMemoryRandom<float>(srcData);
    populateMemoryRandom<float>(filterData);
    test_convolution_sizes_t testConvolutionSizes(
        inputDesc.N, 1, inputDesc.C, inputDesc.H, inputDesc.W, outputDesc.C,
        outputDesc.H, outputDesc.W, filterDesc.H, filterDesc.W, pad[0], pad[1],
        stride[0], stride[1], 1, 1);

  int ip_size[4] = {inputDesc.N, inputDesc.C, inputDesc.H, inputDesc.W};
  int k_size[4] = {filterDesc.N, filterDesc.C, filterDesc.H, filterDesc.W};
  int op_size[4] =  {outputDesc.N, outputDesc.C, outputDesc.H, outputDesc.W};

  std::string str_ip_size  = convert_to_string((int*)ip_size,4);
  std::string str_k_size  = convert_to_string((int*)k_size,4);
  std::string str_op_size  = convert_to_string((int*)op_size,4);

  compute_hipdnn_conv_fwd<float>(testConvolutionSizes, srcData.gpu(),
                                filterData.gpu(), NULL, dstDataGPU.gpu(),&avg_time);
   
 std::cout << "\nAverage Time is: " << avg_time << "micro seconds"<<std::endl;
 
   std::string strt = "./result_unittest.csv";
    std::string testname = "convolution_fwd:func_check_full_conv";
    float* temp = dstDataGPU.getDataFromGPU();
    std::string str  = convert_to_string((float*)temp,(int)dstDataGPU.get_num_elements());
    write_to_csv(strt, str, testname, avg_time, str_ip_size, str_k_size, str_op_size);
}

TEST(convolution_fwd, func_check_dilation1x1_batch64) {
Desc inputDesc(64, 3, 7, 7);
Desc filterDesc(3, 3, 3, 3);
int pad[2] = {2, 2}; // padding 2
int stride[2] = {1, 1}; // stride 1
float avg_time = 0;

Desc outputDesc =
calculateConv2DOutputDesc(inputDesc, filterDesc, pad, stride);
Memory<float> srcData = createMemory<float>(inputDesc);
Memory<float> dstDataCPU = createMemory<float>(outputDesc);
Memory<float> dstDataGPU = createMemory<float>(outputDesc);
Memory<float> filterData = createMemory<float>(filterDesc);
populateMemoryRandom<float>(srcData);
populateMemoryRandom<float>(filterData);
test_convolution_sizes_t testConvolutionSizes(
inputDesc.N, 1, inputDesc.C, inputDesc.H, inputDesc.W, outputDesc.C,
outputDesc.H, outputDesc.W, filterDesc.H, filterDesc.W, pad[0], pad[1],
stride[0], stride[1], 1, 1);

  int ip_size[4] = {inputDesc.N, inputDesc.C, inputDesc.H, inputDesc.W};
  int k_size[4] = {filterDesc.N, filterDesc.C, filterDesc.H, filterDesc.W};
  int op_size[4] =  {outputDesc.N, outputDesc.C, outputDesc.H, outputDesc.W};

  std::string str_ip_size  = convert_to_string((int*)ip_size,4);
  std::string str_k_size  = convert_to_string((int*)k_size,4);
  std::string str_op_size  = convert_to_string((int*)op_size,4);

 compute_hipdnn_conv_fwd<float>(testConvolutionSizes, srcData.gpu(),
                                filterData.gpu(), NULL, dstDataGPU.gpu(),&avg_time);
   
std::cout << "\nAverage Time is: " << avg_time << "micro seconds"<<std::endl;

std::string strt = "./result_unittest.csv";
std::string testname = "convolution_fwd:func_check_dilation1x1_batch64";
float* temp = dstDataGPU.getDataFromGPU();
std::string str = convert_to_string((float*)temp,(int)dstDataGPU.get_num_elements());
write_to_csv(strt, str, testname,avg_time, str_ip_size, str_k_size, str_op_size);
}
