/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <csignal>
#include <filesystem>
#include <mutex>

#define PORT 8080
#define BUFFER_SIZE 1024
#define ROOT_DIR "./static"

int server_fd;
std::mutex cout_mutex; // Mutex for thread-safe std::cout usage

void signal_handler(int signal) {
    std::cout << "\nShutting down the server..." << std::endl;
    close(server_fd);
    exit(0);
}

std::string get_content_type(const std::string& path) {
    // Check file extension by comparing the substring of the last part of the path
    if (path.size() >= 5 && path.compare(path.size() - 5, 5, ".html") == 0) return "text/html";
    if (path.size() >= 4 && path.compare(path.size() - 4, 4, ".css") == 0) return "text/css";
    if (path.size() >= 3 && path.compare(path.size() - 3, 3, ".js") == 0) return "application/javascript";
    if (path.size() >= 4 && path.compare(path.size() - 4, 4, ".png") == 0) return "image/png";
    if ((path.size() >= 4 && path.compare(path.size() - 4, 4, ".jpg") == 0) || 
        (path.size() >= 5 && path.compare(path.size() - 5, 5, ".jpeg") == 0)) return "image/jpeg";
    return "text/plain";
}

bool is_safe_path(const std::string& path) {
    // Prevent directory traversal outside of the ROOT_DIR
    return path.find("..") == std::string::npos && path.find(ROOT_DIR) == 0;
}

void serve_file(int client_socket, const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (file) {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::string response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: " + get_content_type(file_path) + "\r\n"
            "Content-Length: " + std::to_string(content.size()) + "\r\n\r\n" + content;
        if (send(client_socket, response.c_str(), response.size(), 0) == -1) {
            std::cerr << "[ERROR] Failed to send response." << std::endl;
        } else {
            std::cout << "[INFO] Served file: " << file_path << std::endl;
        }
    } else {
        const char* not_found_response = 
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 44\r\n\r\n"
            "<html><body><h1>404 Not Found</h1></body></html>";
        if (send(client_socket, not_found_response, strlen(not_found_response), 0) == -1) {
            std::cerr << "[ERROR] Failed to send 404 response." << std::endl;
        } else {
            std::cout << "[ERROR] File not found: " << file_path << std::endl;
        }
    }
    close(client_socket);
    std::lock_guard<std::mutex> guard(cout_mutex);
    std::cout << "[INFO] Connection closed for client." << std::endl;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_read <= 0) {
        std::cerr << "[ERROR] Failed to read request." << std::endl;
        close(client_socket);
        return;
    }

    std::string request(buffer);
    std::string file_path = request.substr(request.find(' ') + 1);
    file_path = file_path.substr(0, file_path.find(' '));

    if (file_path == "/") {
        file_path = "/index.html";
    }

    std::string full_path = std::string(ROOT_DIR) + file_path;

    // Ensure the path is safe
    if (!is_safe_path(full_path)) {
        const char* forbidden_response = 
            "HTTP/1.1 403 Forbidden\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: 44\r\n\r\n"
            "<html><body><h1>403 Forbidden</h1></body></html>";
        if (send(client_socket, forbidden_response, strlen(forbidden_response), 0) == -1) {
            std::cerr << "[ERROR] Failed to send 403 response." << std::endl;
        }
        close(client_socket);
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::cout << "[ERROR] Forbidden access attempt to: " << full_path << std::endl;
        return;
    }

    serve_file(client_socket, full_path);
}

int main() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    signal(SIGINT, signal_handler);

    std::cout << "[INFO] Creating socket..." << std::endl;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        std::cerr << "[ERROR] Socket creation failed: " << strerror(errno) << std::endl;
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    std::cout << "[INFO] Binding socket to port " << PORT << "..." << std::endl;
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "[ERROR] Bind failed: " << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << "[INFO] Listening for connections..." << std::endl;
    if (listen(server_fd, 3) < 0) {
        std::cerr << "[ERROR] Listen failed: " << strerror(errno) << std::endl;
        return -1;
    }

    std::cout << "[INFO] Server running on port " << PORT << std::endl;

    while (true) {
        std::cout << "[INFO] Waiting for a client connection..." << std::endl;
        int client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (client_socket < 0) {
            std::cerr << "[ERROR] Accept failed: " << strerror(errno) << std::endl;
            continue;
        }

        std::cout << "[INFO] Client connected, handling request..." << std::endl;

        std::thread t(handle_client, client_socket);
        t.detach();
    }

    return 0;
}