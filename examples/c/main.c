#include<stdio.h>
#include<string.h>
#include<CL/cl.h>
void print(float *a)
{
	printf("%f %f %f\n", a[0], a[1], a[2]);
}
char* read(char *filename)
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
	printf("PROGRAM: size %d bytes\n", filesize);
	printf("---------------------\n");
	printf("%s\n", buffer);
	printf("---------------------\n");
	
	return buffer;
}
int main()
{
	const char * kernelSource = read("./fill.cl");
	cl_platform_id platform;
	clGetPlatformIDs(1, &platform, NULL);
	cl_device_id device;
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
	cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
	cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);
	cl_program program = clCreateProgramWithSource(context, 1, (const char**) &kernelSource, strlen(kernelSource), NULL);
	clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	cl_kernel kernel = clCreateKernel(program, "fill", NULL);
	{
		unsigned int n = 3;
		float *h_a = malloc(n*sizeof(float));
		print(h_a);
		cl_mem d_a = clCreateBuffer(context, CL_MEM_READ_WRITE, n*sizeof(float), NULL, NULL);

		clEnqueueWriteBuffer(queue, d_a, CL_FALSE, 0, n*sizeof(float), h_a, 0, NULL, NULL);
		clSetKernelArg(kernel, 0, sizeof(cl_mem), &d_a);
		float X = 3.15;
		clSetKernelArg(kernel, 1, sizeof(float), &X);
		size_t global_dim = 3;
		size_t local_dim = 3;
		clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &global_dim, &local_dim, 0, NULL, NULL);
		clEnqueueReadBuffer(queue, d_a, CL_FALSE, 0, n*sizeof(float), h_a, 0, NULL, NULL);
		clFinish(queue);
		print(h_a);
		clReleaseMemObject(d_a);
	}
	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(queue);
	clReleaseContext(context);
}
