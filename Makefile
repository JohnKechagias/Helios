# -=- Makefile -=-

# CPP flags
ENGINE_PATH = $(shell pwd)/Engine
CFLAGS = -std=c++20 -I$(VULKAN_SDK_PATH)/include -I$(srcdir)/Engine
# Linker flags
#LFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXrandr

LFLAGS = -L$(VULKAN_SDK_PATH)/lib `pkg-config --static --libs glfw3` -lvulkan

VulkanTest: *.cpp *.hpp
	g++ $(CFLAGS) -o VulkanTest *.cpp $(LFLAGS)

.PHONY: test clean

test: VulkanTest
	LD_LIBRARY_PATH=$(VULKAN_SDK_PATH)/lib
		VK_LAYER_PATH=$(VULKAN_SDK_PATH)/etc/vulkan/explicit_layer.d
		./VulkanTest

clean:
	rm -f VulkanTest