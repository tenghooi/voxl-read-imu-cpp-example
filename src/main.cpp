#include <iostream>
#include <string>
#include <unistd.h>
#include <getopt.h>

#include "read-imu.h"
                   
int main(int argc, char** argv)
{           
    if (parse_opts(argc, argv))
	{
		print_usage();
		return -1;
	}

	enable_signal_handler();
	main_running = 1;
	std::cout << "Subscribing to pipe: " << imu_name << std::endl;

	pipe_client_set_connect_cb(CH, connect_cb, nullptr);
	pipe_client_set_disconnect_cb(CH, disconnect_cb, nullptr);
	pipe_client_set_simple_helper_cb(CH, helper_cb, nullptr);

	int ret = pipe_client_open(CH, imu_name, CLIENT_NAME, CLIENT_FLAG_EN_SIMPLE_HELPER, IMU_RECOMMENDED_READ_BUF_SIZE);
	if (ret < 0)
	{
		pipe_print_error(ret);
		return -1;
	}

	while (main_running)
		usleep(500000);
	
	pipe_client_close_all();

    return 0;
}