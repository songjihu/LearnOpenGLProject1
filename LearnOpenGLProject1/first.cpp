/*#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main();

//����ע��ص��������ı䴰�ڴ�С
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//��������
void processInput(GLFWwindow* window);
//�����ζ���
/*
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,
     // �ڶ���������
    0.5f, -0.5f, 0.0f,  // ���½�
    -0.5f, -0.5f, 0.0f, // ���½�
    -0.5f, 0.5f, 0.0f   // ���Ͻ�
};
*/
/*
float vertices[] = {
    0.5f, 0.5f, 0.0f,   // ���Ͻ�
    0.5f, -0.5f, 0.0f,  // ���½�
    -0.5f, -0.5f, 0.0f, // ���½�
    -0.5f, 0.5f, 0.0f   // ���Ͻ�
};

unsigned int indices[] = { // ע��������0��ʼ! 
    0, 1, 3, // ��һ��������
    1, 2, 3  // �ڶ���������
};

//��ɫ��Դ��
const char *vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n" 
"void main()\n" 
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";
//Ƭ����ɫ��
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

//Ƭ����ɫ��1
const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.8f, 1.0f);\n"
"}\n\0";





int main()
{
    glfwInit();//��ʼ��glfw
    //ʹ��glfwWindowHint����glfw������GLFW����Ҫʹ�õ�OpenGL�汾��3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//ѡ�����ƣ�ö���ͣ�+ ���� ���汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ģʽ
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //�������ڶ���
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//�� �� ���� 
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //�����ڵ�����������Ϊ��ǰ�̵߳���������
    glfwMakeContextCurrent(window);

    //��ʼ��GLAD��GLAD��������OpenGLָ�룩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //���ô��ڵ�ά�ȣ�����OpenGL��Ⱦ���ڵĳߴ��С�����Ա�ʵ�ʴ���С
    glViewport(0, 0, 800, 600);//�������½�λ�� �߶� ���

    //ע�� ʹglfw�������ڴ�Сʱ���ô˺���
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //���嶥�㻺�����
    unsigned int VBO;
    glGenBuffers(1, &VBO);//���㻺�����Ļ���������GL_ARRAY_BUFFER

    //������ɫ��
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);//����Ϊ������ɫ��
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//�������ɫ��Դ�븽�ӵ���ɫ��������,�ڶ�����ָ���˴��ݵ�Դ���ַ�������
    glCompileShader(vertexShader);//����
    //����Ƿ����ɹ�
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ohohoh:ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    //����Ƭ����ɫ��
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //������ɫ������
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

    //����Ƭ����ɫ��1
    unsigned int fragmentShader1;
    fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShaderSource1, NULL);
    glCompileShader(fragmentShader1);
    //������ɫ������1
    unsigned int shaderProgram1;
    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);


    //����VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // 1. ��VAO
    glBindVertexArray(VAO);
    // 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. ���ö�������ָ��
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //��Ⱦѭ��(Render Loop)��������������GLFW�˳�ǰһֱ�������У�ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�
    while (!glfwWindowShouldClose(window))
    {

        processInput(window);//�������루����ESC�رգ�

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ ״̬���ú���
        glClear(GL_COLOR_BUFFER_BIT); //�����Ļ����ɫ���� ״̬ʹ�ú���

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ
         // 4. ��������
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);//������
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//����


        glUseProgram(shaderProgram1);
        //glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);//������
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//����

        glBindVertexArray(0);
        glfwSwapBuffers(window);//������ɫ���� ���� ��ʾ
        glfwPollEvents();//��鴥���¼�
    }

    //�ͷ�
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
    //����û��Ƿ����˷��ؼ�(Esc)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);//�رմ���
}*/