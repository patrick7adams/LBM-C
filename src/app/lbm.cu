// #include "lbm.cuh"

// void initialize_cuda(float* distances, float* directional_densities, float* directional_densities_tmp, float* densities, float* ux, float* uy, int* walls) {
//     float* cuda_distances, cuda_directional_densities, cuda_directional_densities_tmp, cuda_densities, cuda_ux, cuda_uy;
//     int* cuda_walls;
//     cudaMalloc(&cuda_distances, totalPoints*sizeof(float));
//     cudaMalloc(&cuda_directional_densities, totalPoints*9*sizeof(float));
//     cudaMalloc(&cuda_directional_densities_tmp, totalPoints*9*sizeof(float));
//     cudaMalloc(&cuda_densities, totalPoints*sizeof(float));
//     cudaMalloc(&cuda_ux, totalPoints*sizeof(float));
//     cudaMalloc(&cuda_uy, totalPoints*sizeof(float));
//     cudaMalloc(&cuda_walls, totalPoints*sizeof(int));
    
//     cudaMemcpy(cuda_directional_densities, directional_densities, totalPoints*9*sizeof(float), cudaMemcpyHostToDevice)
// }