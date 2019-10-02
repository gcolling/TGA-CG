#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Shader.h"
#include "Mesh.h"
#include "ObjectReader.h"
#include "Material.h"
#include "MaterialReader.h"
#include "Object.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

void window_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void processInput(vector<Object*>);
int getSelectedIndex(vector<Object*>);
bool isModelKey();
void disableObjects(vector<Object*>);
void readFiles(vector<Object*>);
void preparePrintingData(vector<Object*>);
void draw(vector<Object*>);
Material* getMaterialObject(string materialId);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const float cameraSpeed = 0.005f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = normalize(cameraPos - cameraTarget);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = normalize(cross(up, cameraDirection));
glm::vec3 cameraUp = cross(cameraDirection, cameraRight);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float previousX = 640.0f / 2.0;
float previousY = 480.0f / 2.0;
float fov = 45.0f;

float scale = 1.001f;
float movement = 0.001f;

GLFWwindow* window;
vector<Material*> materials;

int main() {
	vector<Object*> objects;

	Object* obj1 = new Object("mesa01.obj");
	objects.push_back(obj1);

	Object* obj2 = new Object("cube.obj");
	objects.push_back(obj2);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Teste de versão OpenGL", NULL, NULL);
	if (!window) {
		fprintf(stderr, "Error while opening window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = GL_TRUE;
	glewInit();

	readFiles(objects);
	preparePrintingData(objects);
	draw(objects);

	glfwTerminate();
	return 0;
}

void window_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	/*if (firstMouse)
	{
		previousX = xpos;
		previousY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - previousX;
	float yoffset = previousY - ypos;
	previousX = xpos;
	previousY = ypos;

	float sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.y = cos(glm::radians(yaw)) * sin(glm::radians(pitch));
	front.x = cos(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);*/
}

void processInput(vector<Object*> objects){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	//selecting objects
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
		disableObjects(objects);
		objects[0]->toggleSelected();
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
		disableObjects(objects);
		objects[1]->toggleSelected();
	}
	
	// vou trabalhar com classe obj3d, que possui uma mesh e atributo selected (bool) e atributo model (transform)
	// cada obj vai ter a sua model
	int selectedIndex = getSelectedIndex(objects);
	if (selectedIndex != -1 && isModelKey() == true) {
		vector<float> center = objects[selectedIndex]->getCenter();

		//gets the properties matrixes of selected object, if any
		glm::mat4 model = objects[selectedIndex]->getModel();
		glm::mat4 translation = objects[selectedIndex]->getTranslation();
		glm::mat4 rotation = objects[selectedIndex]->getRotation();
		glm::mat4 scaling = objects[selectedIndex]->getScaling();
		float centerX = center[0];
		float centerY = center[1];

		//translating
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			translation = glm::translate(translation, glm::vec3(movement, 0.0f, 0.0f));
			model = scaling * rotation * translation;
			centerX = centerX + movement;
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			translation = glm::translate(translation, glm::vec3(-movement, 0.0f, 0.0f));
			model = scaling * rotation * translation;
			centerX = centerX - movement;
		}
		else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			translation = glm::translate(translation, glm::vec3(0.0f, movement, 0.0f));
			model = scaling * rotation * translation;
			centerY = centerY + movement;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			translation = glm::translate(translation, glm::vec3(0.0f, -movement, 0.0f));
			model = scaling * rotation * translation;
			centerY = centerY - movement;
		}

		//rotating
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
			rotation = glm::rotate(rotation, glm::radians(-0.05f), glm::vec3(0, 1, 0));
			model = scaling * rotation * translation;
		}
		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
			rotation = glm::rotate(rotation, glm::radians(0.05f), glm::vec3(0, 1, 0));
			model = scaling * rotation * translation;
		}
		else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
			rotation = glm::rotate(rotation, glm::radians(-0.05f), glm::vec3(1, 0, 0));
			model = scaling * rotation * translation;
		}
		else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
			rotation = glm::rotate(rotation, glm::radians(0.05f), glm::vec3(1, 0, 0));
			model = scaling * rotation * translation;
		}

		//scaling
		if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
		{
			scaling = glm::scale(scaling, glm::vec3(scale, scale, scale));
			model = scaling * rotation * translation;
		}
		else if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
		{
			scaling = glm::scale(scaling, glm::vec3(1.0f / scale, 1.0f / scale, 1.0f / scale));
			model = scaling * rotation * translation;
		}

		//sets the updated porperties tables of the selected object
		objects[selectedIndex]->setModel(model);
		objects[selectedIndex]->setTranslation(translation);
		objects[selectedIndex]->setRotation(rotation);
		objects[selectedIndex]->setScaling(scaling);
		objects[selectedIndex]->setCenter(centerX, centerY);
	}

	//camera
	if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	else if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

int getSelectedIndex(vector<Object*> objects) {
	for (int o = 0; o < objects.size(); o++) {
		if (objects[o]->isSelected() == true)
			return o;
	}
	return -1;
}

void disableObjects(vector<Object*> objects) {
	for (int o = 0; o < objects.size(); o++) {
		objects[o]->disable();
	}
}

bool isModelKey() {
	if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) ||
		(glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS))
		return true;
	return false;
}

void readFiles(vector<Object*> objects) {
	for (int i = 0; i < objects.size(); i++) {
		ObjectReader* objectReader = new ObjectReader(objects[i]->getFilePath());
		Mesh* mesh = objectReader->readFile();
		objects[i]->setMesh(mesh);
		MaterialReader* matReader = new MaterialReader(mesh->getMaterialFile());
		vector<Material*> fileMaterials = matReader->readFile();
		for (int m = 0; m < fileMaterials.size(); m++) {
			materials.push_back(fileMaterials[m]);
		}
	}
}

void preparePrintingData(vector<Object*> objects) {
	vector<float> vs;

	for (int o = 0; o < objects.size(); o++) {
		Mesh* mesh = objects[o]->getMesh();

		mesh->getShader()->setInt("material.tex", 0);

		for (int i = 0; i < mesh->getGroups().size(); i++) {
			vector<Face*> faces = mesh->getGroups()[i]->getFaces();
			for (int j = 0; j < faces.size(); j++) {
				vector<int> vertsIndex = faces[j]->getVerts();
				vector<int> textsIndex = faces[j]->getTexts();
				vector<int> normsIndex = faces[j]->getNorms();

				if (vertsIndex.size() != normsIndex.size()) {
					throw "Vertex and Normal length differ.";
				}

				for (int k = 0; k < vertsIndex.size(); k++) {
					glm::vec3 v = mesh->getVertex()[vertsIndex[k]];
					glm::vec2 t = mesh->getMappings()[textsIndex[k]];
					glm::vec3 n = mesh->getNormals()[normsIndex[k]];

					vs.push_back(v.x);
					vs.push_back(v.y);
					vs.push_back(v.z);
					vs.push_back(t.x);
					vs.push_back(t.y);
					vs.push_back(n.x);
					vs.push_back(n.y);
					vs.push_back(n.z);
				}
			}

			GLuint vbo = 0, vao = 0;

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vs.size() * sizeof(float), vs.data(), GL_STATIC_DRAW);

			//vertex
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

			//texture
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

			//normal
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

			mesh->getGroups()[i]->setVAOIndex(vao);

			if (mesh->getGroups()[i]->getMaterial() != "") {

				Material* material = getMaterialObject(mesh->getGroups()[i]->getMaterial()); //@TODO verificar materials e pegar o certo pela id

				if (material != nullptr && material->getTextureFile() != "") {
					unsigned int textureID;

					glGenTextures(1, &textureID);
					glBindTexture(GL_TEXTURE_2D, textureID);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					int width, height, nrChannels;

					unsigned char* data = stbi_load(material->getTextureFile().c_str(), &width, &height, &nrChannels, 0);
					if (data)
					{

						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
						glGenerateMipmap(GL_TEXTURE_2D);
					}
					else
					{
						std::cout << "Texture failed to load at path: " << material->getTextureFile().c_str() << std::endl;
					}

					mesh->getGroups()[i]->setTextureIndex(textureID);
					stbi_image_free(data);
					glBindTexture(GL_TEXTURE_2D, 0);
				}
			}
			glBindVertexArray(0); // use mesh->getGroups()[i]->getVAOIndex()
			vs.clear();
		}
	}
}

Material* getMaterialObject(string materialId) {
	for (int i = 0; i < materials.size(); i++) {
		if (materials[i]->getMaterialid() == materialId) {
			return materials[i];
		}
	}
	return nullptr;
}

void draw(vector<Object*> objects) {

	while (!glfwWindowShouldClose(window)) {
		processInput(objects);

		glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		for (int o = 0; o < objects.size(); o++) {
			Mesh* mesh = objects[o]->getMesh();

			mesh->getShader()->use();
			mesh->getShader()->setMat4("view", view);
			mesh->getShader()->setMat4("projection", projection);
			mesh->getShader()->setMat4("model", objects[o]->getModel());
			if (objects[o]->isSelected() == true) {
				mesh->getShader()->setFloat("selected", 1.0);
			}
			else {
				mesh->getShader()->setFloat("selected", 0.0);
			}

			for (int i = 0; i < mesh->getGroups().size(); i++) {
				GLuint VAO = mesh->getGroups()[i]->getVAOIndex();
				glBindVertexArray(VAO);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mesh->getGroups()[i]->getTextureIndex());

				if (mesh->getGroups()[i]->getMaterial() != "") {
					Material* material = getMaterialObject(mesh->getGroups()[i]->getMaterial()); //@TODO verificar a lib de materials e pegar o certo pela id
				}

				glDrawArrays(GL_TRIANGLES, 0, mesh->getGroups()[i]->getFaces().size() * 3);
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}