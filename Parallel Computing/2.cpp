#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <chrono>
#include <vector>

void child_process(int read_fd, int write_fd) {
    close(read_fd); 

    
    int result = 0;
    for (int i = 0; i < 100000; ++i) {
        result += i;
    }

    
    write(write_fd, &result, sizeof(result));
    close(write_fd); 
    exit(0);
}

void parent_process(int read_fd, int write_fd) {
    close(write_fd); 

    
    int result;
    read(read_fd, &result, sizeof(result));
    std::cout << "Result from child process: " << result << std::endl;
    close(read_fd); 
}

int main() {
    int sample_sizes[] = {5000, 50000, 500000};
    std::vector<double> execution_times;

    for (int sample_size : sample_sizes) {
        auto start = std::chrono::high_resolution_clock::now();

        int fd[2];
        if (pipe(fd) == -1) {
            std::cerr << "Pipe failed" << std::endl;
            return 1;
        }

        pid_t pid = fork();
        if (pid < 0) {
            std::cerr << "Fork failed" << std::endl;
            return 1;
        }

        if (pid == 0) {
            
            child_process(fd[0], fd[1]);
        } else {
            
            parent_process(fd[0], fd[1]);
            wait(NULL); 
        }

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
