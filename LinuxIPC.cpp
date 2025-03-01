#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

void StringReversal(std::string &word){
    int len = word.length();
    for (int x = 0; x < len/2; x++)
    {
        std::swap(word[x], word[len-x-1]);
    }
}
int main(){
    int pipefd[2];
    pid_t process_id;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    process_id = fork();
    if (process_id == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (process_id == 0)
    {
        close(pipefd[1]);
            char buffer[100];
            ssize_t count = read(pipefd[0], buffer, sizeof(buffer));
            if (count == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }
            std::string received_str(buffer);
            StringReversal(received_str);  // Reverse the string
            std::cout << "[CHILD]: " << received_str << std::endl;
    
            close(pipefd[0]);  // Close the read end
        } else {  // Parent process
            close(pipefd[0]);  // Close the read end
            std::string input;
            std::cout << "[PARENT] Enter a string: ";
            std::getline(std::cin, input);  // Read user input
    
            write(pipefd[1], input.c_str(), input.size() + 1);  // Send to child
            close(pipefd[1]);  // Close the write end
    
            wait(nullptr);  // Wait for the child
        }
        return 0;
    }