/*#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main();

//窗口注册回调函数，改变窗口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//处理输入
void processInput(GLFWwindow* window);
//三角形顶点
/*
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     // 第二个三角形
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};
*/
/*
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // 右上角
    0.5f, -0.5f, 0.0f,  // 右下角
    -0.5f, -0.5f, 0.0f, // 左下角
    -0.5f, 0.5f, 0.0f   // 左上角
};

unsigned int indices[] = { // 注意索引从0开始! 
    0, 1, 3, // 第一个三角形
    1, 2, 3  // 第二个三角形
};

//着色器源码
const char *vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n" 
"void main()\n" 
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";
//片段着色器
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

//片段着色器1
const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.8f, 1.0f);\n"
"}\n\0";





int main()
{
    glfwInit();//初始化glfw
    //使用glfwWindowHint配置glfw，告诉GLFW我们要使用的OpenGL版本是3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//选项名称（枚举型）+ 整数 主版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //创建窗口对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//宽 高 名称 
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //将窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    //初始化GLAD（GLAD用来管理OpenGL指针）
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //设置窗口的维度，告诉OpenGL渲染窗口的尺寸大小，可以比实际窗口小
    glViewport(0, 0, 800, 600);//窗口左下角位置 高度 宽度

    //注册 使glfw调整窗口大小时调用此函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //定义顶点缓冲对象
    unsigned int VBO;
    glGenBuffers(1, &VBO);//顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER

    //定义着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//类型为顶点着色器
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//把这个着色器源码附加到着色器对象上,第二参数指定了传递的源码字符串数量
    glCompileShader(vertexShader);//编译
    //检测是否编译成功
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ohohoh:ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //定义片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //定义着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ohohoh:ERROR::SHADER::VERTEX::LINK_FAILED\n" << infoLog << std::endl;
    }

    //定义片段着色器1
    unsigned int fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    //定义着色器程序1
    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);


    //创建VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //渲染循环(Render Loop)，它能在我们让GLFW退出前一直保持运行，每次循环的开始前检查一次GLFW是否被要求退出
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);//处理输入（按下ESC关闭）

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//整个颜色缓冲都会被填充为glClearColor里所设置的颜色 状态设置函数
        glClear(GL_COLOR_BUFFER_BIT); //清空屏幕的颜色缓冲 状态使用函数

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式
         // 4. 绘制物体
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);//三角形
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//矩形


        glUseProgram(shaderProgram1);
        //glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);//三角形
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//矩形

        glBindVertexArray(0);
        glfwSwapBuffers(window);//交换颜色缓冲 绘制 显示
        glfwPollEvents();//检查触发事件
    }

    //释放
    glfwTerminate();

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    //检查用户是否按下了返回键(Esc)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);//关闭窗口
}*/