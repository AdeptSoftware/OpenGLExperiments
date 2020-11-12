#pragma once
#include "Resources/object.h"
#include "camera.h"
#include "loader.h"

#define STEP			0.05f

CObject cube(vCubeTexture, sizeof(vCubeTexture), false);
CObject grid(vGrid, 528);
CCamera g_camera({ 0.0f, 1.0f, 10.0f });

GLfloat g_fCenterX = 320.0f;
GLfloat g_fCenterY = 240.0f;

GLint g_obj_mode = 0;
GLint g_cam_mode = 0;
GLboolean g_bTexture = true;

void SetCubeParam(GLfloat x, GLfloat y, GLfloat z) {
	if (g_obj_mode == 0) cube.Position({ x, y, z }, true);
	else if (g_obj_mode == 1) cube.Rotate({ x, y, z }, true);
	else if (g_obj_mode == 2) cube.Scale({ x, y, z }, true);
}

void OnWndSize(GLFWwindow* pWindow, GLsizei nWidth, GLsizei nHeight) {
	glViewport(0, 0, nWidth, nHeight);
	g_fCenterY = float(nHeight)/2;
	g_fCenterX = float(nWidth)/2;
}

void OnMouse(GLFWwindow* pWindow, GLint nKey, GLint nAction, GLint nMods) {
	/*if (nKey == GLFW_MOUSE_BUTTON_LEFT) {
		if (nAction == GLFW_PRESS)			g_capture_cam = false;
		else if (nAction == GLFW_RELEASE)	g_capture_cam = false;
	}*/
}

void OnCursorPos(GLFWwindow* pWindow, GLdouble x, GLdouble y) {
	glfwSetCursorPos(pWindow, g_fCenterX, g_fCenterY);
	g_camera.ProcessMouseMovement(float(x - g_fCenterX), float(g_fCenterY - y));
}

void OnKey(GLFWwindow* pWindow, GLint nKey, GLint nScanCode, GLint nAction, GLint nMode) {
	if (nKey == GLFW_KEY_ESCAPE && nAction == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, GL_TRUE);
	if (nKey == GLFW_KEY_PAUSE && nAction == GLFW_PRESS)
		system("pause");
	if (nAction == GLFW_REPEAT || nAction == GLFW_PRESS) {
		if (nKey == GLFW_KEY_RIGHT)			  SetCubeParam( STEP,  0.0f,  0.0f);
		else if (nKey == GLFW_KEY_LEFT)	      SetCubeParam(-STEP,  0.0f,  0.0f);
		else if (nKey == GLFW_KEY_UP)		  SetCubeParam( 0.0f,  STEP,  0.0f);
		else if (nKey == GLFW_KEY_DOWN)		  SetCubeParam( 0.0f, -STEP,  0.0f);
		else if (nKey == GLFW_KEY_KP_1)		  SetCubeParam( 0.0f,  0.0f,  STEP);
		else if (nKey == GLFW_KEY_KP_0)		  SetCubeParam( 0.0f,  0.0f, -STEP);
		else if (nKey == GLFW_KEY_1)		  g_obj_mode = 0;	// Position
		else if (nKey == GLFW_KEY_2)		  g_obj_mode = 1;	// Rotate
		else if (nKey == GLFW_KEY_3)		  g_obj_mode = 2;	// Scale

		else if (nKey == GLFW_KEY_A)		  g_camera.ProcessKeyboard(LEFT, 1);
		else if (nKey == GLFW_KEY_D)		  g_camera.ProcessKeyboard(RIGHT, 1);
		else if (nKey == GLFW_KEY_W)		  g_camera.ProcessKeyboard(FORWARD, 1);
		else if (nKey == GLFW_KEY_S)		  g_camera.ProcessKeyboard(BACKWARD, 1);
		else if (nKey == GLFW_KEY_KP_DECIMAL) g_camera.ProcessMouseScroll(-0.0f);
		else if (nKey == GLFW_KEY_KP_ADD)	  g_camera.ProcessMouseScroll(1.0f);

		else if (nKey == GLFW_KEY_T)		  g_bTexture = !g_bTexture;
	}
}