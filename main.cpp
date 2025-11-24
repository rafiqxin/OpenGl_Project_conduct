#include<iostream>

//注意：glad头文件必须在GLFW头文件之前引入
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<string>
#include<assert.h>//断言
#include"wrapper/checkError.h"
#include"application/Application.h"
/*
* 目标：
* 1、掌握GLFW窗口创建的基本流程
* 2、掌握GLFW窗口大小变化的监听
* 3、掌握GLFW键盘输入的监听
* 4、opengl api:
*		glViewport:设置视口
*		glClearColor:设置清空屏幕所用的颜色
*		glClear:清空屏幕
*		GL_COLOR_BUFFER_BIT:颜色缓冲区
*		glfwSwapBuffers:执行双缓冲区交换
* 5、opengl错误处理
*		GLenum glGetError(void); 检查之前调用的OpenGL函数是否有错误发生
*		将错误代码封装成函数
* 		将错误的检查代码放到别的cpp文件
*		使用宏定义GL_CALL简化函数调用
*		在CmakeLists.txt中使用预编译宏，来控制是否开启错误检查
* 6、封装思路Application类,将窗体相关的代码封装到类中
*		单例类：原因是一个程序中只需要一个窗体对象,把application放private构造函数
* 7、编写一个OnResize函数，监听窗口大小变化
*/

void OnResize(int width, int height) {
	GL_CALL(glViewport(0, 0, width, height));
	std::cout << "窗体最新大小：" << width << "," << height << std::endl;
}
void OnKey(int key, int action, int mods) {
	std::cout << key <<	std::endl;
}

//声明且实现事件回调函数：窗口大小变化回调函数
void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
	//设置视口大小
	//std::cout << "窗体最新大小：" << width << "," << height << std::endl;
	//紧跟着调整视口大小
	glViewport(0, 0, width, height);
}

//声明且实现加入键盘响应回调函数
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_W) {
		std::cout << "键盘按键W被按下：" << key << std::endl;
	}
	std::cout << action << std::endl;
	std::cout << mods << std::endl;
}
/*
* 1、创建vbo(vertex buffer object)
 */
void prepare() {
	//1 创建一个vbo对象,还没有真正分配显存
	GLuint vbo = 0;
	GL_CALL(glGenBuffers(1, &vbo));

	//2 销毁vbo对象
	GL_CALL(glDeleteBuffers(1, &vbo));

	//3 创建n个vbo对象
	GLuint vboarr[] = { 0,0,0 };
	GL_CALL(glGenBuffers(3, vboarr));

	//4 销毁n个vbo对象
	GL_CALL(glDeleteBuffers(3, vboarr));
}

int main() {
	if (!app->init(800, 600)) {
		return -1;
	}

	app->SetResizeCallback(OnResize);
	app->SetKeyBoardCallback(OnKey);
	//加入监听设置,监听窗体大小变化
	//glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
	//加入监听设置，监听键盘输入
	//glfwSetKeyCallback(window, keyCallback);

	//初始化GLAD加载当前版本的OpenGL函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD初始化失败" << std::endl;
		return -1;
	}
	//设置视口大小
	GL_CALL(glViewport(0, 0, 800, 600));
	GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));

	prepare();

//3、执行窗体循环
	while (app->update()) {
		//执行opengl画布清理
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

		//渲染操作	
	}

//销毁窗体，释放资源
	app->destroy();
	return 0;
}