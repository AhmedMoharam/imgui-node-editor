#pragma once
#include <imgui_node_editor.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <limits>
using namespace ax;
namespace ed = ax::NodeEditor;


enum class PinType
{
	Flow,
	Bool,
	Int,
	Float,
	String,
	Object,
	Function,
	Delegate,
};

enum class PinKind
{
	Output,
	Input
};

enum class NodeType
{
	Blueprint,
	Simple,
	Tree,
	Comment,
	Houdini
};

struct Node;

struct Pin
{
	ed::PinId   ID;
	::Node*     Node;
	std::string Name;
	PinType     Type;
	PinKind     Kind;
	bool valid_exec;

	Pin(int id, const char* name, PinType type) :
		ID(id), Node(nullptr), Name(name), Type(type), Kind(PinKind::Input), valid_exec(true), bool_data(false)
	{
		float_data = 0.0f;
	}

	float float_data;
	std::string sting_data;
	bool bool_data;
};

struct Node
{
	ed::NodeId ID;
	std::string Name;
	std::vector<Pin> Inputs;
	std::vector<Pin> Outputs;
	ImColor Color;
	NodeType Type;
	ImVec2 Size;

	std::string State;
	std::string SavedState;

	Node(int id, const char* name, ImColor color = ImColor(255, 255, 255)) :
		ID(id), Name(name), Color(color), Type(NodeType::Blueprint), Size(0, 0), isInputNode(false)
	{
	}

	void setExec(std::function<void()> f)
	{
		m_exec_func = f;
	}

	void exec()
	{
		if (m_exec_func)
			m_exec_func();
	}

	std::function<void()> m_exec_func;
	bool isInputNode;

};

struct Link
{
	ed::LinkId ID;

	ed::PinId StartPinID;
	ed::PinId EndPinID;

	ImColor Color;

	Link(ed::LinkId id, ed::PinId startPinId, ed::PinId endPinId) :
		ID(id), StartPinID(startPinId), EndPinID(endPinId), Color(255, 255, 255)
	{
	}
};

struct NodeIdLess
{
	bool operator()(const ed::NodeId& lhs, const ed::NodeId& rhs) const
	{
		return lhs.AsPointer() < rhs.AsPointer();
	}
};


//////////////Static vars /////////////////////////////

static ed::EditorContext* m_Editor = nullptr;




static const int            s_PinIconSize = 24;
static std::vector<Node>    s_Nodes;
static std::vector<Link>    s_Links;
static ImTextureID          s_HeaderBackground = nullptr;
//static ImTextureID          s_SampleImage = nullptr;
static ImTextureID          s_SaveIcon = nullptr;
static ImTextureID          s_RestoreIcon = nullptr;
static ImTextureID          s_BackTestingImage = nullptr;
static ImGuiTextBuffer		s_BackTestingResult;


static const float          s_TouchTime = 1.0f;

static std::map<ed::NodeId, float, NodeIdLess> s_NodeTouchTime;

static int s_NextId = 1;
static std::map<int, int>	s_ExecNodes_indecies;



///////////// Helper functions (uses static vars)////////////////////////

static int GetNextId()
{
	return s_NextId++;
}


static ed::LinkId GetNextLinkId()
{
	return ed::LinkId(GetNextId());
}

static void TouchNode(ed::NodeId id)
{
	s_NodeTouchTime[id] = s_TouchTime;
}

static float GetTouchProgress(ed::NodeId id)
{
	auto it = s_NodeTouchTime.find(id);
	if (it != s_NodeTouchTime.end() && it->second > 0.0f)
		return (s_TouchTime - it->second) / s_TouchTime;
	else
		return 0.0f;
}

static void UpdateTouch()
{
	const auto deltaTime = ImGui::GetIO().DeltaTime;
	for (auto& entry : s_NodeTouchTime)
	{
		if (entry.second > 0.0f)
			entry.second -= deltaTime;
	}
}

static Node* FindNode(ed::NodeId id)
{
	for (auto& node : s_Nodes)
		if (node.ID == id)
			return &node;

	return nullptr;
}

static Link* FindLink(ed::LinkId id)
{
	for (auto& link : s_Links)
		if (link.ID == id)
			return &link;

	return nullptr;
}

static Pin* FindPin(ed::PinId id)
{
	if (!id)
		return nullptr;

	for (auto& node : s_Nodes)
	{
		for (auto& pin : node.Inputs)
			if (pin.ID == id)
				return &pin;

		for (auto& pin : node.Outputs)
			if (pin.ID == id)
				return &pin;
	}

	return nullptr;
}

static bool IsPinLinked(ed::PinId id)
{
	if (!id)
		return false;

	for (auto& link : s_Links)
		if (link.StartPinID == id || link.EndPinID == id)
			return true;

	return false;
}

static Pin* FindLinkedPin(ed::PinId id)
{
	if (!id)
		return nullptr;

	for (auto& link : s_Links)
		if (link.StartPinID == id)
		{
			return FindPin(link.EndPinID);
		}
		else if (link.EndPinID == id)
		{
			return FindPin(link.StartPinID);
		}

	return nullptr;
}

static bool CanCreateLink(Pin* a, Pin* b)
{
	if (!a || !b || a == b || a->Kind == b->Kind || a->Type != b->Type || a->Node == b->Node)
		return false;

	return true;
}



static void BuildNode(Node* node)
{
	for (auto& input : node->Inputs)
	{
		input.Node = node;
		input.Kind = PinKind::Input;
	}

	for (auto& output : node->Outputs)
	{
		output.Node = node;
		output.Kind = PinKind::Output;
	}
}

void BuildNodes()
{
	for (auto& node : s_Nodes)
		BuildNode(&node);
}

///////////////////////

//helper for get_string_input
const char * evaluate_node_and_get_string(ed::NodeId id, ax::NodeEditor::PinId output_pin_id)
{
	return nullptr;
}

const char * get_string_input(ed::NodeId id, int input_pin_index)
{
	Node * node = FindNode(id);
	Pin * pin = &(node->Inputs[input_pin_index]);
	if (pin->Type == PinType::String)
	{
		// if linked with pin is input node (to do implement input node type) -> get value
		// if not evaluate node and get output at pin id
		Pin * connected_pin = FindLinkedPin(pin->ID);
		if (connected_pin)
		{
			Node * node = connected_pin->Node;
			if (node->isInputNode)
			{
				return connected_pin->sting_data.c_str();
			}
			else
			{
				return evaluate_node_and_get_string(node->ID, connected_pin->ID);
			}
		}
		else
		{
			// not connected to any node
			return nullptr;
		}		
	}
	return nullptr;
}

//helper for get_float_input
float evaluate_node_and_get_float(Node * node, Pin * output_pin)
{
	node->exec();
	return output_pin->float_data;
}

float get_float_input(ed::NodeId id, int input_pin_index)
{
	Node * node = FindNode(id);
	Pin * pin = &(node->Inputs[input_pin_index]);
	if (pin->Type == PinType::Float)
	{
		// if linked with pin is input node (to do implement input node type) -> get value
		// if not evaluate node and get output at pin id
		Pin * connected_pin = FindLinkedPin(pin->ID);
		if (connected_pin)
		{
			Node * node = connected_pin->Node;
			if (node->Type == NodeType::Simple)
			{
				return evaluate_node_and_get_float(node, connected_pin);
			}
			else
			{
				return connected_pin->float_data;
			}
		}
		else
		{
			// not connected to any node
			return std::numeric_limits<float>::infinity();
		}
	}
	else {
		// wrong exec function 
		std::cout << "wrong exec function " << std::endl;
		throw;
	}
	return 0.0f;
}

//helper for get_bool_input
float evaluate_node_and_get_bool(Node * node, Pin * output_pin)
{
	node->exec();
	return output_pin->bool_data;
}


bool get_bool_input(ed::NodeId id, int input_pin_index)
{
	Node * node = FindNode(id);
	Pin * pin = &(node->Inputs[input_pin_index]);
	if (pin->Type == PinType::Bool)
	{
		// if linked with pin is input node (to do implement input node type) -> get value
		// if not evaluate node and get output at pin id
		Pin * connected_pin = FindLinkedPin(pin->ID);
		if (connected_pin)
		{
			Node * node = connected_pin->Node;
			if (node->Type == NodeType::Simple)
			{
				return evaluate_node_and_get_bool(node, connected_pin);
			}
			else
			{
				return connected_pin->bool_data;
			}
		}
		else
		{
			// not connected to any node
			return pin->bool_data;
		}
	}
	else {
		// wrong exec function 
		std::cout << "wrong exec function " << std::endl;
		throw;
	}
	return false;
}

void set_float_output(ed::NodeId id, int output_pin_index, float result)
{
	Node * node = FindNode(id);
	Pin * pin = &(node->Outputs[output_pin_index]);
	pin->float_data = result;

}

void set_bool_output(ed::NodeId id, int output_pin_index, float result)
{
	Node * node = FindNode(id);
	Pin * pin = &(node->Outputs[output_pin_index]);
	pin->bool_data = result;

}

void set_string_output(ed::NodeId id, int output_pin_index, char * result)
{

}

