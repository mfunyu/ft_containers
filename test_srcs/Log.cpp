#include "UnitTester.hpp"
#include <iostream>

const std::string Log::k_logfile            = "result.log";
std::string       Log::_current_explanation = "";

Log::Log()
{
	_open_logfile();
}

Log::~Log() {}

void Log::set_explanation(std::string explanation)
{
	_current_explanation = explanation;
}

void Log::write_to_logfile(t_unit_tests& current_test)
{
	_logfile_stream << current_test.func_name << ": ";
	if (current_test.result == TEST_SUCCESS)
		_logfile_stream << "[PASS]" << std::endl;
	else
		_logfile_stream << "[FAIL: " << _current_explanation << "]"
		                << std::endl;
}

void Log::_open_logfile()
{
	_logfile_stream.open(k_logfile, std::ios::out);
	if (!_logfile_stream.good())
		throw std::runtime_error("open");
}
