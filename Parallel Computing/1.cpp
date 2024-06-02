#include <iostream>
#include <vector>
#include <random>
#include <chrono>

void sampling(int num_samples, std::vector<int>& histogram) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    for (int i = 0; i < num_samples; ++i) {
        int counter = 0;
        for (int j = 0; j < 12; ++j) {
            int random_number = dis(gen);
            if (random_number >= 49) {
                counter++;
            }
        }
        histogram[counter]++;
    }
}

int main() {
    int sample_sizes[] = {5000, 50000, 500000};
    std::vector<double> execution_times;

    for (int sample_size : sample_sizes) {
        std::vector<int> histogram(25, 0); 

        auto start = std::chrono::high_resolution_clock::now();
        
        sampling(sample_size, histogram);
        
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        execution_times.push_back(duration.count());
    }

    
    std::cout << "Execution times for different sample sizes:\n";
    for (int i = 0; i < execution_times.size(); ++i) {
        std::cout << "Sample size: " << sample_sizes[i] << ", Execution time: " << execution_times[i] << " seconds\n";
    }

    return 0;
}
