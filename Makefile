CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
VULKAN_SDK_PATH = /Users/panagiotiskaragiannis/VulkanSDK/1.4.304.1

# Include and library directories
INCLUDE_DIRS = -I$(VULKAN_SDK_PATH)/macOS/include -I/opt/homebrew/Cellar/glfw/3.4/include $(foreach dir, $(wildcard */), -I$(dir))
LIBRARY_DIRS = -L$(VULKAN_SDK_PATH)/macOS/lib -L/opt/homebrew/Cellar/glfw/3.4/lib -Wl,-rpath,$(VULKAN_SDK_PATH)/macOS/lib
#LIBS = -lvulkan -lglfw 
LIBS = -lvulkan -lglfw -framework Cocoa -framework IOKit -framework CoreVideo -framework Metal -framework QuartzCore

# Target and source files
TARGET = output/vulkan_test
SOURCES = main.cpp $(wildcard */*.cpp)
OBJECTS = $(patsubst %.cpp, output/%.o, $(SOURCES))

# Default target
all: $(TARGET)

# Linking the target
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LIBRARY_DIRS) -o $@ $^ $(LIBS)

# Compiling object files
output/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

# Run the application
run: all
	./$(TARGET)

# Cleaning up
clean:
	rm -rf output