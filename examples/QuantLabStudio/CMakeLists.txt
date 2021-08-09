add_example_executable(QuantLabStudio
    blueprints-system.cpp
	BP_DataStructures.h
	BP_NodesLibrary.h
    utilities/builders.h
    utilities/drawing.h
    utilities/widgets.h
    utilities/builders.cpp
    utilities/drawing.cpp
    utilities/widgets.cpp
)
set_target_properties(QuantLabStudio PROPERTIES
LINK_FLAGS /SUBSYSTEM:CONSOLE
)

set(_Py_Dir ${IMGUI_NODE_EDITOR_ROOT_DIR}/external/python)

set (_Py_DLLS  
	"${_Py_Dir}/lib/python37.dll"
	"${_Py_Dir}/lib/boost_python37-vc141-mt-gd-x64-1_76.dll"
	"${_Py_Dir}/lib/boost_python37-vc141-mt-x64-1_76.dll" 
	)
	
foreach(_dll ${_Py_DLLS})
add_custom_command( 
		TARGET QuantLabStudio
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E 
		copy_if_different  ${_dll} $<TARGET_FILE_DIR:QuantLabStudio>
	)
endforeach()

set (imgui_ini "${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini")
add_custom_command(
		TARGET QuantLabStudio
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E 
		copy_if_different  ${imgui_ini} $<TARGET_FILE_DIR:QuantLabStudio>
	)

