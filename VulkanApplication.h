#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#ifndef VULKANAPPLICATION_H
#define VULKANAPPLICATION_H

#include "Global.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <array>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <boost/format.hpp>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <optional>
#include <string>

struct UniformBufferObject
{
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
};

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(Vertex);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions()
	{
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		attributeDescriptions[2].binding = 0;
		attributeDescriptions[2].location = 2;
		attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[2].offset = offsetof(Vertex, texCoord);
		return attributeDescriptions;
	}
};

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	[[nodiscard]] bool isComplete() const
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class VulkanApplication
{
  public:
	VulkanApplication(int width, int height, std::string title);

	void run();

  private:
	void initWindow();
	static void frameBufferResizeCallback(GLFWwindow *window, [[maybe_unused]] int width, [[maybe_unused]] int height);
	void initVulkan();
	void pickPhysicalDevice();
	void createInstance();
	void createLogicalDevice();
	void createSurface();
	void mainLoop();
	void cleanup() const;
	void cleanupSwapChain() const;
	static std::vector<const char *> getRequiredExtensions();
	[[nodiscard]] bool isDeviceSuitable(const VkPhysicalDevice &device) const;
	[[nodiscard]] QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device) const;
	static bool checkValidationLayerSupport();
	static bool checkDeviceExtensionSupport(const VkPhysicalDevice &device);
	[[nodiscard]] SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice &device) const;
	static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &avaiableFormats);
	static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &avaiablePresentModes);
	[[nodiscard]] VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities) const;
	void createSwapChain();
	void createImageViews();
	void createGraphicsPipeline();
	[[nodiscard]] VkShaderModule createShaderModule(const std::vector<char> &code) const;
	void createRenderPass();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) const;
	void createSyncObjects();
	void recreateSwapChain();
	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();
	void createTextureImage();
	void createDescriptorPool();
	void createDescriptorSets();
	[[nodiscard]] uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer &buffer, VkDeviceMemory &bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void createDescriptorSetLayout();
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);
	void createTextureImageView();
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags flags);
	void createTextureSampler();
	void createDepthResources();
	VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();
	bool hasStencilComponent(VkFormat format);
	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	void loadModel();
	// Drawing Functions
	void drawFrame();
	void updateUniformBuffer(uint32_t currentImage);

	int width;
	int height;
	std::string title;
	GLFWwindow *window = nullptr;
	VkInstance instance;
	VkPhysicalDevice physicalDevice;
	VkDevice device{};
	VkQueue graphicsQueue;
	QueueFamilyIndices qfIndices;
	VkSurfaceKHR surface{};
	VkQueue presentQueue{};
	VkSwapchainKHR swapChain{};
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat{};
	VkExtent2D swapChainExtent{};
	VkRenderPass renderPass{};
	VkDescriptorSetLayout descriptorSetLayout{};
	VkPipelineLayout pipelineLayout{};
	VkPipeline graphicsPipeline{};
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkCommandPool commandPool{};

	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkSemaphore> imageAvaiableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	uint32_t currentFrame = 0;

	bool framebufferResized = false;

	VkBuffer vertexBuffer{};
	VkDeviceMemory vertexBufferMemory{};
	VkBuffer indexBuffer{};
	VkDeviceMemory indexBufferMemory{};

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void *> uniformBuffersMapped;

	VkDescriptorPool descriptorPool{};
	std::vector<VkDescriptorSet> descriptorSets;

	VkImage textureImage{};
	VkDeviceMemory textureImageMemory{};
	VkImageView textureImageView{};
	VkSampler textureSampler{};

	VkImage depthImage{};
	VkDeviceMemory depthImageMemory{};
	VkImageView depthImageView{};

#ifdef SQUARE_EXAMPLE
	std::vector<Vertex> vertices = {
	    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
	    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
	    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
	    {{-0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},

	    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
	    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
	    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
	    {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}

	};

	std::vector<uint32_t> indices = {
	    0, 1, 2, 2, 3, 0,
	    4, 5, 6, 6, 7, 4

	};
#else
	std::vector<Vertex> vertices{};
	std::vector<uint32_t> indices{};
#endif
};

#endif // VULKANAPPLICATION_H

#pragma clang diagnostic pop