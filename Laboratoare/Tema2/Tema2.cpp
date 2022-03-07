#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include <random>

using namespace std;

typedef struct Plajer {
	float x = 0.f;
	float y = 0.4f;
	float z = 0.f;

}Plajer;


Plajer player;

glm::vec3 albastru =   glm::vec3(0, 0, 1);
glm::vec3 galben =     glm::vec3(1, 1, 0);
glm::vec3 rosu =       glm::vec3(1, 0, 0);
glm::vec3 verde =      glm::vec3(0, 1, 0);
glm::vec3 portocaliu = glm::vec3(1, 0.5f, 0);
glm::vec3 purple =     glm::vec3(0.5f, 0, 0.5f);
int contorizare = -1;
int peepo = 0;
int score = 0;
int contor = 1;
int timp_oranj = 0;
long int nrColozions = 0;
bool persUno = false;
bool setCamera = false;
bool jump = false;
bool globalColizion = false;
bool aliverino1 = true;
bool aliverino2 = true;
bool aliverino3 = true;
bool dead = false;
bool movingUp = true;
float speed = 0, speed_coef = 0, flyTime = 0, plajer_X = 0;
float moveBlyat = 0.f;
float fuelScale = 2.8f;
float dissapear = 1.f;
float offset = 1.2f;
float speedBila = 5.0f;
float keks = .35f;
float acc = 0.f;
float timeStamp;

vector <Tema2::Drum> drumuriLeft;
vector <Tema2::Drum> drumuriMid;
vector <Tema2::Drum> drumuriRight;

Tema2::Tema2()
{

}
Tema2::~Tema2()
{

}
void Tema2::Init()
{
	renderCameraTarget = false;

	camera = new Tema::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	GetCameraInput()->SetActive(false); // dont show camera coords

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	// platform
	{
		{
			vector<VertexFormat> vertices1
			{
				VertexFormat(glm::vec3(0,  0,  1), glm::vec3(1.0f, 1.0f, 0.15f)),
				VertexFormat(glm::vec3(1,  0,  1), glm::vec3(1.0f, 1.0f, 0.15f)),
				VertexFormat(glm::vec3(0,  1,  1), glm::vec3(1.0f, 1.0f, 0.15f)),
				VertexFormat(glm::vec3(1,  1,  1), glm::vec3(1.0f, 1.0f, 0.15f)),
				VertexFormat(glm::vec3(0,  0,  0), glm::vec3(1.0f, 1.0f, 0.15f)),
				VertexFormat(glm::vec3(1,  0,  0), glm::vec3(1.0f, 1.0f, 0.15f)),
				VertexFormat(glm::vec3(0,  1,  0), glm::vec3(1.0f, 1.0f, 0.15f)),
				VertexFormat(glm::vec3(1,  1,  0), glm::vec3(1.0f, 1.0f, 0.15f)),

				
			};

			vector<unsigned short> indices =
			{
				0, 1, 2,	
				1, 3, 2,	
				2, 3, 7,
				2, 7, 6,
				1, 7, 3,
				1, 5, 7,
				6, 7, 4,
				7, 5, 4,
				0, 4, 1,
				1, 4, 5,
				2, 6, 4,
				0, 2, 4

			};
			vector<VertexFormat> vertices2
			{
				VertexFormat(glm::vec3(0,  0,  1), glm::vec3(0.9f, 0.1f, 0.1f)),
				VertexFormat(glm::vec3(1,  0,  1), glm::vec3(0.9f, 0.1f, 0.1f)),
				VertexFormat(glm::vec3(0,  1,  1), glm::vec3(0.9f, 0.1f, 0.1f)),
				VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0.9f, 0.1f, 0.1f)),
				VertexFormat(glm::vec3(0,  0,  0), glm::vec3(0.9f, 0.1f, 0.1f)),
				VertexFormat(glm::vec3(1,  0,  0), glm::vec3(0.9f, 0.1f, 0.1f)),
				VertexFormat(glm::vec3(0,  1,  0), glm::vec3(0.9f, 0.1f, 0.1f)),
				VertexFormat(glm::vec3(1, 1, 0), glm::vec3(0.9f, 0.1f, 0.1f)),


			};
			vector<VertexFormat> vertices3
			{
				VertexFormat(glm::vec3(0,  0,  1), glm::vec3(0.1f, 0.f, 0.3f)),
				VertexFormat(glm::vec3(1,  0,  1), glm::vec3(0.1f, 0.f, 0.3f)),
				VertexFormat(glm::vec3(0,  1,  1), glm::vec3(0.1f, 0.f, 0.3f)),
				VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0.1f, 0.f, 0.3f)),
				VertexFormat(glm::vec3(0,  0,  0), glm::vec3(0.1f, 0.f, 0.3f)),
				VertexFormat(glm::vec3(1,  0,  0), glm::vec3(0.1f, 0.f, 0.3f)),
				VertexFormat(glm::vec3(0,  1,  0), glm::vec3(0.1f, 0.f, 0.3f)),
				VertexFormat(glm::vec3(1,  1,  0), glm::vec3(0.1f, 0.f, 0.3f)),

			};
			vector<VertexFormat> vertices4
			{
				VertexFormat(glm::vec3(0,  0,  1), glm::vec3(0.1f, 0.2f, 0.7f)),
				VertexFormat(glm::vec3(1,  0,  1), glm::vec3(0.1f, 0.2f, 0.7f)),
				VertexFormat(glm::vec3(0,  1,  1), glm::vec3(0.1f, 0.2f, 0.7f)),
				VertexFormat(glm::vec3(1,  1,  1), glm::vec3(0.1f, 0.2f, 0.7f)),
				VertexFormat(glm::vec3(0,  0,  0), glm::vec3(0.1f, 0.2f, 0.7f)),
				VertexFormat(glm::vec3(1,  0,  0), glm::vec3(0.1f, 0.2f, 0.7f)),
				VertexFormat(glm::vec3(0,  1,  0), glm::vec3(0.1f, 0.2f, 0.7f)),
				VertexFormat(glm::vec3(1,  1,  0), glm::vec3(0.1f, 0.2f, 0.7f)),

			};

			meshes["cube1"] = new Mesh("generated cube 1");
			meshes["cube1"]->InitFromData(vertices1, indices);

			meshes["cube2"] = new Mesh("generated cube 2");
			meshes["cube2"]->InitFromData(vertices2, indices);

			meshes["cube3"] = new Mesh("generated cube 3");
			meshes["cube3"]->InitFromData(vertices3, indices);

			meshes["cube4"] = new Mesh("generated cube 4");
			meshes["cube4"]->InitFromData(vertices4, indices);
		}
	}
	// runners
	{
		{	
			// albastru		
			vector<VertexFormat> drumVertices
			{
				VertexFormat(glm::vec3(0,  0,  1), albastru),
				VertexFormat(glm::vec3(1,  0,  1), albastru),
				VertexFormat(glm::vec3(0,  1,  1), albastru),
				VertexFormat(glm::vec3(1,  1,  1), albastru),
				VertexFormat(glm::vec3(0,  0,  0), albastru),
				VertexFormat(glm::vec3(1,  0,  0), albastru),
				VertexFormat(glm::vec3(0,  1,  0), albastru),
				VertexFormat(glm::vec3(1,  1,  0), albastru),


			};
			vector<unsigned short> drumIndices =
			{
				0, 1, 2,
				1, 3, 2,
				2, 3, 7,
				2, 7, 6,
				1, 7, 3,
				1, 5, 7,
				6, 7, 4,
				7, 5, 4,
				0, 4, 1,
				1, 4, 5,
				2, 6, 4,
				0, 2, 4

			};		
			//rosu			
				vector<VertexFormat> drumVertices1
				{
					VertexFormat(glm::vec3(0,  0,  1), rosu),
					VertexFormat(glm::vec3(1,  0,  1), rosu),
					VertexFormat(glm::vec3(0,  1,  1), rosu),
					VertexFormat(glm::vec3(1,  1,  1), rosu),
					VertexFormat(glm::vec3(0,  0,  0), rosu),
					VertexFormat(glm::vec3(1,  0,  0), rosu),
					VertexFormat(glm::vec3(0,  1,  0), rosu),
					VertexFormat(glm::vec3(1,  1,  0), rosu),


				};
			//galben		
				vector<VertexFormat> drumVertices2
				{
					VertexFormat(glm::vec3(0,  0,  1), galben),
					VertexFormat(glm::vec3(1,  0,  1), galben),
					VertexFormat(glm::vec3(0,  1,  1), galben),
					VertexFormat(glm::vec3(1,  1,  1), galben),
					VertexFormat(glm::vec3(0,  0,  0), galben),
					VertexFormat(glm::vec3(1,  0,  0), galben),
					VertexFormat(glm::vec3(0,  1,  0), galben),
					VertexFormat(glm::vec3(1,  1,  0), galben),


				};		
			//verde		
				vector<VertexFormat> drumVertices3
				{
					VertexFormat(glm::vec3(0,  0,  1), verde),
					VertexFormat(glm::vec3(1,  0,  1), verde),
					VertexFormat(glm::vec3(0,  1,  1), verde),
					VertexFormat(glm::vec3(1,  1,  1), verde),
					VertexFormat(glm::vec3(0,  0,  0), verde),
					VertexFormat(glm::vec3(1,  0,  0), verde),
					VertexFormat(glm::vec3(0,  1,  0), verde),
					VertexFormat(glm::vec3(1,  1,  0), verde),

				};		
			//morcov		
				vector<VertexFormat> drumVertices4
				{
					VertexFormat(glm::vec3(0,  0,  1), portocaliu),
					VertexFormat(glm::vec3(1,  0,  1), portocaliu),
					VertexFormat(glm::vec3(0,  1,  1), portocaliu),
					VertexFormat(glm::vec3(1,  1,  1), portocaliu),
					VertexFormat(glm::vec3(0,  0,  0), portocaliu),
					VertexFormat(glm::vec3(1,  0,  0), portocaliu),
					VertexFormat(glm::vec3(0,  1,  0), portocaliu),
					VertexFormat(glm::vec3(1,  1,  0), portocaliu),


				};
				// purple
				vector<VertexFormat> drumVertices5
				{
					VertexFormat(glm::vec3(0,  0,  1), purple),
					VertexFormat(glm::vec3(1,  0,  1), purple),
					VertexFormat(glm::vec3(0,  1,  1), purple),
					VertexFormat(glm::vec3(1,  1,  1), purple),
					VertexFormat(glm::vec3(0,  0,  0), purple),
					VertexFormat(glm::vec3(1,  0,  0), purple),
					VertexFormat(glm::vec3(0,  1,  0), purple),
					VertexFormat(glm::vec3(1,  1,  0), purple),
				};
				vector<VertexFormat> drumVertices6
				{
					VertexFormat(glm::vec3(0,  0,  1), albastru),
					VertexFormat(glm::vec3(1,  0,  1), rosu),
					VertexFormat(glm::vec3(0,  1,  1), albastru),
					VertexFormat(glm::vec3(1,  1,  1), verde),
					VertexFormat(glm::vec3(0,  0,  0), albastru),
					VertexFormat(glm::vec3(1,  0,  0), portocaliu),
					VertexFormat(glm::vec3(0,  1,  0), albastru),
					VertexFormat(glm::vec3(1,  1,  0), purple),


				};
			
			meshes["dB"] = new Mesh("Albastru");
			meshes["dB"]->InitFromData(drumVertices, drumIndices);

			meshes["dR"] = new Mesh("Rosu");
			meshes["dR"]->InitFromData(drumVertices1, drumIndices);

			meshes["dG"] = new Mesh("galben");
			meshes["dG"]->InitFromData(drumVertices2, drumIndices);

			meshes["dV"] = new Mesh("verde");
			meshes["dV"]->InitFromData(drumVertices3, drumIndices);

			meshes["dP"] = new Mesh("Portocala");
			meshes["dP"]->InitFromData(drumVertices4, drumIndices);

			meshes["hit"] = new Mesh("Purple");
			meshes["hit"]->InitFromData(drumVertices5, drumIndices);

			meshes["BS"] = new Mesh("bonus");
			meshes["BS"]->InitFromData(drumVertices6, drumIndices);
		}

	}
	//bar
	{
	{
			vector<VertexFormat>BarVertices1
			{
				VertexFormat(glm::vec3(0, 0,  0), glm::vec3(1, 1, 1)),
				VertexFormat(glm::vec3(0, 1,  0), glm::vec3(1, 1, 1)),
				VertexFormat(glm::vec3(1, 1,  0), glm::vec3(1, 1, 1)),
				VertexFormat(glm::vec3(1, 0,  0), glm::vec3(1, 1, 1)),
			};
			vector<unsigned short> BarIndices =
			{
				0, 3, 1,
				1, 2, 3
			};

			vector<VertexFormat>BarVertices2
			{
				VertexFormat(glm::vec3(0, 0,  0), verde),
				VertexFormat(glm::vec3(0, 1,  0), verde),
				VertexFormat(glm::vec3(1, 1,  0), verde),
				VertexFormat(glm::vec3(1, 0,  0), verde),
			};
			vector<VertexFormat>BarVertices3
			{
				VertexFormat(glm::vec3(0, 0,  0), portocaliu),
				VertexFormat(glm::vec3(0, 1,  0), portocaliu),
				VertexFormat(glm::vec3(1, 1,  0), portocaliu),
				VertexFormat(glm::vec3(1, 0,  0), portocaliu),
			};
			vector<VertexFormat>BarVertices4
			{
				VertexFormat(glm::vec3(0, 0,  0), rosu),
				VertexFormat(glm::vec3(0, 1,  0), rosu),
				VertexFormat(glm::vec3(1, 1,  0), rosu),
				VertexFormat(glm::vec3(1, 0,  0), rosu),
			};
		
			meshes["Bar1"] = new Mesh("generated cube 1");
			meshes["Bar1"]->InitFromData(BarVertices1, BarIndices);
			meshes["Bar2V"] = new Mesh("generated cube 2");
			meshes["Bar2V"]->InitFromData(BarVertices2, BarIndices);
			meshes["Bar2G"] = new Mesh("generated cube 3");
			meshes["Bar2G"]->InitFromData(BarVertices3, BarIndices);
			meshes["Bar2R"] = new Mesh("generated cube 4");
			meshes["Bar2R"]->InitFromData(BarVertices4, BarIndices);
		}
	}
	//left row
	{
		Drum aux2{};
		aux2.x = -4.1f;
		aux2.y = 0.f;
		aux2.z = -6.f;
		aux2.hit = false;
		aux2.lenght = 8;
		aux2.type = 1;

		drumuriLeft.push_back(aux2);

		aux2.x = -4.1f;
		aux2.y = 0.f;
		aux2.z = -16.f;
		aux2.hit = false;
		aux2.lenght = 8;
		aux2.type = 1;

		drumuriLeft.push_back(aux2);

		aux2.x = -4.1f;
		aux2.y = 0.f;
		aux2.z = -26.f;
		aux2.hit = false;
		aux2.lenght = 8;
		aux2.type = 1;

		drumuriLeft.push_back(aux2);

	}
	// mid
	{
		Drum aux1{};
		aux1.x = -.75f;
		aux1.y = 0.f;
		aux1.z = -6.f;
		aux1.hit = false;
		aux1.lenght = 8;
		aux1.type = 1;

		drumuriMid.push_back(aux1);

		aux1.x = -.75f;
		aux1.y = 0.f;
		aux1.z = -16.f;
		aux1.hit = false;
		aux1.lenght = 8;
		aux1.type = 1;

		drumuriMid.push_back(aux1);

		aux1.x = -.75f;
		aux1.y = 0.f;
		aux1.z = -26.f;
		aux1.hit = false;
		aux1.lenght = 8;
		aux1.type = 1;

		drumuriMid.push_back(aux1);
	}
	//right
	{
		Drum aux3{};
		aux3.x = 2.6f;
		aux3.y = 0.f;
		aux3.z = -6.f;
		aux3.hit = false;
		aux3.lenght = 8;
		aux3.type = 1;

		drumuriRight.push_back(aux3);

		aux3.x = 2.6f;
		aux3.y = 0.f;
		aux3.z = -16.f;
		aux3.hit = false;
		aux3.lenght = 8;
		aux3.type = 1;

		drumuriRight.push_back(aux3);

		aux3.x = 2.6f;
		aux3.y = 0.f;
		aux3.z = -26.f;
		aux3.hit = false;
		aux3.lenght = 8;
		aux3.type = 1;

		drumuriRight.push_back(aux3);
	}

	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}
void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}
void Tema2::SetCameraPersons() {

	if (!setCamera)
	{
		camera->Set(glm::vec3(0, 2, 6.f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
		persUno = false;
	}
	else
	{
		persUno = true;
		camera->Set(glm::vec3(player.x, player.y,  -0.5), glm::vec3(player.x, player.y, -5), glm::vec3(0, 1, 0));
	}
}
Tema2::Drum Tema2::collisionEffect(Drum el)
{	
	switch (el.type)
	{
	case 1:
		score++;
		cout << "Score: " << score << endl;
		break;
	case 2:
		timp_oranj += 70;
		timeStamp += 7;
		if (score > 0)
		{
			score--;
			cout << "Score: " << score << endl;
		}
		break;
	case 3:
		fuelScale -= 0.3f;
		timeStamp += 7;
		if (score > 0)
		{
			score--;
			cout << "Score: " << score << endl;
		}
		break;
	case 4:
		fuelScale += 0.5f;
		timeStamp += 7;
		score += 2;
		cout << "Score: " << score << endl;
		break;
	case 5:
		cout << endl << endl << endl;
		cout << "Final Score: " << score << endl;
		cout << "GAME OVER" << endl;
		window->Close();
		break;
	default:
		
		break;
	}
	el.type = 6;
	return el;
}
void Tema2::SpawnThings(glm::mat4 modelMatrix, Drum el)
{
	switch (el.type)
	{
	case 1:
		RenderMesh(meshes["dB"], shaders["VertexColor"], modelMatrix);

		break;
	case 2:
		RenderMesh(meshes["dP"], shaders["VertexColor"], modelMatrix);

		break;
	case 3:
		RenderMesh(meshes["dG"], shaders["VertexColor"], modelMatrix);

		break;
	case 4:
		RenderMesh(meshes["dV"], shaders["VertexColor"], modelMatrix);

		break;
	case 5:
		RenderMesh(meshes["dR"], shaders["VertexColor"], modelMatrix);

		break;
	default:
		RenderMesh(meshes["hit"], shaders["VertexColor"], modelMatrix);
		break;
	}
}
void Tema2::colisiones()
{
	float x, y, z, distance;
	//left 
	{
		for (int i = 0; i < 3; i++)
		{
			x = max(drumuriLeft.at(i).x - .3f, min(player.x, drumuriLeft.at(i).x + 1.45f));
			y = max(drumuriLeft.at(i).y, min(player.y, drumuriLeft.at(i).y + 0.1f));
			z = max(drumuriLeft.at(i).z + 0.1f, min(player.z, drumuriLeft.at(i).z + speed_coef + 0.1f));

			distance = sqrt((x - player.x) * (x - player.x) +
				(y - player.y) * (y - player.y) +
				(z - player.z) * (z - player.z));

			if (player.y == 0.4f && distance <= 0.3f)
			{
				drumuriLeft.at(i) = collisionEffect(drumuriLeft.at(i));
				
				nrColozions++;
				drumuriLeft.at(i).hit = true;
			}
			else
			{
				drumuriLeft.at(i).hit = false;
			}
		}
	}
	//mid
	{
		for (int i = 0; i < 3; i++)
		{
			x = max(drumuriMid.at(i).x - .1f, min(player.x, drumuriMid.at(i).x + 1.45f));
			y = max(drumuriMid.at(i).y, min(player.y, drumuriMid.at(i).y + 0.1f));
			z = max(drumuriMid.at(i).z + 0.1f, min(player.z, drumuriMid.at(i).z + speed_coef + 0.1f));

			distance = sqrt((x - player.x) * (x - player.x) +
				(y - player.y) * (y - player.y) +
				(z - player.z) * (z - player.z));

			if (player.y == 0.4f && distance <= 0.3f)
			{
				drumuriMid.at(i) = collisionEffect(drumuriMid.at(i));
			
				nrColozions++;
				drumuriMid.at(i).hit = true;
			}
			else
			{
				drumuriMid.at(i).hit = false;
			}
		}
	}
	//right
	{
		for (int i = 0; i < 3; i++)
		{
			x = max(drumuriRight.at(i).x - .1f, min(player.x, drumuriRight.at(i).x + 1.45f));
			y = max(drumuriRight.at(i).y, min(player.y, drumuriRight.at(i).y + 0.1f));
			z = max(drumuriRight.at(i).z + 0.1f, min(player.z, drumuriRight.at(i).z + speed_coef + 0.1f));

			distance = sqrt((x - player.x) * (x - player.x) +
				(y - player.y) * (y - player.y) +
				(z - player.z) * (z - player.z));

			if (player.y == 0.4f && distance <= 0.3f)
			{
				
				drumuriRight.at(i) = collisionEffect(drumuriRight.at(i));
				nrColozions++;
				drumuriRight.at(i).hit = true;
			}
			else
			{
				drumuriRight.at(i).hit = false;
			}
		}
	}

}
void Tema2::GemeratePlatform()
{
	{
		glm::mat4 startArea = glm::mat4(1);
		startArea = glm::translate(startArea, glm::vec3(-3.f,0,-3.f + speed_coef));
		startArea = glm::scale(startArea, glm::vec3(6.f, 0.1f, 6.f));
		RenderMesh(meshes["cube2"], shaders["VertexColor"], startArea);
	}
	// right side
	{
		
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(5.f, 0, -0.75f + speed_coef)); 
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.5f));
			RenderMesh(meshes["cube3"], shaders["VertexColor"], modelMatrix);
		}
		{

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(3.f, 0, 0.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, .1f, 1.f));
			RenderMesh(meshes["cube1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(4.f, 0.0f, 0.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(4.f, 0.0, -1.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(3.f, 0.0, 1.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(3.f, 0., -1.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(3.f, 0.0, -2.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
	}
	// left side
	{
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-6.f, 0, -0.75f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.5f));
			RenderMesh(meshes["cube3"], shaders["VertexColor"], modelMatrix);
		}
		{

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.f, 0, 0.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, .1f, 1.f));
			RenderMesh(meshes["cube1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.f, 0., -1.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-5.f, 0.0f, -1.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-5.f, 0.0, 0.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.f, 0.0, -2.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-4.f, 0.0, 1.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
	}
	// bottom
	{
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-.75f, 0, 5.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f, 0.1f, 1.f));
			RenderMesh(meshes["cube3"], shaders["VertexColor"], modelMatrix);
		}
		{

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-.0f, 0, 3.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, .1f, 1.f));
			RenderMesh(meshes["cube1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.f, 0., 3.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.f, 0.0f, 4.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-.0f, 0.0, 4.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.f, 0.0, 3.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(1.f, 0.0, 3.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
	}
	// top
	{
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-.75f, 0, -6.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f, 0.1f, 1.f));
			RenderMesh(meshes["cube3"], shaders["VertexColor"], modelMatrix);
		}
		{

			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-.0f, 0, -4.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, .1f, 1.f));
			RenderMesh(meshes["cube1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.f, 0., -4.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.f, 0.0f, -5.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-.0f, 0.0, -5.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.f, 0.0, -4.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(1.f, 0.0, -4.f + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, 0.1f, 1.f));
			RenderMesh(meshes["cube4"], shaders["VertexColor"], modelMatrix);
		}
	}

	// end
}
void Tema2::GenerateDroom()
{

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(7, 8);
	uniform_int_distribution<> distr_z(0, 1);
	uniform_int_distribution<> distr_type(1, 5);
	//left
	{
		for (int i = 0; i < drumuriLeft.size(); i++)
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(drumuriLeft.at(i).x, drumuriLeft.at(i).y, drumuriLeft.at(i).z + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f, 0.1f, -drumuriLeft.at(i).lenght));

			SpawnThings(modelMatrix, drumuriLeft.at(i));
		

		}


		if (drumuriLeft.at(0).z + speed_coef > dissapear + drumuriLeft.at(0).lenght)
		{
			
			drumuriLeft.at(0).z = drumuriLeft.at(2).z  - drumuriLeft.at(2).lenght - distr_z(gen) - offset;
			drumuriLeft.at(0).lenght = (float)distr(gen);
			drumuriLeft.at(0).type = distr_type(gen);

			if (drumuriLeft.at(0).type == 5)
			{
				drumuriLeft.at(0).type = distr_type(gen);
			}
		}
		if (drumuriLeft.at(1).z + speed_coef > dissapear + drumuriLeft.at(1).lenght)
		{
			drumuriLeft.at(1).z = drumuriLeft.at(0).z  - drumuriLeft.at(1).lenght - distr_z(gen) - offset;
			drumuriLeft.at(1).lenght = (float)distr(gen);
			drumuriLeft.at(1).type = distr_type(gen);

			if (drumuriLeft.at(1).type == 5)
			{
				drumuriLeft.at(1).type = distr_type(gen);
			}
		}
		if (drumuriLeft.at(2).z + speed_coef > dissapear + drumuriLeft.at(2).lenght)
		{
			drumuriLeft.at(2).z = drumuriLeft.at(1).z  - drumuriLeft.at(1).lenght - distr_z(gen) - offset;
			drumuriLeft.at(2).lenght = (float)distr(gen);
			drumuriLeft.at(2).type = distr_type(gen);

			if (drumuriLeft.at(2).type == 5)
			{
				drumuriLeft.at(2).type = distr_type(gen);
			}
		}
	}
	// mid
	{
		for (int i = 0; i < drumuriMid.size(); i++)
		{

			glm::mat4 modelMatrix = glm::mat4(1);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(drumuriMid.at(i).x, drumuriMid.at(i).y, drumuriMid.at(i).z + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f, 0.1f, -drumuriMid.at(i).lenght));
			SpawnThings(modelMatrix, drumuriMid.at(i));
			
		}


		if (drumuriMid.at(0).z + speed_coef > dissapear + drumuriMid.at(0).lenght)
		{
			drumuriMid.at(0).z = drumuriMid.at(2).z - drumuriMid.at(2).lenght - distr_z(gen) - offset;
			drumuriMid.at(0).lenght = (float)distr(gen);
			drumuriMid.at(0).type = distr_type(gen);

			if (drumuriMid.at(0).type == 5)
			{
				drumuriMid.at(0).type = distr_type(gen);
			}
		}
		if (drumuriMid.at(1).z + speed_coef > dissapear + drumuriMid.at(1).lenght)
		{
			drumuriMid.at(1).z = drumuriMid.at(0).z - drumuriMid.at(1).lenght - distr_z(gen) - offset;
			drumuriMid.at(1).lenght = (float)distr(gen);
			drumuriMid.at(1).type = distr_type(gen);

			if (drumuriMid.at(1).type == 5)
			{
				drumuriMid.at(1).type = distr_type(gen);
			}
		}
		if (drumuriMid.at(2).z + speed_coef > dissapear + drumuriMid.at(2).lenght)
		{
			drumuriMid.at(2).z = drumuriMid.at(1).z - drumuriMid.at(1).lenght - distr_z(gen) - offset;
			drumuriMid.at(2).lenght = (float)distr(gen);
			drumuriMid.at(2).type = distr_type(gen);

			if (drumuriMid.at(2).type == 5)
			{
				drumuriMid.at(2).type = distr_type(gen);
			}

		}
	}
	//right
	{
		for (int i = 0; i < drumuriRight.size(); i++)
		{

			glm::mat4 modelMatrix = glm::mat4(1);

			modelMatrix = glm::translate(modelMatrix, glm::vec3(drumuriRight.at(i).x, drumuriRight.at(i).y, drumuriRight.at(i).z + speed_coef));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f, 0.1f, -drumuriRight.at(i).lenght));
			SpawnThings(modelMatrix, drumuriRight.at(i));
		

		}


		if (drumuriRight.at(0).z + speed_coef > dissapear + drumuriRight.at(0).lenght)
		{
			drumuriRight.at(0).z = drumuriRight.at(2).z - drumuriRight.at(2).lenght - distr_z(gen) - offset;
			drumuriRight.at(0).lenght = (float)distr(gen);
			drumuriRight.at(0).type = distr_type(gen);

			if (drumuriRight.at(0).type == 5)
			{
				drumuriRight.at(0).type = distr_type(gen);
			}
		}
		if (drumuriRight.at(1).z + speed_coef > dissapear + drumuriRight.at(1).lenght)
		{
			drumuriRight.at(1).z = drumuriRight.at(0).z - drumuriRight.at(1).lenght - distr_z(gen) - offset;
			drumuriRight.at(1).lenght = (float)distr(gen);
			drumuriRight.at(1).type = distr_type(gen);

			if (drumuriRight.at(1).type == 5)
			{
				drumuriRight.at(1).type = distr_type(gen);
			}

		}
		if (drumuriRight.at(2).z + speed_coef > dissapear + drumuriRight.at(2).lenght)
		{
			drumuriRight.at(2).z = drumuriRight.at(1).z - drumuriRight.at(1).lenght - distr_z(gen) - offset;
			drumuriRight.at(2).lenght = (float)distr(gen);
			drumuriRight.at(2).type = distr_type(gen);

			if (drumuriRight.at(2).type == 5)
			{
				drumuriRight.at(2).type = distr_type(gen);
			}

		}
	}
}
void Tema2::GenerateBar()
{

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.2f, 4.33f, -8.8f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(2.8f, .4f, 0.f));
			RenderMesh(meshes["Bar1"], shaders["VertexColor"], modelMatrix);
		}
		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.2f, 4.312f, -8.7f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(fuelScale, .4f, 0.f));
			if (fuelScale > 1.8)
			{
				RenderMesh(meshes["Bar2V"], shaders["VertexColor"], modelMatrix);
			}
			else if (fuelScale > 0.8)
			{
				RenderMesh(meshes["Bar2G"], shaders["VertexColor"], modelMatrix);
			}
			else
			{
				RenderMesh(meshes["Bar2R"], shaders["VertexColor"], modelMatrix);
			}
		}


}


void Tema2::Update(float deltaTimeSeconds)
{
	peepo = 0;

	//generate initial platform
	GemeratePlatform();
	//generate platforms
	GenerateDroom();
	// generate fuel bar
	GenerateBar();
	// check for collisions
	colisiones();
	//change camera view
    SetCameraPersons();
	
	// spawn player
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(player.x, player.y, player.z));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.7f, 0.7f, 0.7f));
		if (timeStamp > 0)
		{
			timeStamp -= deltaTimeSeconds * 5.8f;
			if (persUno == false)
			{
				
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, - 5));
				RenderSimpleMeshTema2(meshes["sphere"], shaders["ShaderTema2"], modelMatrix);
				
			}
			
		}
		else {
			
			RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (drumuriLeft.at(i).hit || drumuriMid.at(i).hit || drumuriRight.at(i).hit)
		{
			peepo++;	}

	}
	if (nrColozions > 0 && peepo == 0 && jump == false)
	{
		
		dead = true;
		player.y -= deltaTimeSeconds * 3.2f;
		
	}
	if (player.y < -5)
	{
		cout << endl << endl << endl;
		cout << "Final Score: " << score << endl;
		cout << "Fell of the platform --> GAME OVER!" << endl;
		window->Close();
	}

	// jump logic
	{
		if (jump)
		{
			float newY = 0.4f + speedBila * flyTime - 0.5f * 10.f * flyTime * flyTime;
			flyTime += 0.01f;
			player.y = max(newY, player.y);
			if (newY >= 0.4f)
			{
				player.y = newY;
			}
			else
			{
				player.y = 0.4f;
				jump = false;
				flyTime = 0;
			}

		}
	}
	// fuels scale limit
	{
		if (fuelScale > 2.8f)
		{
			fuelScale = 2.8f;
		}// no fuel left :(
		else if (fuelScale <= 0)
		{
			cout << endl << endl << endl;
			cout << "Final Score: " << score << endl;
			cout << "Out of fuel --> GAME OVER!" << endl;
			window->Close();
		}
	}
}
void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}
void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}
// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h
void Tema2::RenderSimpleMeshTema2(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");

	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");

	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// TODO : get shader location for uniform mat4 "Projection"
	GLint projectLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");

	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(projectLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	GLint time_location = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(time_location, timeStamp);


	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}
Mesh* Tema2::CreateMeshTema2(const char* name, const vector<VertexFormat>& vertices, const vector<unsigned short>& indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// TODO: Create the VBO and bind it
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// TODO: Crete the IBO and bind it
	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// TODO: Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	meshes[name]->vertices = vertices;
	meshes[name]->indices = indices;
	return meshes[name];
}
void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (!dead)
	{
		// orange plato effect	
		{
			if (timp_oranj == 0)
			{
				//hold W to increase speed
				if (window->KeyHold(GLFW_KEY_W))
				{
					acc += deltaTime * keks;
					contorizare++;
				}// hold to decrease speed
				if (window->KeyHold(GLFW_KEY_S))
				{
					if (contorizare > 0)
					{
						acc -= deltaTime * keks;
						contorizare--;
					}
					else if (contorizare == 0)
					{
						acc = 0;
					}
				}
			}
			if (timp_oranj > 0)
			{
				timp_oranj -= deltaTime * 0.1f;
			}
		}
		//logic of fuel usage while moving
		if (fuelScale > 0)
		{
			if (speed_coef <= 0)
			{
				speed_coef *= -1;
			}
			if (acc != 0)
			{
				fuelScale -= deltaTime * (speed_coef / 3000);
			}
		}
		else
		{
			fuelScale = 0.f;
		}
		// hold to move left
		if (window->KeyHold(GLFW_KEY_A))
		{
			player.x -= deltaTime * 3.5f;
		}// and right
		if (window->KeyHold(GLFW_KEY_D))
		{
			player.x += deltaTime * 3.5f;
		}
	}
	speed_coef += acc;
}
void Tema2::OnKeyPress(int key, int mods)
{
	if (!dead)
	{
		// press to jump
		if (key == GLFW_KEY_SPACE && flyTime < 0.4f && jump == false)
		{
			flyTime = 0;
			jump = true;

		}
		// press to switch camera view
		if (key == GLFW_KEY_C) {
			contor++;
			if (contor % 2 == 0)
			{
				setCamera = true;
			}
			else
			{
				setCamera = false;
			}
		}
	}
}
void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}
void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	
}
void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}
void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}
void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
void Tema2::OnWindowResize(int width, int height)
{
}


