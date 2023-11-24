// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant
// 2023/11/17 - Cornel

#include <string>
#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <thread>
#include "process_data.h"

namespace sdds
{
	// The following function receives array (pointer) as the first argument, number of array 
	//   elements (size) as second argument, divisor as the third argument, and avg as fourth argument. 
	//   size and divisor are not necessarily same. When size and divisor hold same value, avg will 
	//   hold average of the array elements. When they are different, avg will hold a value called 
	// 	 as average-factor. For part 1, you will be using same value for size and double. Use of 
	//   different values for size and divisor will be useful for multi-threaded implementation in part-2. 
	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	// The following function receives array (pointer) as the first argument, number of array elements  
	//   (size) as second argument, divisor as the third argument, computed average value of the data items
	//   as fourth argument, and var as fifth argument. Size and divisor are not necessarily same as in the 
	//   case of computeAvgFactor. When size and divisor hold same value, var will get total variance of 
	//   the array elements. When they are different, var will hold a value called as variance factor. 
	//   For part 1, you will be using same value for size and double. Use of different values for size 
	//   and divisor will be useful for multi-threaded implementation in part-2. 
	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}

	// The following constructor of the functor receives name of the data file, opens it in 
	//   binary mode for reading, reads first int data as total_items, allocate memory space 
	//   to hold the data items, and reads the data items into the allocated memory space. 
	//   It prints first five data items and the last three data items as data samples. 
	//   
	ProcessData::ProcessData(const std::string& filename, int n_threads) {  
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.


		std::ifstream file(filename, std::ios::binary);

		if (file)
		{
			file.read(reinterpret_cast<char*>(&total_items), sizeof(int));

			data = new int[total_items];

			file.read(reinterpret_cast<char*>(data), sizeof(int) * total_items);
		}


		file.close();

		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]" << std::endl;

		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads; i++)
			p_indices[i] = i * (total_items / num_threads);
		p_indices[num_threads] = total_items;
	}
	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	ProcessData::operator bool() const {
		return total_items > 0 && data;
	}

	int ProcessData::operator()(const std::string& target_file, double& avg, double& var)
	{

		if (data != nullptr && num_threads > 0)
		{
			double tempAvg{};
			auto compute = std::bind(computeAvgFactor, std::placeholders::_1, std::placeholders::_2, total_items, std::placeholders::_3);

			std::thread* threads = new std::thread[total_items];
			for (auto i = 0; i < total_items; i++)
			{
				threads[i](compute(data[i], p_indices[i], tempAvg));
				avg += tempAvg;
			}


			computeVarFactor(data, total_items, total_items, avg, var);
		}

		std::ofstream file(target_file, std::ios::binary);

		if (file)
		{
			file.write(reinterpret_cast<char*>(&total_items), sizeof(int));

			file.write(reinterpret_cast<char*>(data), sizeof(int) * total_items);

		}
		else
		{
			throw std::string("Exception");
		}

		file.close();

		return 1;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
	//   function logic for the computation of average and variance by running the 
	//   function computeAvgFactor and computeVarFactor in multile threads. 
	// The function divides the data into a number of parts, where the number of parts is 
	//   equal to the number of threads. Use multi-threading to compute average-factor for 
	//   each part of the data by calling the function computeAvgFactor. Add the obtained 
	//   average-factors to compute total average. Use the resulting total average as the 
	//   average value argument for the function computeVarFactor, to compute variance-factors 
	//   for each part of the data. Use multi-threading to compute variance-factor for each 
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument fname_target. 
	// Also, read the workshop instruction.



	int ProcessData::operator()(const std::string& target_file, double& total_avg, double& total_var) {
		if (!data) return 0;  

		
		std::vector<std::thread> threads;
		threads.reserve(num_threads);

		double tempAvg{};
		double totalAvg{};

		auto computeAvg = std::bind(computeAvgFactor, std::placeholders::_1, std::placeholders::_2, total_items, std::ref(std::placeholders::_3));

		for (int i = 0; i < num_threads; ++i) {
			int partition_size = p_indices[i + 1] - p_indices[i];
			/*auto computeAvg = std::bind(computeAvgFactor, data + p_indices[i], partition_size, total_items, std::ref(averages[i]));*/

			threads.emplace_back(computeAvg(data + p_indices[i], partition_size, tempAvg));
		}

		
		for (auto& t : threads) {
			t.join();
		}

		
		total_avg = 0;
		for (int i = 0; i < num_threads; ++i) {
			total_avg += averages[i];
		}

		
		threads.clear();
		for (int i = 0; i < num_threads; ++i) {
			int partition_size = p_indices[i + 1] - p_indices[i];
			auto computeVar = std::bind(computeVarFactor, data + p_indices[i], partition_size, total_items, total_avg, std::ref(variances[i]));
			threads.emplace_back(computeVar);
		}

		for (auto& t : threads) {
			t.join();
		}

		
		total_var = 0;
		for (int i = 0; i < num_threads; ++i) {
			total_var += variances[i];
		}

		
		std::ofstream file(target_file, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Unable to open target file for writing.");
		}

		file.write(reinterpret_cast<char*>(&total_items), sizeof(total_items));
		file.write(reinterpret_cast<char*>(data), sizeof(int) * total_items);
		if (!file) {
			throw std::runtime_error("Error occurred while writing to file.");
		}

		return 1;
	}







}
