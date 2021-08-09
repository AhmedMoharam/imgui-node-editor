#include <boost/python.hpp>
#include "application.h"
#include <iostream>
#include <string>

class Py_Trading {
public:
	Py_Trading();
	double RSI(const char *);
	int OBV(const char *);
	double MACD(const char *);
	double IchimokuCloud(const char *);
	float WILLIAMS(const char *);
	virtual ~Py_Trading() {}
private:
	boost::python::object Trading_object;
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
		//exit(1);
	}
}

double Py_Trading::RSI(const char *stock)
{

	try
	{

		boost::python::object value = Trading_object.attr("RSI")(stock);
		return boost::python::extract<double>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		//exit(1);
	}

}

int Py_Trading::OBV(const char *stock)
{
	try
	{
		boost::python::object value = Trading_object.attr("OBV")(stock);
		return boost::python::extract<int>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		//exit(1);
	}
}

double Py_Trading::MACD(const char *stock)
{
	try
	{
		boost::python::object value = Trading_object.attr("MACD")(stock);
		return boost::python::extract<double>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		//exit(1);
	}
}

double Py_Trading::IchimokuCloud(const char *stock)
{
	try
	{
		boost::python::object value = Trading_object.attr("IchimokuCloud")(stock);
		return boost::python::extract<double>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		//exit(1);
	}
}

float Py_Trading::WILLIAMS(const char *stock)
{
	try
	{
		boost::python::object value = Trading_object.attr("WILLIAMS")(stock);
		return boost::python::extract<float>(value);;
	}
	catch (const boost::python::error_already_set&)
	{
		std::cerr << "Error! Python Failed" << std::endl;
		PyErr_Print();
		//exit(1);
	}
}


static Py_Trading obj;

double py::RSI(const char * stock)
{
	return obj.RSI(stock);
}


double py::OBV(const char *stock)
{
	return obj.OBV(stock);
}

double py::MACD(const char *stock)
{
	return obj.MACD(stock);
}

double py::IchimokuCloud(const char *stock)
{
	return obj.IchimokuCloud(stock);
}

double py::WILLIAMS(const char *stock)
{
	return obj.WILLIAMS(stock);
}


