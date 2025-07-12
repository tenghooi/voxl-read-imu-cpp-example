#ifndef READ_IMU_H
#define READ_IMU_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <unistd.h>
#include <getopt.h>
#include <vector>

#include <modal_pipe.h>
#include <voxl_cutils.h>

#define CLIENT_NAME "read-imu-cpp-example"
#define CH 1

extern bool en_newline;
extern char imu_name[];

void print_usage();
int parse_opts(const int argc, char* argv[]);

void helper_cb([[maybe_unused]] int ch, char* data, int bytes, [[maybe_unused]] void* context);
void connect_cb(int, void*);
void disconnect_cb(int, void*);

#endif // READ_IMU_H