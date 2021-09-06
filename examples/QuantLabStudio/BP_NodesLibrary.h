#pragma once
#include <iostream>
#include <limits>
#define EXEC_NODE_NAME "Exec"

const bool verbose = false;



static Node* SpawnExec()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, EXEC_NODE_NAME , ImColor(255, 255, 255));
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	s_Nodes.back().setExec([]() -> void {
		if (verbose)
			std::cout << "Hello from inside exec" << std::endl; 
		});
	BuildNode(&s_Nodes.back());
	return &s_Nodes.back();
}

static Node* SpawnNodeA()
{
	s_Nodes.emplace_back(GetNextId(), "Node A", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	s_Nodes.back().setExec([]() -> void {std::cout << "Hello from inside Node A" << std::endl; });
	BuildNode(&s_Nodes.back());
	return &s_Nodes.back();
}

static Node* SpawnNodeB()
{
	s_Nodes.emplace_back(GetNextId(), "Node B", ImColor(255, 0, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	s_Nodes.back().setExec([]() -> void {std::cout << "Hello from inside Node B" << std::endl; });
	BuildNode(&s_Nodes.back());
	return &s_Nodes.back();
}
// Utils ---------------------------------------------------------------------
static Node* SpawnSequence()
{
	s_Nodes.emplace_back(GetNextId(), "Sequence", ImColor(255, 225, 225));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	s_Nodes.back().setExec([]() -> void {
		if (verbose)
			std::cout << "Hello from inside Sequence" << std::endl; 
		});
	BuildNode(&s_Nodes.back());
	return &s_Nodes.back();
}

static Node* SpawnBranch()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "Branch", ImColor(255, 225, 225));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Condition", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "True", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "False", PinType::Flow);

	s_Nodes.back().setExec([node_id]() -> void {
		bool condition = get_bool_input(node_id, 1);
		Node * node = FindNode(node_id);
		if (condition)
		{	
			node->Outputs[0].valid_exec = true;
			node->Outputs[1].valid_exec = false;
			if (verbose)
				std::cout << "Branch: Condition is True " << std::endl;
		}
		else
		{
			node->Outputs[0].valid_exec = false;
			node->Outputs[1].valid_exec = true;
			if (verbose)
				std::cout << "Branch: Condition is False " << std::endl;
		}
				
	});
	BuildNode(&s_Nodes.back());
	return &s_Nodes.back();
}

static Node* SpawnADD()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "+", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float input1 = get_float_input(node_id, 0);
			float input2 = get_float_input(node_id, 1);
			float result = input1 + input2;
			if (verbose)
				std::cout << "ADD " << input1 << "+" << input2 << "=" << result << std::endl;
			set_float_output(node_id, 0, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnSubtract()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "-", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float input1 = get_float_input(node_id, 0);
			float input2 = get_float_input(node_id, 1);
			float result = input1 - input2;
			if (verbose)
				std::cout << "Subtract " << input1 << "-" << input2 << "=" << result << std::endl;
			set_float_output(node_id, 0, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnMultiply()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "x", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float input1 = get_float_input(node_id, 0);
			float input2 = get_float_input(node_id, 1);
			float result = input1 * input2;
			if (verbose)
				std::cout << "Mul " << input1 << "x" << input2 << "=" << result << std::endl;
			set_float_output(node_id, 0, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnDivide()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "/", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float input1 = get_float_input(node_id, 0);
			float input2 = get_float_input(node_id, 1);
			float result = input1 / input2;
			if (verbose)
				std::cout << "Div " << input1 << "/" << input2 << "=" << result << std::endl;
			set_float_output(node_id, 0, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnLessThan()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "<", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float input1 = get_float_input(node_id, 0);
			float input2 = get_float_input(node_id, 1);
			bool result = input1 < input2;
			set_bool_output(node_id, 0, result);
			if (verbose)
				std::cout << "Less Than " << input1 << "<" << input2 << "=" << std::boolalpha << result << std::endl;
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnLessThanOrEqual()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "<=", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float input1 = get_float_input(node_id, 0);
			float input2 = get_float_input(node_id, 1);
			bool result = input1 <= input2;
			set_bool_output(node_id, 0, result);
			if (verbose)
				std::cout << "Less Than Or Equal" << input1 << "<=" << input2 << "=" << std::boolalpha << result << std::endl;
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnMoreThan()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, ">", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float input1 = get_float_input(node_id, 0);
			float input2 = get_float_input(node_id, 1);
			bool result = input1 > input2;
			set_bool_output(node_id, 0, result);
			if (verbose)
				std::cout << "More Than " << input1 << ">" << input2 << "=" << std::boolalpha << result << std::endl;
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnMoreThanOrEqual()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, ">=", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float input1 = get_float_input(node_id, 0);
			float input2 = get_float_input(node_id, 1);
			bool result = input1 >= input2;
			set_bool_output(node_id, 0, result);
			if (verbose)
				std::cout << "More Than Or Equal" << input1 << ">=" << input2 << "=" << std::boolalpha << result << std::endl;
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

// Print ---------------------------------------------------------------------

static Node* SpawnPrintFloat()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "Print", ImColor(75, 0, 130));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "float", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float result = get_float_input(node_id, 1); if (result == std::numeric_limits<float>::infinity()) result = 0.0f;
			Node * node = FindNode(node_id);
			Pin * pin = &(node->Inputs[1]);
			pin->float_data = result;
			std::cout << "Print Float: " << result << std::endl;
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnPrintString()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "Print", ImColor(75, 0, 130));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "String", PinType::String);
	s_Nodes.back().setExec([node_id]() -> void
		{
			const char * result = get_string_input(node_id, 1);
			std::cout << "Print String: " << result << std::endl;
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

// Inputs ---------------------------------------------------------------------
static Node* SpawnStringInputNode()
{
	s_Nodes.emplace_back(GetNextId(), "", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().isInputNode = true;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "String", PinType::String);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnFloatInputNode()
{
	s_Nodes.emplace_back(GetNextId(), "", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().isInputNode = true;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Float", PinType::Float);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

// Trading ---------------------------------------------------------------------
static Node* SpawnRSI()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "RSI", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Stock Name", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "days", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Result", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			const char * stock = get_string_input(node_id, 1);
			float days = get_float_input(node_id, 2);	if (days == std::numeric_limits<float>::infinity())	days = 20;

			float result = py::RSI(stock, static_cast<int>(days));
			if (verbose)
				std::cout << "RSI " << result << std::endl;
			set_float_output(node_id, 1, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnMACD()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "MACD", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Stock Name", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Start Date", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "End Date", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Price Name", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Period 1", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Period 2", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Period 3", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Result", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			const char * stock = get_string_input(node_id, 1);
			const char * start_date = get_string_input(node_id, 2); if (!start_date) start_date = "2020-01-01";
			const char * end_date = get_string_input(node_id, 3);	if (!end_date) end_date = "2021-01-01";
			const char * price_name = get_string_input(node_id, 4);	if (!price_name) price_name = "Close";
			float period1 = get_float_input(node_id, 5);	if (period1 == std::numeric_limits<float>::infinity()) period1 = 26.0f;
			float period2 = get_float_input(node_id, 6);	if (period2 == std::numeric_limits<float>::infinity()) period2 = 12.0f;
			float period3 = get_float_input(node_id, 7);	if (period3 == std::numeric_limits<float>::infinity()) period3 = 9.0f;
			
			float result = py::MACD(stock, start_date, end_date, price_name, static_cast<int>(period1), static_cast<int>(period2), static_cast<int>(period3));
			if (verbose)
				std::cout << "MACD " << result << std::endl;
			set_float_output(node_id, 1, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnIchimokuCloud()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "IchimokuCloud", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Stock Name", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Start Date", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "End Date", PinType::String);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Result", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			const char * stock = get_string_input(node_id, 1);
			const char * start_date = get_string_input(node_id, 2); if (!start_date) start_date = "2019-01-01";
			const char * end_date = get_string_input(node_id, 3);	if (!end_date) end_date = "2021-01-01";

			float result = py::IchimokuCloud(stock, start_date, end_date);
			if (verbose)
				std::cout << "IchimokuCloud " << result << std::endl;
			set_float_output(node_id, 1, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnOBV()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "OBV", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Stock Name", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Start Date", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "End Date", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "days", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Result", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			const char * stock = get_string_input(node_id, 1);
			const char * start_date = get_string_input(node_id, 2); if (!start_date) start_date = "2020-01-01";
			const char * end_date = get_string_input(node_id, 3);	if (!end_date) end_date = "2021-01-01";
			float days = get_float_input(node_id, 4);	if (days == std::numeric_limits<float>::infinity()) days = 14.0f;

			float result = py::OBV(stock, start_date, end_date, static_cast<int>(days));
			if (verbose)
				std::cout << "OBV " << result << std::endl;
			set_float_output(node_id, 1, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnWILLIAMS()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "WILLIAMS", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Stock Name", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Start Date", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "End Date", PinType::String);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "days", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Result", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			const char * stock = get_string_input(node_id, 1);
			const char * start_date = get_string_input(node_id, 2); if (!start_date) start_date = "2020-01-01";
			const char * end_date = get_string_input(node_id, 3);	if (!end_date) end_date = "2021-01-01";
			float days = get_float_input(node_id, 4);	if (days == std::numeric_limits<float>::infinity()) days = 14.0f;
			float result = py::WILLIAMS(stock, start_date, end_date, static_cast<int>(days));
			if (verbose)
				std::cout << "WILLIAMS " << result << std::endl;
			set_float_output(node_id, 1, result);
		});

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnBacktesting()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, "Backtesting", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "commission", PinType::Float);
	s_Nodes.back().setExec([node_id]() -> void
		{
			float commission = get_float_input(node_id, 1);	if (commission == std::numeric_limits<float>::infinity()) commission = 0.002f;
			char const * result = py::backtesting(commission);
			s_BackTestingImage = Application_LoadTexture("backtesting.png");
			s_BackTestingResult.appendf("%s", result);
			if (verbose)
				std::cout << "Backtesting " << std::endl;
		});
	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

// -------------------------------------------------------------------------------------------------------------------------------------

static Node* SpawnInputActionNode()
{
	s_Nodes.emplace_back(GetNextId(), "InputAction Fire", ImColor(255, 128, 128));
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Delegate);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Pressed", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Released", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnBranchNode()
{
	s_Nodes.emplace_back(GetNextId(), "Branch");
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Condition", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "True", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "False", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnDoNNode()
{
	s_Nodes.emplace_back(GetNextId(), "Do N");
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Enter", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "N", PinType::Int);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Reset", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Exit", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Counter", PinType::Int);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnOutputActionNode()
{
	s_Nodes.emplace_back(GetNextId(), "OutputAction");
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Sample", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Condition", PinType::Bool);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Event", PinType::Delegate);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnPrintStringNode()
{
	s_Nodes.emplace_back(GetNextId(), "Print String");
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "In String", PinType::String);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnMessageNode()
{
	s_Nodes.emplace_back(GetNextId(), "", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Message", PinType::String);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnSetTimerNode()
{
	s_Nodes.emplace_back(GetNextId(), "Set Timer", ImColor(128, 195, 248));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Object", PinType::Object);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Function Name", PinType::Function);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Time", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Looping", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnLessNode()
{
	s_Nodes.emplace_back(GetNextId(), "<", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnWeirdNode()
{
	s_Nodes.emplace_back(GetNextId(), "o.O", ImColor(128, 195, 248));
	s_Nodes.back().Type = NodeType::Simple;
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnTraceByChannelNode()
{
	s_Nodes.emplace_back(GetNextId(), "Single Line Trace by Channel", ImColor(255, 128, 64));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Start", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "End", PinType::Int);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Trace Channel", PinType::Float);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Trace Complex", PinType::Bool);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Actors to Ignore", PinType::Int);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Draw Debug Type", PinType::Bool);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "Ignore Self", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Out Hit", PinType::Float);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Return Value", PinType::Bool);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnTreeSequenceNode()
{
	s_Nodes.emplace_back(GetNextId(), "Sequence");
	s_Nodes.back().Type = NodeType::Tree;
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnTreeTaskNode()
{
	s_Nodes.emplace_back(GetNextId(), "Move To");
	s_Nodes.back().Type = NodeType::Tree;
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnTreeTask2Node()
{
	s_Nodes.emplace_back(GetNextId(), "Random Wait");
	s_Nodes.back().Type = NodeType::Tree;
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnComment()
{
	s_Nodes.emplace_back(GetNextId(), "Test Comment");
	s_Nodes.back().Type = NodeType::Comment;
	s_Nodes.back().Size = ImVec2(300, 200);

	return &s_Nodes.back();
}

static Node* SpawnHoudiniTransformNode()
{
	s_Nodes.emplace_back(GetNextId(), "Transform");
	s_Nodes.back().Type = NodeType::Houdini;
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnHoudiniGroupNode()
{
	s_Nodes.emplace_back(GetNextId(), "Group");
	s_Nodes.back().Type = NodeType::Houdini;
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}
