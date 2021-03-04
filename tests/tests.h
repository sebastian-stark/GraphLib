#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

std::ofstream graph_lib_log;

/**
 * initialize logging (open a file stream into which log output can be written)
 */
void initlog(int argc, char *argv[])
{
	const std::string log_file_name = std::string(argv[0]) + "_.log";
	graph_lib_log.open(log_file_name.c_str());
}

/**
 * stop logging (compare the output of the program with sample output)
 */
int stoplog(int argc, char *argv[])
{
	graph_lib_log.close();
	const std::string log_file_name = std::string(argv[0]) + "_.log";
	const std::string comparison_log_file_name = std::string(argv[0]) + ".log";
	std::ifstream log_file(log_file_name.c_str());
	std::ifstream comparison_log_file(comparison_log_file_name.c_str());
	std::stringstream log_file_ss, comparison_log_file_ss;
	log_file_ss << log_file.rdbuf();
	comparison_log_file_ss << comparison_log_file.rdbuf();
	std::cout << comparison_log_file_ss.str() << std::endl << std::endl;
	std::cout << log_file_ss.str() << std::endl;
	return (comparison_log_file_ss.str() != log_file_ss.str());
}

