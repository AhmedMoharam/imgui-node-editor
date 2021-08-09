#pragma once
#include <iostream>
#define EXEC_NODE_NAME "Exec"

static Node* SpawnExec()
{
	int node_id = GetNextId();
	s_Nodes.emplace_back(node_id, EXEC_NODE_NAME , ImColor(255, 255, 255));
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	s_Nodes.back().setExec([]() -> void {std::cout << "Hello from inside exec" << std::endl; });
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

static Node* SpawnSequence()
{
	s_Nodes.emplace_back(GetNextId(), "Sequence", ImColor(255, 225, 225));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

	s_Nodes.back().setExec([]() -> void {std::cout << "Hello from inside Sequence" << std::endl; });
	BuildNode(&s_Nodes.back());
	return &s_Nodes.back();
}

static Node* SpawnRSI()
{
	s_Nodes.emplace_back(GetNextId(), "RSI", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Stock:", PinType::String);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnMACD()
{
	s_Nodes.emplace_back(GetNextId(), "MACD", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Stock:", PinType::String);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnIchimokuCloud()
{
	s_Nodes.emplace_back(GetNextId(), "IchimokuCloud", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Stock:", PinType::String);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnOBV()
{
	s_Nodes.emplace_back(GetNextId(), "OBV", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Stock:", PinType::String);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

static Node* SpawnWILLIAMS()
{
	s_Nodes.emplace_back(GetNextId(), "WILLIAMS", ImColor(255, 128, 128));
	s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Bool);
	s_Nodes.back().Outputs.emplace_back(GetNextId(), "Stock:", PinType::String);

	BuildNode(&s_Nodes.back());

	return &s_Nodes.back();
}

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
