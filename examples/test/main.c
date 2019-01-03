#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<CL/cl.h>
void print(float *a)
{
	printf("%f %f %f\n", a[0], a[1], a[2]);
}
char* read_file(char *filename)
{
	FILE *fp = fopen (filename , "rb" );
	if(!fp)
	{
		perror(filename);
		exit(1);
	}
	fseek(fp, 0L, SEEK_END);
	long filesize = ftell(fp);
	rewind(fp);
	char *buffer = malloc((filesize+1)*sizeof(char));
	if(!buffer)
	{	
		fclose(fp);
		fputs("memory alloc fails",stderr);
		exit(1);
	}
	if(1 != fread(buffer, filesize, 1, fp))
	{
		fclose(fp);
		free(buffer);
		fputs("entire read fails",stderr);
		exit(1);
	}
	buffer[filesize] = '\0';
	fclose(fp);
	printf("---------------------\n");
	printf("PROGRAM: size %ld bytes\n", filesize);
	printf("---------------------\n");
	printf("%s\n", buffer);
	printf("---------------------\n");
	
	return buffer;
}
char string[1024];
int main()
{
	cl_int err;
	char * kernelSource = read_file("./fill.cl");
	size_t kernelLength = strlen(kernelSource);
	cl_platform_id platforms[3];
	clGetPlatformIDs(3, &(platforms[0]), NULL);
	cl_platform_id platform = platforms[1]; //SET PLATFORM
	{
		clGetPlatformInfo(platform, CL_PLATFORM_NAME, 1024*sizeof(char)*sizeof(char), &(string[0]), NULL);
		printf("Platform: %s\n", &(string[0]));
	}
	cl_device_id device;
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
	{
		clGetDeviceInfo(device, CL_DEVICE_NAME, 1024*sizeof(char)*sizeof(char), &(string[0]), NULL);
		printf("Device: %s\n", &(string[0]));
	}
	cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &err);
	if (CL_SUCCESS != err)
	{
		printf("Create Context failed!\n");
		__builtin_trap();
	}

	//get device cl version
	clGetDeviceInfo(device, CL_DEVICE_VERSION, 1024*sizeof(char), &(string[0]), NULL);
	cl_command_queue queue;
	cl_command_queue_properties properties[] = {0};
	queue = clCreateCommandQueueWithProperties(context, device, &(properties[0]), NULL);

	cl_program program = clCreateProgramWithSource(context, 1, (const char**) &kernelSource, &kernelLength, &err);
	if (CL_SUCCESS != err)
	{
		printf("Create Program failed!\n");
		__builtin_trap();
	}
	clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	cl_build_status status;
	while (1)
	{
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &status, NULL);
		if (CL_BUILD_IN_PROGRESS != status)
			break;
	}
	if (CL_BUILD_SUCCESS != status)
	{
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 1024*sizeof(char), &(string[0]),NULL);
		printf("Build log:\n%s\n", string);
		__builtin_trap();
	}

	cl_kernel kernel = clCreateKernel(program, "fill", &err);
	if (CL_SUCCESS != err)
	{
		printf("Create Kernel failed!\n");
		__builtin_trap();
	}
	{
		unsigned int n = 3;
		float *h_a = malloc(n*sizeof(float));
		h_a[0] = 1;h_a[1] = 1;h_a[2] = 1;
		print(h_a);
		cl_mem d_a = clCreateBuffer(context, CL_MEM_READ_WRITE, n*sizeof(float), NULL, NULL);

		clEnqueueWriteBuffer(queue, d_a, CL_FALSE, 0, n*sizeof(float), h_a, 0, NULL, NULL);
		clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
		cl_float x = 3.16;
		clSetKernelArg(kernel, 1, sizeof(cl_float), &x);
		size_t global_dim = 3;
		size_t local_dim = 3;
		clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_dim, &local_dim, 0, NULL, NULL);
		clEnqueueReadBuffer(queue, d_a, CL_FALSE, 0, n*sizeof(float), h_a, 0, NULL, NULL);
		clFinish(queue);
		print(h_a);
		clReleaseMemObject(d_a);
		free(h_a);
	}
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
	free(kernelSource);
}
