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
set (imgui_ini "${CMAKE_CURRENT_SOURCE_DIR}/imgui.ini")
set (chromedriver  "${CMAKE_CURRENT_SOURCE_DIR}/chromedriver.exe" )
set (installs ${imgui_ini} ${chromedriver} ${_Py_DLLS})
	
foreach(element ${installs})
add_custom_command( 
		TARGET QuantLabStudio
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E 
		copy_if_different  ${element} $<TARGET_FILE_DIR:QuantLabStudio>
	)
endforeach()


