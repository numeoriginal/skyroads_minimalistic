#pragma once
#include <Component/SimpleScene.h>
#include "Tema2Camera.h"
#include <vector>
#include <Core/GPU/Mesh.h>

class Tema2 : public SimpleScene
{
	public:
		Tema2();
		~Tema2();

		typedef struct Drum {
			float x, y, z;
			float lenght;

			int type;
			bool hit;

		}Drum;

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		void GemeratePlatform();
		void GenerateDroom();
		void GenerateBar();
		void SetCameraPersons();
		Drum collisionEffect(Drum el);
		void SpawnThings(glm::mat4 modelMatrix, Drum el);
		void colisiones();
		void RenderSimpleMeshTema2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
		
	
		Mesh* CreateMeshTema2(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);

	protected:
		Tema::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
		bool type;

		
};
