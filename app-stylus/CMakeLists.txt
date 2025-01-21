cmake_minimum_required(VERSION 3.13...3.22)

project(app)

set(CMAKE_CXX_STANDARD 17)
set(XMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread")
set(RLIB --docroot ../ -c ../wt_config.xml --http-address 0.0.0.0 --http-port 9010)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/)

include_directories(${SOURCE_DIR})

set(SOURCES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/001-App/App.cpp
    ${SOURCE_DIR}/002-Dbo/Session.cpp

    ${SOURCE_DIR}/003-Preview/Preview.cpp
    ${SOURCE_DIR}/003-Preview/TreeNode.cpp
    ${SOURCE_DIR}/003-Preview/ElemNode.cpp

    ${SOURCE_DIR}/003-TreePreview/PTree.cpp
    ${SOURCE_DIR}/003-TreePreview/TreePreview.cpp
    ${SOURCE_DIR}/004-TempPreview/PNode.cpp
    ${SOURCE_DIR}/004-TempPreview/TempPreview.cpp
    ${SOURCE_DIR}/005-ClassesEdditor/ClassesEdditor.cpp
    
    ${SOURCE_DIR}/100-Utils/tinyxml2/tinyxml2.cpp
    ${SOURCE_DIR}/101-Stylus/Stylus.cpp
    ${SOURCE_DIR}/101-Stylus/XMLBrain.cpp
    
    ${SOURCE_DIR}/101-Stylus/PanelDialogs/BaseDialogPanel.cpp
    ${SOURCE_DIR}/101-Stylus/PanelDialogs/LeftPanel.cpp
    ${SOURCE_DIR}/101-Stylus/PanelDialogs/RightPanel.cpp
    ${SOURCE_DIR}/101-Stylus/PanelDialogs/EdditorPanel.cpp
    ${SOURCE_DIR}/101-Stylus/PanelDialogs/SettingsPanel.cpp
    ${SOURCE_DIR}/101-Stylus/PanelDialogs/QuickCommandsPanel.cpp
    

    ${SOURCE_DIR}/101-Stylus/Tailwind/Base.cpp
    ${SOURCE_DIR}/101-Stylus/Tailwind/TailwindConfig.cpp
    ${SOURCE_DIR}/101-Stylus/Tailwind/Category.cpp
    
    ${SOURCE_DIR}/101-Stylus/ClassChangers/SelectionBoxClassChanger.cpp
    ${SOURCE_DIR}/101-Stylus/ClassChangers/ComboBoxClassChanger.cpp
    ${SOURCE_DIR}/101-Stylus/ClassChangers/ColorsWidget.cpp

    ${SOURCE_DIR}/101-Stylus/TCategory/BasePanel.cpp
    ${SOURCE_DIR}/101-Stylus/TCategory/SpacingP.cpp
    ${SOURCE_DIR}/101-Stylus/TCategory/SizingP.cpp
    ${SOURCE_DIR}/101-Stylus/TCategory/TransitionsAndAnimationP.cpp
    ${SOURCE_DIR}/101-Stylus/TCategory/AccesibilityP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/BackgroundP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/BordersP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/EffectsP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/FiltersP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/FlexAndGridP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/InteractivityP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/LayoutP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/SvgP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/TablesP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/TransformsP.cpp 
    ${SOURCE_DIR}/101-Stylus/TCategory/TypographyP.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} 
    wthttp
    wt
    wtdbo
    wtdbosqlite3
    wtdbopostgres
    # boost_filesystem
    boost_regex
)

add_custom_target(run
    COMMAND ${PROJECT_NAME} ${RLIB}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

