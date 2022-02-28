这是一个ReadMe
使用本项目时可能需要载入依赖
依赖包在dependence中
对项目右键->属性
C/C++->常规->附加包含目录->编辑
添加
$(SolutionDir)dependences\GLEW\include
$(SolutionDir)dependences\GLFW\include

链接器->常规->添加库目录
添加
$(SolutionDir)dependences\GLFW\lib-vc2015
$(SolutionDir)dependences\GLEW\lib\Release\Win32

链接器->输入->附加依赖项
添加
opengl32.lib
glfw3.lib
glew32s.lib