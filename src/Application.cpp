#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <shader_m.h>
#include <camera.h>
#include <model.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);
unsigned int loadCubemap(vector<std::string> faces);

// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 900;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader shader("src/6.1.cubemaps.vs", "src/6.1.cubemaps.fs");
    Shader skyboxShader("src/6.1.skybox.vs", "src/6.1.skybox.fs");

    // load models

  
    Model circus("resources/objects/themepark/AnyConv.com__circus.obj");

    Model ferris_wheel("resources/objects/themepark/AnyConv.com__ferris_wheel_low_poly.obj");

    Model food_cart("resources/objects/themepark/AnyConv.com__avika_street_food_cart.obj");

    Model sport("resources/objects/themepark/AnyConv.com__zis-101a_sport_1938.obj");

    Model hot_air_baloon("resources/objects/themepark/AnyConv.com__hot_air_balloon_-_low_poly.obj");

    Model seasaw("resources/objects/themepark/AnyConv.com__seesaw.obj");

    Model swing("resources/objects/themepark/AnyConv.com__swing.obj");

    Model swing2("resources/objects/themepark/AnyConv.com__swing_gameasset_under_18k_triangles_with_uv.obj");

    Model micky("resources/objects/themepark/AnyConv.com__tahla_mickey_mouse.obj");

    Model carosel("resources/objects/themepark/AnyConv.com__spaceship_carousel_-_discovery.obj");

    Model carosel2("resources/objects/themepark/AnyConv.com__sports_town-carouselhelix..obj");

    Model copter("resources/objects/plan/brabazon.obj");

    Model bike("resources/objects/town/AnyConv.com__speedboat_n2.obj");

    Model roller_coaster("resources/objects/themepark/AnyConv.com__15_the_fall_3december2019.obj");

    Model ship_food_cart("resources/objects/themepark/AnyConv.com__airship_restaurant_-_lunapark.obj");

    Model gate("resources/objects/themepark/AnyConv.com__ishtar_gate_babylon.obj");

    Model seesaw("resources/objects/themepark/AnyConv.com__seesaw_type-1.obj");

    Model carousel3("resources/objects/themepark/AnyConv.com__christmas_carousel.obj");

    Model water("resources/objects/themepark/AnyConv.com__playground.obj");

    Model palace("resources/objects/themepark/AnyConv.com__cologne_cathedral.obj");

    Model tire("resources/objects/themepark/AnyConv.com__inflatable_pool_float.obj");

    Model ballon("resources/objects/themepark/AnyConv.com__cartoon_balloons.obj");

    Model welcome("resources/objects/themepark/AnyConv.com__welcome3D.obj");

    Model helicopter("resources/objects/themepark/AnyConv.com__helicopter.obj");

    Model slide("resources/objects/themepark/AnyConv.com__slide_playground.obj");
    
    Model chalkboard("resources/objects/themepark/AnyConv.com__chalkboard_sign_v2.obj");
   
    Model elephant("resources/objects/themepark/AnyConv.com__circus_elephant.obj");

    Model claw("resources/objects/themepark/AnyConv.com__claw_machine.obj");

    Model fountain("resources/objects/themepark/AnyConv.com__fountain.obj");

    Model bench("resources/objects/themepark/bench.obj");


    

    

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    // skybox VAO
    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // load textures
    // -------------
    unsigned int cubeTexture = loadTexture("resources/textures/bricks2.jpg");


    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    //unsigned int amount = 1000;



    vector<std::string> faces
    {
        "resources/textures/my/posx.jpg",
        "resources/textures/my/negx.jpg",
        "resources/textures/my/posy.jpg",
        "resources/textures/my/negy.jpg",
        "resources/textures/my/posz.jpg",
        "resources/textures/my/negz.jpg"
    };

    unsigned int cubemapTexture = loadCubemap(faces);

    // shader configuration
    // --------------------
   // shader.use();
   // shader.setInt("texture1", 0);

    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // configure transformation matrices
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();;
        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);


        float rotAngle = 45;

        // draw circus>
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-90.0f, -30.0f, -480.0f));
        model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
        shader.setMat4("model", model);
        circus.Draw(shader);


        // draw ferris wheel>
        glm::mat4 model1 = glm::mat4(1.0f);
        model1 = glm::translate(model1, glm::vec3(-100.0f, -30.0f, -100.0f));
        model1 = glm::scale(model1, glm::vec3(8.0f, 8.0f, 8.0f));
        model1 = glm::rotate(model1, rotAngle, glm::vec3(0.0f, 0.25f, 0.0f));
        shader.setMat4("model", model1);
        ferris_wheel.Draw(shader);

    

        // draw foodcart>
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, glm::vec3(140.0f, -10.0f, -200.0f));
        model2 = glm::scale(model2, glm::vec3(12.0f, 12.0f, 12.0f));
        shader.setMat4("model", model2);
        food_cart.Draw(shader);

        // draw seesaw>
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3(75.0f, -10.0f, -200.0f));
        model3 = glm::scale(model3, glm::vec3(12.0f, 12.0f, 12.0f));
        shader.setMat4("model", model3);
        seesaw.Draw(shader);


        //draw food ship cart>
        glm::mat4 model4 = glm::mat4(1.0f);
        model4 = glm::translate(model4, glm::vec3(-100.0f, 20.0f, 300.0f));
        model4 = glm::scale(model4, glm::vec3(8.0f, 8.0f, 8.0f));
        shader.setMat4("model", model4);
        ship_food_cart.Draw(shader);
  


        // draw micky>
        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model5 = glm::mat4(1.0f);
            model5 = glm::translate(model5, glm::vec3(-25.0f, -10.0f, 0.0f));
            model5 = glm::scale(model5, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down

            float angle = 2.0f * i;
            if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = glfwGetTime() * 5.0f;
            model5 = glm::rotate(model5, -glm::radians(angle), glm::vec3(0.0f, 0.5f, 0.0f));
            model5 = glm::translate(model5, glm::vec3(300.0f, 0.0f, 0.0f));
            model5 = glm::rotate(model5, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
            shader.setMat4("model", model5);
            micky.Draw(shader);

        }

        // draw roller coaster>
        glm::mat4 model6 = glm::mat4(1.0f);
        model6 = glm::translate(model6, glm::vec3(-300.0f, -10.0f, -380.0f));
        model6 = glm::scale(model6, glm::vec3(5.0f, 5.0f, 10.0f));
        model6 = glm::rotate(model6, rotAngle, glm::vec3(0.0f, 0.15f, 0.0f));
        shader.setMat4("model", model6);
        roller_coaster.Draw(shader);


        // draw swing>
        glm::mat4 model7 = glm::mat4(1.0f);
        model7 = glm::translate(model7, glm::vec3(200.0f, -10.0f, -100.0f));
        model7 = glm::scale(model7, glm::vec3(0.07f, 0.07f, 0.07f));
        model7 = glm::rotate(model7, rotAngle, glm::vec3(0.0f, 0.40f, 0.0f));
        shader.setMat4("model", model7);
        swing.Draw(shader);


        // draw slide>
        glm::mat4 model8 = glm::mat4(1.0f);
        model8 = glm::translate(model8, glm::vec3(200.0f, -10.0f, -0.300f));
        model8 = glm::scale(model8, glm::vec3(6.0f, 6.0f, 6.0f));
        shader.setMat4("model", model8);
        slide.Draw(shader);

        // draw sport>
        glm::mat4 model9 = glm::mat4(1.0f);
        model9 = glm::translate(model9, glm::vec3(40.0f, -10.0f, -200.0f));
        model9 = glm::scale(model9, glm::vec3(70.0f, 70.0f, 70.0f));
        shader.setMat4("model", model9);
        sport.Draw(shader);

        // draw hot air baloon near >
        glm::mat4 model10 = glm::mat4(1.0f);
        model10 = glm::translate(model10, glm::vec3(40.0f, 30.0f, 0.0f));
        model10 = glm::scale(model10, glm::vec3(0.70f, 0.70f, 0.70f));
        model10 = glm::rotate(model10, rotAngle, glm::vec3(0.0f, -0.15f, 0.0f));
        shader.setMat4("model", model10);
        hot_air_baloon.Draw(shader);

        // draw carosel>
        glm::mat4 model11 = glm::mat4(1.0f);
        model11 = glm::translate(model11, glm::vec3(305.0f, -10.0f, -100.0f));
        model11 = glm::scale(model11, glm::vec3(20.0f, 20.0f, 20.0f));
        shader.setMat4("model", model11);
        carosel.Draw(shader);

        // draw carosel2>
        glm::mat4 model12 = glm::mat4(1.0f);
        model12 = glm::translate(model12, glm::vec3(55.0f, -10.0f, -200.0f));
        model12 = glm::scale(model12, glm::vec3(6.0f, 6.0f, 6.0f));
        shader.setMat4("model", model12);
        carosel2.Draw(shader);

        // draw waterbike >
        glm::mat4 model13 = glm::mat4(1.0f);
        model13 = glm::translate(model13, glm::vec3(-45.0f, -20.0f, 90.0f));
        model13 = glm::scale(model13, glm::vec3(3.0f, 3.0f, 3.0f));
        shader.setMat4("model", model13);
        bike.Draw(shader);


        // draw hot air baloon far>
        glm::mat4 model14 = glm::mat4(1.0f);
        model14 = glm::translate(model14, glm::vec3(340.0f, 40.0f, 45.0f));
        model14 = glm::scale(model14, glm::vec3(0.70f, 0.70f, 0.70f));
        model14 = glm::rotate(model14, rotAngle, glm::vec3(0.0f, -0.15f, 0.0f));
        shader.setMat4("model", model14);
        hot_air_baloon.Draw(shader);


        // draw waterbike >
        glm::mat4 model15 = glm::mat4(1.0f);
        model15 = glm::translate(model15, glm::vec3(0.0f, -20.0f, 90.0f));
        model15 = glm::scale(model15, glm::vec3(3.0f, 3.0f, 3.0f));
        shader.setMat4("model", model15);
        bike.Draw(shader);

        // draw claw>
        glm::mat4 model16 = glm::mat4(1.0f);
        model16 = glm::translate(model16, glm::vec3(20.0f, -10.0f, -160.0f));
        model16 = glm::scale(model16, glm::vec3(6.0f, 6.0f, 6.0f));
        shader.setMat4("model", model16);
        claw.Draw(shader);

        // draw helicopter

        for (unsigned int i = 0; i < 1; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model17 = glm::mat4(1.0f);
            model17 = glm::translate(model17, glm::vec3(0.0f, 40.0f, 90.0f));
            model17 = glm::scale(model17, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

            float angle = 2.0f * i;
            if (i % 3 == 0)  // every 3rd iteration (including the first) we set the angle using GLFW's time function.
                angle = glfwGetTime() * 5.0f;
            model17 = glm::rotate(model17, -glm::radians(angle), glm::vec3(0.0f, 0.5f, 0.0f));
            model17 = glm::translate(model17, glm::vec3(300.0f, 0.0f, 0.0f));
            model17 = glm::rotate(model17, rotAngle, glm::vec3(0.0f, 0.8f, 0.0f));
            shader.setMat4("model", model17);
            helicopter.Draw(shader);

        }

        //draw carausel3 >
        glm::mat4 model20 = glm::mat4(1.0f);
        model20 = glm::translate(model20, glm::vec3(85.0f, -10.0f, 20.0f));
        model20 = glm::scale(model20, glm::vec3(3.0f, 3.0f, 3.0f));
        shader.setMat4("model", model20);
        carousel3.Draw(shader);

        //water game
        glm::mat4 model21 = glm::mat4(1.0f);
        model21 = glm::translate(model21, glm::vec3(50.0f, -20.0f, 170.0f));
        model21 = glm::scale(model21, glm::vec3(12.0f, 12.0f, 12.0f));
        shader.setMat4("model", model21);
        water.Draw(shader);



        // draw palace >
        glm::mat4 model22 = glm::mat4(1.0f);
        model22 = glm::translate(model22, glm::vec3(-400.0f, -20.0f, 1850.0f));
        model22 = glm::scale(model22, glm::vec3(150.0f, 150.0f, 150.0f));
        shader.setMat4("model", model22);
        palace.Draw(shader);


        //draw tire

        glm::mat4 model24 = glm::mat4(1.0f);
        model24 = glm::translate(model24, glm::vec3(-40.0f, -20.0f, 360.0f));
        model24 = glm::scale(model24, glm::vec3(0.05f, 0.05f, 0.05f));
        model24 = glm::rotate(model24, rotAngle, glm::vec3(0.0f, -0.15f, 0.0f));
        shader.setMat4("model", model24);
        tire.Draw(shader);


        //draw fountain

        glm::mat4 model29 = glm::mat4(1.0f);
        model29 = glm::translate(model29, glm::vec3(40.0f, -10.0f, -50.0f));
        model29 = glm::scale(model29, glm::vec3(3.0f, 3.0f, 3.0f));
        //model29 = glm::rotate(model29, rotAngle, glm::vec3(0.0f, 0.15f, 0.0f));
        shader.setMat4("model", model29);
        fountain.Draw(shader);


        //draw bench
        glm::mat4 model30 = glm::mat4(1.0f);
        model30 = glm::translate(model30, glm::vec3(1850.0f, -10.0f, -10.0f));
        model30 = glm::scale(model30, glm::vec3(5.0f, 5.0f, 10.0f));
        model30 = glm::rotate(model30, rotAngle, glm::vec3(0.0f, 0.15f, 0.0f));
        shader.setMat4("model", model30);
        bench.Draw(shader);

        // draw palace2> 
        glm::mat4 model33 = glm::mat4(1.0f);
        model33 = glm::translate(model33, glm::vec3(-400.0f, -20.0f, 1050.0f));
        model33 = glm::scale(model33, glm::vec3(150.0f, 150.0f, 150.0f));
        shader.setMat4("model", model33);
        palace.Draw(shader);
       



        // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxShader.use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS); // set depth function back to default

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
  //  glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &skyboxVAO);
    //  glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &skyboxVBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front) 
// -Z (back)
// -------------------------------------------------------
unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

