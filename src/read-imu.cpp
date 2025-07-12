#include "read-imu.h"

bool en_newline {false}; // flag to enable newline after each print
char imu_name[64];

void print_usage()
{
	std::cout << "\n"
		"voxl-read-imu-cpp-example - A simple example to read IMU data from VOXL\n" 
		"\nCommand line arguments are as follows: \n\n"
		"-i, --input_imu             imu pipe to show imu data\n"
		"-n, --new_line              print data on new line\n"
		"-h, --help                  print this help message\n"
		"\n"
	<< std::endl;

	return;
}  

int parse_opts(const int argc, char* argv[])
{
	static struct option LongOptions[] =
	{
		{"help",          no_argument,        0, 'h'},
		{"input_imu",     required_argument,  0, 'i'},
		{"new_line",      no_argument,        0, 'n'},
	};

	int optionIndex {0};
	int status {0};
	int option {0};

	while ((status == 0) && (option = getopt_long (argc, argv, "hi:n", LongOptions, &optionIndex)) != -1)
	{
		switch(option)
		{
			case 'h':
				status = -1;
				break;

			case 'i':
				sscanf(optarg, "%s", imu_name);
				break;

			case 'n':
				en_newline = true;
				break;

			// Unknown argument
			case '?':
			default:
				std::cout << "Invalid argument passed!" << std::endl;
				status = -1;
				break;
		}
	}

	if(status != 0) return status;

	if(strlen(imu_name) == 0)
	{
		std::cout << "Missing required argument: input imu\n" << std::endl;
		return -1;
	}

	return status;
}

// called when the simple helper has data for us
void helper_cb([[maybe_unused]] int ch, char* data, int bytes, [[maybe_unused]] void* context)
{
    // validate that the data makes sense
	int n_packets {0};
	imu_data_t* data_array = pipe_validate_imu_data_t(data, bytes, &n_packets);
	if (data_array == NULL) 
        return;

	// print latest packet
	if (!en_newline) 
        std::cout << "\r" << CLEAR_LINE;
	
	// std::cout << "Latest IMU data: " << n_packets << " packets received." << std::endl;

	std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(7) << data_array[n_packets-1].accl_ms2[0] << "|"
			  << std::setw(7) << data_array[n_packets-1].accl_ms2[1] << "|"
			  << std::setw(7) << data_array[n_packets-1].accl_ms2[2] << "|"
			  << std::setw(7) << data_array[n_packets-1].gyro_rad[0] << "|"
			  << std::setw(7) << data_array[n_packets-1].gyro_rad[1] << "|"
			  << std::setw(7) << data_array[n_packets-1].gyro_rad[2] ;

	std::cout << std::defaultfloat << std::flush;
 
	if (en_newline) 
        std::cout << std::endl;

	return;
}

void connect_cb([[maybe_unused]] int ch, [[maybe_unused]] void* context)
{	
	std::cout << "VOXL Hello Cross!!!!!\n" << std::endl;
	std::cout << "   IMU Acceleration and Gyro Data\n";
	std::cout << "   X   |   Y   |   Z   |   X   |   Y   |   Z   \n" << std::endl;
	return;
}

void disconnect_cb([[maybe_unused]] int ch, [[maybe_unused]] void* context)
{
	std::cerr << "\r" << CLEAR_LINE FONT_BLINK "Disconnected from go-single-waypoint-server" RESET_FONT << std::endl;
	return;
}