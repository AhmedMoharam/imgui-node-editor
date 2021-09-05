#include <boost/python.hpp>
#include "application.h"
#include <iostream>
#include <string>
#include <thread>

class Py_Trading {
public:
	Py_Trading();
	float RSI(const char *, int);
	float OBV(const char *stock, const char *start_date, const char *end_date, int days);
	float MACD(const char *stock, const char *start_date, const char *end_date,const char *price_name,int period1, int period2, int period3);
	float IchimokuCloud(const char *stock, const char *start_date, const char *end_date);
	float WILLIAMS(const char *stock, const char *start_date, const char *end_date, int days);
	virtual ~Py_Trading();
private:
	void init();
	void wait_init_done();
	boost::python::object Trading_object;
	std::thread init_thread;
};


int setenv(const char *name, const char *value, int overwrite)
{
	int errcode = 0;
	if (!overwrite) {
		size_t envsize = 0;
		errcode = getenv_s(&envsize, NULL, 0, name);
		if (errcode || envsize) return errcode;
	}
	return _putenv_s(name, value);
}


Py_Trading::Py_Trading()
{
	init_thread = std::thread(&Py_Trading::init, this);
}

Py_Trading::~Py_Trading()
{
	wait_init_done();
}


void Py_Trading::init()
{
	setenv("PYTHONHOME", "python-venv", 1);
	setenv("PYTHONPATH", "python-venv", 1);
	Py_Initialize();
	try
	{
		boost::python::object trading_module = boost::python::import("Trading");
		Trading_object = trading_module.attr("TradingClass")();
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		exit(1);
	}
}

void Py_Trading::wait_init_done()
{
	if (init_thread.joinable())
		init_thread.join();
}
float Py_Trading::RSI(const char *stock,int days)
{
	wait_init_done();
	try
	{

		boost::python::object value = Trading_object.attr("RSI")(stock, days);
		return boost::python::extract<float>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		return 0.0f;
	}

}

float Py_Trading::OBV(const char *stock, const char *start_date, const char *end_date, int days)
{
	wait_init_done();
	try
	{
		boost::python::object value = Trading_object.attr("OBV")(stock, start_date, end_date, days);
		return boost::python::extract<float>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		return 0.0f;
	}
}

float Py_Trading::MACD(const char *stock, const char *start_date, const char *end_date, const char *price_name, int period1, int period2, int period3)
{
	wait_init_done();
	try
	{
		//2020-01-01
		//2021-01-01
		boost::python::object value = Trading_object.attr("MACD")(stock, start_date, end_date, price_name, period1, period2, period3);
		return boost::python::extract<float>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		return 0.0f;
	}
}

float Py_Trading::IchimokuCloud(const char *stock, const char *start_date, const char *end_date)
{
	wait_init_done();
	try
	{
		boost::python::object value = Trading_object.attr("IchimokuCloud")(stock, start_date, end_date);
		return boost::python::extract<float>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		return 0.0f;
	}
}

float Py_Trading::WILLIAMS(const char *stock, const char *start_date, const char *end_date, int days)
{
	wait_init_done();
	try
	{
		boost::python::object value = Trading_object.attr("WILLIAMS")(stock, start_date, end_date, days);
		return boost::python::extract<float>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		return 0.0f;
	}
}


static Py_Trading obj;

float py::RSI(const char *stock, int days)
{
	return obj.RSI(stock, days);
}

float py::OBV(const char *stock, const char *start_date, const char *end_date, int days)
{
	return obj.OBV(stock, start_date, end_date, days);
}

float py::MACD(const char *stock, const char *start_date, const char *end_date, const char *price_name, int period1, int period2, int period3)
{
	return obj.MACD(stock, start_date, end_date, price_name, period1, period2, period3);
}

float py::IchimokuCloud(const char *stock, const char *start_date, const char *end_date)
{
	return obj.IchimokuCloud(stock, start_date, end_date);
}

float py::WILLIAMS(const char *stock, const char *start_date, const char *end_date, int days)
{
	return obj.WILLIAMS(stock, start_date, end_date, days);
}


