#pragma once

#include"Walnut/Image.h"

#include"Camera.h"
#include"Ray.h"
#include"Scene.h"

#include<memory>
#include <glm/glm.hpp>

class Renderer
{
public:
	struct Settings
	{
		bool Accumulate = true;
	};
public:
	Renderer() = default;

	void OnResize(uint32_t width, uint32_t height);
	void Render(const Scene &scene, const Camera& camera);

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }

	void ResetFrameIndex() { m_FrameIndex = 1; }
	Settings& GetSettings() { return m_Settings; }
private:
	struct HitPayLoad
	{
		float HitDistance;
		glm::vec3 worldNormal;
		glm::vec3 worldPosition;

		int objectIndex;
	};

	glm::vec4 PerPixel(uint32_t x, uint32_t y); //ReyGen

	HitPayLoad TraceRay(const Ray& ray);
	HitPayLoad ClosestHit(const Ray& ray, float hitDistance, int objectIndex);
	HitPayLoad Miss(const Ray& ray);
private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	Settings m_Settings;

	std::vector<uint32_t> m_ImageHorizontalIterator, m_ImageVerticalIterator; 

	const Scene* m_AtiveScene = nullptr;
	const Camera* m_AtiveCamera = nullptr;

	uint32_t* m_ImageData = nullptr;
	glm::vec4* m_AccumulateData = nullptr;


	uint32_t m_FrameIndex = 1;

};