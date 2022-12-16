#include "../include/server.h"

#include <string>
#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
    wrz_server::Web_Server server(5000, "192.168.106.157");
    server.run();
}