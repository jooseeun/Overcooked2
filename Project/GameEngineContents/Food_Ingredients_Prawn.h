#pragma once
#include "GamePlayObject.h"
// Ό³Έν :
class Food_Ingredients_Prawn : public GamePlayObject
{
public:
	// constrcuter destructer
	Food_Ingredients_Prawn();
	~Food_Ingredients_Prawn();

	// delete Function
	Food_Ingredients_Prawn(const Food_Ingredients_Prawn& _Other) = delete;
	Food_Ingredients_Prawn(Food_Ingredients_Prawn&& _Other) noexcept = delete;
	Food_Ingredients_Prawn& operator=(const Food_Ingredients_Prawn& _Other) = delete;
	Food_Ingredients_Prawn& operator=(Food_Ingredients_Prawn&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	static GameEngineFBXMesh* Mesh_Prawn;


};

